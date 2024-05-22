#include "utils.h"

#define NES_INSTRUCTION_ASSERT(condition, instruction_name) \
  do { \
    NES_ASSERT((condition), std::format("Invalid " #instruction_name " instruction, opcode name: {}, address mode: {}, cycles: {}", opcode.name, static_cast<int>(opcode.address_mode), opcode.cycles)); \
  } while (false)

void CPU::Break(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "BRK" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 7, "Break");

  PushStack(pc_ >> 8);
  PushStack(pc_ & 0xff);

  PushStack(p_);

  SetStatusFlag(StatusFlags::kInterruptDisable, true);

  pc_ = Read8bit(0xfffe) | (Read8bit(0xffff) << 8);
}

void CPU::BranchIfPositive(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "BPL" &&
                         opcode.address_mode == AddressMode::kRelative &&
                         opcode.cycles == 2, "BranchIfPositive");

  if (GetStatusFlag(StatusFlags::kNegative) == false) {
    pc_ = Addressing(opcode.address_mode);
  } else {
    NextInstruction(opcode.address_mode);
  }
}

void CPU::JumptoSubRoutine(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "JSR" &&
                         opcode.address_mode == AddressMode::kAbsolute &&
                         opcode.cycles == 6, "JumptoSubRoutine");
}

void CPU::SetInterruptDisable(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "SEI" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "SetInterruptDisable");

  SetStatusFlag(StatusFlags::kInterruptDisable, true);

  NextInstruction(opcode.address_mode);
}

void CPU::ClearDecimal(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "CLD" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "ClearDecimal");

  SetStatusFlag(StatusFlags::kDecimal, false);

  NextInstruction(opcode.address_mode);
}

void CPU::LoadToAccumulator(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "LDA" &&
                         opcode.address_mode != AddressMode::kNone,
                         "LoadToAccumulator");

  uint16_t new_address = Addressing(opcode.address_mode);
  a_ = Read8bit(new_address);

  if (((a_ & 0x8000) >> 7) == 1) {
    SetStatusFlag(StatusFlags::kNegative, true);
  } else if (a_ == 0) {
    SetStatusFlag(StatusFlags::kZero, true);
  }

  NextInstruction(opcode.address_mode);
}

void CPU::StoreFromAccumulator(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "STA" &&
                         opcode.address_mode != AddressMode::kNone,
                         "StoreFromAccumulator");

  uint16_t new_address = Addressing(opcode.address_mode);
  Write8bit(new_address, a_);

  NextInstruction(opcode.address_mode);
}

void CPU::LoadToX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "LDX" &&
                         opcode.address_mode != AddressMode::kNone,
                         "LoadToX");

  uint16_t new_address = Addressing(opcode.address_mode);
  x_ = Read8bit(new_address);

  if (((x_ & 0x8000) >> 7) == 1) {
    SetStatusFlag(StatusFlags::kNegative, true);
  } else if (a_ == 0) {
    SetStatusFlag(StatusFlags::kZero, true);
  }

  NextInstruction(opcode.address_mode);
}

void CPU::AddWithCarry(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "ADC" &&
                         opcode.address_mode != AddressMode::kNone,
                         "AddWithCarry");

  uint16_t new_address = Addressing(opcode.address_mode);
  uint8_t tmp = a_;
  a_ += Read8bit(new_address);

  if (((a_ & 0x8000) >> 7) == 1) {
    SetStatusFlag(StatusFlags::kNegative, true);
  } else if (a_ == 0) {
    SetStatusFlag(StatusFlags::kZero, true);
  } else if (a_ < tmp) {
    SetStatusFlag(StatusFlags::kCarry, true);
  }

  NextInstruction(opcode.address_mode);
}

void CPU::TransXToStackPointer(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "TXS" &&
                         opcode.address_mode == AddressMode::kNone,
                         "TransXToStackPointer");

  s_ = x_;

  NextInstruction(opcode.address_mode);
}

#undef NES_INSTRUCTION_ASSERT
