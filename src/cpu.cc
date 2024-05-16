#include "cpu.h"

#include <array>
#include <algorithm>
#include <cassert>

namespace nes {

CPU::CPU(std::array<uint8_t, 65536> &memory) : memory_(memory), cycles_(0) {
  OnPowerUp();
}

CPU::~CPU() {}

void CPU::OnPowerUp() {
  a_ = x_ = y_ = 0;
  p_ = 0x34;
  s_ = 0xFD;
}

void CPU::OnReset() {
  a_ = x_ = y_ = 0;
  SetStatusFlag(StatusFlags::kInterrupt_disable, true);
  s_ -= 3;

  std::fill(memory_.begin(), memory_.end(), 0);
}

void CPU::Tick() {
  cycles_ = 0;

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

  cycles_ += opcode_obj.cycles;

  while (cycles_-- > 0);
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
