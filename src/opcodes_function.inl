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

  PushStack(p.raw);

  p.interrupt_disable = 1;

  pc_ = Read8bit(0xfffe) | (Read8bit(0xffff) << 8);
}

void CPU::JumptoSubRoutine(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "JSR" &&
                         opcode.address_mode == AddressMode::kAbsolute &&
                         opcode.cycles == 6, "JumptoSubRoutine");
  PushStack(pc_ >> 8);
  PushStack(pc_ & 0xff);

  uint16_t new_address = Addressing(opcode.address_mode);
  pc_ = new_address;
}

void CPU::SetInterruptDisable(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "SEI" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "SetInterruptDisable");

  p.interrupt_disable = 1;

  NextInstruction(opcode.address_mode);
}

void CPU::ClearDecimal(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "CLD" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "ClearDecimal");

  p.decimal = 0;

  NextInstruction(opcode.address_mode);
}

void CPU::LoadToAccumulator(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "LDA" &&
                         opcode.address_mode != AddressMode::kNone,
                         "LoadToAccumulator");

  uint16_t new_address = Addressing(opcode.address_mode);
  a_ = Read8bit(new_address);

  if (((a_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (a_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::LoadToX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "LDX" &&
                         opcode.address_mode != AddressMode::kNone,
                         "LoadToX");

  uint16_t new_address = Addressing(opcode.address_mode);
  x_ = Read8bit(new_address);

  if (((x_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (a_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::LoadToY(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "LDY" &&
                         opcode.address_mode != AddressMode::kNone,
                         "LoadToY");

  uint16_t new_address = Addressing(opcode.address_mode);
  y_ = Read8bit(new_address);

  if (((y_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (a_ == 0) {
    p.zero = 1;
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

  if (((a_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (a_ == 0) {
    p.zero = 1;
  } else if (a_ < tmp) {
    p.carry = 1;
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

void CPU::Compare(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "CMP" &&
                         opcode.address_mode != AddressMode::kNone,
                         "Compare");

  uint16_t new_address = Addressing(opcode.address_mode);
  uint8_t v = Read8bit(new_address);
  uint8_t result = a_ - v;
  if (((result & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (result == 0) {
    p.zero = 1;
  } else if (result > a_) {
    p.carry = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::CompareX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "CPX" &&
                         opcode.address_mode != AddressMode::kNone,
                         "CompareX");
  uint16_t new_address = Addressing(opcode.address_mode);
  uint8_t v = Read8bit(new_address);
  uint8_t result = x_ - v;

  if (((result & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (result == 0) {
    p.zero = 1;
  } else if (result > a_) {
    p.carry = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::CompareY(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "CPY" &&
                         opcode.address_mode != AddressMode::kNone,
                         "CompareY");
  uint16_t new_address = Addressing(opcode.address_mode);
  uint8_t v = Read8bit(new_address);
  uint8_t result = y_ - v;

  if (((result & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (result == 0) {
    p.zero = 1;
  } else if (result > a_) {
    p.carry = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::BranchWhenCarryFlagSet(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "BCS" &&
                         opcode.address_mode == AddressMode::kRelative &&
                         opcode.cycles == 2, "BranchWhenCarryFlagSet");

  if (p.carry == 1) {
    pc_ = Addressing(opcode.address_mode);
  } else {
    NextInstruction(opcode.address_mode);
  }
}

void CPU::DecrementX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "DEX" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "DecrementX");
  x_ -= 1;
  if (((x_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (x_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::DecrementY(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "DEY" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "DecrementY");
  y_ -= 1;
  if (((y_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (y_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::IncrementX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "INX" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "IncrementX");

  x_ += 1;
  if (((x_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (x_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::IncrementY(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "INY" &&
                         opcode.address_mode == AddressMode::kNone &&
                         opcode.cycles == 2, "IncrementY");

  y_ += 1;
  if (((y_ & 0x80) >> 7) == 1) {
    p.negative = 1;
  } else if (y_ == 0) {
    p.zero = 1;
  }

  NextInstruction(opcode.address_mode);
}

void CPU::BranchIfPositive(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "BPL" &&
                         opcode.address_mode == AddressMode::kRelative &&
                         opcode.cycles == 2, "BranchIfPositive");

  if (p.negative == 0) {
    pc_ = Addressing(opcode.address_mode);
  } else {
    NextInstruction(opcode.address_mode);
  }
}

void CPU::BranchIfNotEqual(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "BNE" &&
                         opcode.address_mode == AddressMode::kRelative &&
                         opcode.cycles == 2, "BranchIfNotEqual");
  if (p.zero == 0) {
    pc_ = Addressing(opcode.address_mode);
  } else {
    NextInstruction(opcode.address_mode);
  }
}

void CPU::StoreFromAccumulator(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "STA" &&
                         opcode.address_mode != AddressMode::kNone,
                         "StoreFromAccumulator");

  uint16_t new_address = Addressing(opcode.address_mode);
  Write8bit(new_address, a_);

  NextInstruction(opcode.address_mode);
}

void CPU::StoreFromX(const OPCODE &opcode) {
  NES_INSTRUCTION_ASSERT(opcode.name == "STX" &&
                         opcode.address_mode != AddressMode::kNone,
                         "StoreFromX");

  uint16_t new_address = Addressing(opcode.address_mode);
  Write8bit(new_address, x_);

  NextInstruction(opcode.address_mode);
}

#undef NES_INSTRUCTION_ASSERT
