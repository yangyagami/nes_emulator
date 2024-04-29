#ifndef NES_EMULATOR_CPU_H_
#define NES_EMULATOR_CPU_H_

#include <stdint.h>

#include <array>
#include <string>
#include <map>
#include <utility>
#include <functional>

/*
  ###Reference from nesdev.###

  ##Accumulator##
  A is byte-wide and along with the arithmetic logic unit (ALU), supports using the status register for carrying, overflow detection, and so on.

  ##Indexes##
  X and Y are byte-wide and used for several addressing modes. They can be used as loop counters easily, using INC/DEC and branch instructions. Not being the accumulator, they have limited addressing modes themselves when loading and saving.

  ##Program Counter##
  The 2-byte program counter PC supports 65536 direct (unbanked) memory locations, however not all values are sent to the cartridge. It can be accessed either by allowing CPU's internal fetch logic increment the address bus, an interrupt (NMI, Reset, IRQ/BRQ), and using the RTS/JMP/JSR/Branch instructions.

  ##Stack Pointer##
  S is byte-wide and can be accessed using interrupts, pulls, pushes, and transfers. It indexes into a 256-byte stack at $0100-$01FF.

  ##Status Register##
  P has 6 bits used by the ALU but is byte-wide. PHP, PLP, arithmetic, testing, and branch instructions can access this register. See status flags.
*/

namespace nes {

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

class CPU {
 public:
  CPU(std::array<uint8_t, 65536> &memory);
  ~CPU();

  void Reset();

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

  inline uint8_t Read8bit(uint16_t address) {
    return memory_[address];
  }

  inline uint16_t Read16bit(uint16_t address) {
    return (memory_[address + 1] << 8) | memory_[address];
  }
 private:
  void PushStack(uint8_t value);
  uint8_t PopStack();
 private:
  // @INSTRUCTIONS
  void Break(OPCODE &opcode);
  void BranchIfPositive(OPCODE &opcode);
  void JumptoSubRoutine(OPCODE &opcode);

  // @ADDRESS MODE
 private:
  uint8_t a_;
  uint8_t x_;
  uint8_t y_;
  uint16_t pc_;
  uint8_t s_;
  union {
    struct {
      uint8_t carry      : 1;  // 进位标志位
      uint8_t zero       : 1;  // 零标志位
      uint8_t interrupt  : 1;  // 中断禁止标志位
      uint8_t decimal    : 1;  // 十进制模式标志位
      uint8_t none       : 1;  // 未使用的位
      uint8_t none2      : 1;  // 未使用的位
      uint8_t overflow   : 1;  // 溢出标志位
      uint8_t negative   : 1;  // 负数标志位
    };
    uint8_t all;
  } p_;

  std::array<uint8_t, 65536> &memory_;

#include "opcodes_define.inl"
};

}

#endif  // NES_EMULATOR_CPU_H_
