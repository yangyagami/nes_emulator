// Copyright (c) 2023 杨思宇. All rights reserved.

#ifndef NES_EMULATOR_CPU_H_
#define NES_EMULATOR_CPU_H_

#include <stdint.h>

#include <array>
#include <format>
#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <utility>

#include "ppu.h"
#include "utils.h"

/*
  ###Reference from nesdev.###

  ##Accumulator##
  A is byte-wide and along with the arithmetic logic unit (ALU), supports using
  the status register for carrying, overflow detection, and so on.

  ##Indexes##
  X and Y are byte-wide and used for several addressing modes. They can be used
  as loop counters easily, using INC/DEC and branch instructions. Not being the
  accumulator, they have limited addressing modes themselves when loading and
  saving.

  ##Program Counter##
  The 2-byte program counter PC supports 65536 direct (unbanked) memory
  locations, however not all values are sent to the cartridge. It can be
  accessed either by allowing CPU's internal fetch logic increment the address
  bus, an interrupt (NMI, Reset, IRQ/BRQ), and using the RTS/JMP/JSR/Branch
  instructions.

  ##Stack Pointer##
  S is byte-wide and can be accessed using interrupts, pulls, pushes, and
  transfers. It indexes into a 256-byte stack at $0100-$01FF.

  ##Status Register##
  P has 6 bits used by the ALU but is byte-wide. PHP, PLP, arithmetic, testing,
  and branch instructions can access this register. See status flags.
*/

namespace nes {

class CPU {
 public:
  enum class AddressMode {
    kNone = 0,
    kImmediate,
    kZeroPage,
    kZeroPageX,
    kZeroPageY,
    kAbsolute,
    kAbsoluteX,
    kAbsoluteY,
    kIndirect,
    kIndirectZeroX,
    kIndirectZeroY,
    kRelative,
  };

  struct OPCODE {
    std::string name;
    AddressMode address_mode;
    uint8_t cycles;
  };

  explicit CPU(std::array<uint8_t, 65536> &memory,
               std::function<uint8_t(PPU::Registers, bool)> ppu_access);
  ~CPU();

  void OnPowerUp();
  void OnReset();
  void OnCartridgeInsert() {
    pc_ = 0x8000;
  }

  void Tick();

  uint8_t a() { return a_; }
  uint8_t x() { return x_; }
  uint8_t y() { return y_; }
  uint16_t pc() { return pc_; }
  uint8_t s() { return s_; }

 private:
  inline void Write8bit(uint8_t value, uint16_t address) {
    memory_[address] = value;
  }

  uint8_t HandlePPURead(uint16_t address) {
    switch (address) {
      case 0x2002: { // PPUSTATUS
        return ppu_access_(PPU::Registers::kPPUSTATUS, false);
      }
      default: {
        std::string msg =
            std::format("Not implementation ppu read address: {}", address);
        NES_ASSERT(false, msg);
      }
    }
  }

  uint8_t Read8bit(uint16_t address) {
    if (address >= 0x2000 && address <= 0x2007) {
      // Read ppu registers.
      return HandlePPURead(address);
    }
    return memory_[address];
  }

  inline uint16_t Read16bit(uint16_t address) {
    return (memory_[address + 1] << 8) | memory_[address];
  }

 private:
  void PushStack(uint8_t value);
  uint8_t PopStack();

  bool PageCrossed(uint16_t address) {
    return (address & 0xff00) != (pc_ & 0xff00);
  }

  void NextInstruction(AddressMode address_mode) {
    switch (address_mode) {
      case AddressMode::kNone: {
        pc_++;
        break;
      }
      case AddressMode::kAbsoluteX:
      case AddressMode::kAbsoluteY:
      case AddressMode::kAbsolute: {
        pc_ += 3;
        break;
      }
      case AddressMode::kZeroPage:
      case AddressMode::kImmediate:
      case AddressMode::kRelative: {
        pc_ += 2;
        break;
      }
      default: {
        NES_ASSERT(false,
                   std::format("No implementation address mode for NextInstruction: {}",
                               static_cast<int>(address_mode)));
      }
    }
  }

 private:
  // @INSTRUCTIONS
  // void Return(const OPCODE &opcode);
  void Break(const OPCODE &opcode);
  void JumptoSubRoutine(const OPCODE &opcode);
  void SetInterruptDisable(const OPCODE &opcode);
  void ClearDecimal(const OPCODE &opcode);
  void AddWithCarry(const OPCODE &opcode);
  void TransXToStackPointer(const OPCODE &opcode);

  void Compare(const OPCODE &opcode);
  void CompareX(const OPCODE &opcode);
  void CompareY(const OPCODE &opcode);

  void LoadToAccumulator(const OPCODE &opcode);
  void LoadToX(const OPCODE &opcode);
  void LoadToY(const OPCODE &opcode);

  void StoreFromAccumulator(const OPCODE &opcode);
  void StoreFromX(const OPCODE &opcode);
  // void StoreFromY(const OPCODE &opcode);

  void BranchIfPositive(const OPCODE &opcode);
  void BranchWhenCarryFlagSet(const OPCODE &opcode);
  void BranchIfNotEqual(const OPCODE &opcode);

  void DecrementX(const OPCODE &opcode);
  void DecrementY(const OPCODE &opcode);
  void IncrementX(const OPCODE &opcode);
  void IncrementY(const OPCODE &opcode);

  // @ADDRESS MODE
  uint16_t Addressing(AddressMode address_mode) {
    switch (address_mode) {
      case AddressMode::kRelative: {
        return RelativeAddressing();
      }
      case AddressMode::kAbsolute: {
        return AbsoluteAddressing();
      }
      case AddressMode::kAbsoluteX: {
        return AbsoluteXAddressing();
      }
      case AddressMode::kAbsoluteY: {
        return AbsoluteYAddressing();
      }
      case AddressMode::kImmediate: {
        return ImmediateAddressing();
      }
      case AddressMode::kZeroPage: {
        return ZeroPageAddressing();
      }
      default: {
        NES_ASSERT(false, std::format("No support address mode: {}",
                                      static_cast<int>(address_mode)));
      }
    }
  }

  uint16_t RelativeAddressing() {
    int8_t relative_address = Read8bit(pc_ + 1);
    // Skip current opcode.
    uint16_t new_address = pc_ + 2 + relative_address;
    if (PageCrossed(new_address)) {
      cycles_++;
    }
    return new_address;
  }

  uint16_t ImmediateAddressing() { return pc_ + 1; }

  uint16_t ZeroPageAddressing() { return Read8bit(pc_ + 1); }

  uint16_t ZeroPageXAddressing() {
    uint8_t tmp = Read8bit(pc_ + 1);
    uint16_t ret = x_ + tmp;

    return ret & 0x00ff;
  }

  uint16_t ZeroPageYAddressing() {
    uint8_t tmp = Read8bit(pc_ + 1);
    uint16_t ret = y_ + tmp;

    return ret & 0x00ff;
  }

  uint16_t AbsoluteAddressing() {
    uint16_t ret = Read8bit(pc_ + 2);
    ret = (ret << 8) | Read8bit(pc_ + 1);

    return ret;
  }

  uint16_t AbsoluteXAddressing() {
    uint16_t ret = Read8bit(pc_ + 2);
    ret = (ret << 8) | Read8bit(pc_ + 1);

    ret += x_;

    if (PageCrossed(ret)) {
      cycles_++;
    }

    return ret;
  }

  uint16_t AbsoluteYAddressing() {
    uint16_t ret = Read8bit(pc_ + 2);
    ret = (ret << 8) | Read8bit(pc_ + 1);

    ret += y_;

    if (PageCrossed(ret)) {
      cycles_++;
    }

    return ret;
  }

 public:
   union {
     struct {
       uint8_t carry             : 1;  // 进位标志位
       uint8_t zero              : 1;  // 零标志位
       uint8_t interrupt_disable : 1;  // 中断禁止标志位
       uint8_t decimal           : 1;  // 十进制模式标志位
       uint8_t b                 : 1;  // 未使用的位 : 1; B FLAG
       uint8_t none              : 1;  // 未使用的位
       uint8_t overflow          : 1;  // 溢出标志位
       uint8_t negative          : 1;  // 负数标志位
     };
     uint8_t raw;
   } p;

 private:
  uint8_t a_;
  uint8_t x_;
  uint8_t y_;
  uint16_t pc_;
  uint8_t s_;

  std::array<uint8_t, 65536> &memory_;

  int cycles_;

  std::function<uint8_t(PPU::Registers, bool)> ppu_access_;

#include "opcodes_define.inl"
};

}  // namespace nes

#endif  // NES_EMULATOR_CPU_H_
