#include "cpu.h"

#include <array>
#include <algorithm>
#include <cassert>

namespace nes {

CPU::CPU(std::array<uint8_t, 65536> &memory) : memory_(memory) {
  Reset();
}

CPU::~CPU() {

}

void CPU::Reset() {
  a_ = x_ = y_ = p_.all = 0;
  s_ = Read8bit(0xFD);
  pc_ = Read16bit(0xFFFC);

  std::fill(memory_.begin(), memory_.end(), 0);
}

void CPU::Tick() {
  uint8_t opcode = Read8bit(pc_);
  // Map opcode to function
  if (opcodes_.find(opcode) == opcodes_.end()) {
    // TODO(yangsiyu): Handle no such opcode.
    return;
  }

  OPCODE opcode_obj = opcodes_[opcode];

  if (opcode_functions_.find(opcode_obj.name) == opcode_functions_.end()) {
    // TODO(yangsiyu): Handle no such opcode's method.
    return;
  }

  auto func = opcode_functions_[opcode_obj.name];

  func(opcode_obj);

  while (opcode_obj.cycles-- > 0);
}

void CPU::PushStack(uint8_t value) {
  Write8bit(value, 0x0100 + s_);
  s_ -= 1;
}

uint8_t CPU::PopStack() {
  s_ += 1;
  return Read8bit(0x0100 + s_);
}

#include "opcodes_function.inl"

}
