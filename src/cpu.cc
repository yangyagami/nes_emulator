#include "cpu.h"

#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include <functional>

#include "utils.h"

namespace nes {

CPU::CPU(std::array<uint8_t, 65536> &memory,
         std::function<uint8_t(PPU::Registers)> ppu_read,
         std::function<void(uint8_t, PPU::Registers)> ppu_write)
    : memory_(memory),
      cycles_(0),
      ppu_read_(ppu_read),
      ppu_write_(ppu_write) {
  OnPowerUp();
}

CPU::~CPU() {}

void CPU::OnPowerUp() {
  a_ = x_ = y_ = 0;
  p.raw = 0x34;
  s_ = 0xFD;
}

void CPU::OnReset() {
  a_ = x_ = y_ = 0;
  p.interrupt_disable = 1;
  s_ -= 3;

  std::fill(memory_.begin(), memory_.end(), 0);
}

void CPU::Tick() {
  cycles_ = 0;

  uint8_t opcode = Read8bit(pc_);
  // Map opcode to function
  NES_ASSERT(opcodes_.find(opcode) != opcodes_.end(),
             std::format("No such opcode: {:#x}", opcode));

  OPCODE opcode_obj = opcodes_[opcode];

  NES_ASSERT(opcode_functions_.find(opcode_obj.name) != opcode_functions_.end(),
             std::format("No implementation opcode: {}", opcode_obj.name));

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
