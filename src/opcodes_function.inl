void CPU::Break(OPCODE &opcode) {
  assert(opcode.name == "BRK" && opcode.address_mode == AddressMode::kNone
         && opcode.cycles == 7);

  PushStack(pc_ >> 8);
  PushStack(pc_ & 0xff);

  PushStack(p_);

  SetStatusFlag(StatusFlags::kInterrupt_disable, true);

  pc_ = Read8bit(0xfffe) | (Read8bit(0xffff) << 8);
}

void CPU::BranchIfPositive(OPCODE &opcode) {
  assert(opcode.name == "BPL" && opcode.address_mode == AddressMode::kRelative
         && opcode.cycles == 2);

  if (GetStatusFlag(StatusFlags::kNegative) == false) {
    pc_ = Addressing(opcode.address_mode);
  } else {
    pc_++;
  }
}

void CPU::JumptoSubRoutine(OPCODE &opcode) {
  assert(opcode.name == "JSR" && opcode.address_mode == AddressMode::kAbsolute
         && opcode.cycles == 6);
}
