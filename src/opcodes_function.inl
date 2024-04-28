void CPU::Break(OPCODE &opcode) {
  assert(opcode.name == "BRK" && opcode.address_mode == AddressMode::kNone
         && opcode.circle == 7);

  PushStack(pc_ >> 8);
  PushStack(pc & 0xff);

  PushStack(p_.all);

  p_.interrupt = 1;

  pc_ = Read8bit(0xfffe) | (Read8bit(0xffff) << 8);
}

void CPU::BranchIfPositive(OPCODE &opcode) {
  assert(opcode.name == "BPL" && opcode.address_mode == AddressMode::kRelative
         && opcode.circle == 2);

  uint8_t relative_address = Read8bit(pc_);

  if (p_.negative == 0) {
    uint16_t new_address = pc_ + relative_address;
    bool page_crossed = (new_address & 0xff00) != (pc_ & 0xff00);
    pc_ = new_address;
    opcode.cycles++;
    if (page_crossed) {
      opcode.cycles++;
    }
  } else {
    pc_++;
  }
}
