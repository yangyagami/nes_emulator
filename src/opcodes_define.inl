std::map<uint8_t, OPCODE> opcodes_ =
{
  std::pair(0x00, OPCODE{"BRK", AddressMode::kNone, 7 }),
  std::pair(0x01, OPCODE{"ORA", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0x03, OPCODE{"SLO", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0x04, OPCODE{"NOP", AddressMode::kZeroPage, 3 }),
  std::pair(0x05, OPCODE{"ORA", AddressMode::kZeroPage, 3 }),
  std::pair(0x06, OPCODE{"ASL", AddressMode::kZeroPage, 5 }),
  std::pair(0x07, OPCODE{"SLO", AddressMode::kZeroPage, 5 }),
  std::pair(0x08, OPCODE{"PHP", AddressMode::kNone, 3 }),
  std::pair(0x09, OPCODE{"ORA", AddressMode::kImmediate, 2 }),
  std::pair(0x0A, OPCODE{"ASL", AddressMode::kNone, 2 }),
  std::pair(0x0B, OPCODE{"ANC", AddressMode::kImmediate, 2 }),
  std::pair(0x0C, OPCODE{"NOP", AddressMode::kAbsolute, 4 }),
  std::pair(0x0D, OPCODE{"ORA", AddressMode::kAbsolute, 4 }),
  std::pair(0x0E, OPCODE{"ASL", AddressMode::kAbsolute, 6 }),
  std::pair(0x0F, OPCODE{"SLO", AddressMode::kAbsolute, 6 }),
  std::pair(0x10, OPCODE{"BPL", AddressMode::kRelative, 2 }),
  std::pair(0x11, OPCODE{"ORA", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0x13, OPCODE{"SLO", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0x14, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0x15, OPCODE{"ORA", AddressMode::kZeroPageX, 4 }),
  std::pair(0x16, OPCODE{"ASL", AddressMode::kZeroPageX, 6 }),
  std::pair(0x17, OPCODE{"SLO", AddressMode::kZeroPageX, 6 }),
  std::pair(0x18, OPCODE{"CLC", AddressMode::kNone, 2 }),
  std::pair(0x19, OPCODE{"ORA", AddressMode::kAbsoluteY, 4 }),
  std::pair(0x1A, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0x1B, OPCODE{"SLO", AddressMode::kAbsoluteY, 7 }),
  std::pair(0x1C, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x1D, OPCODE{"ORA", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x1E, OPCODE{"ASL", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x1F, OPCODE{"SLO", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x20, OPCODE{"JSR", AddressMode::kAbsolute, 6 }),
  std::pair(0x21, OPCODE{"AND", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0x23, OPCODE{"RLA", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0x24, OPCODE{"BIT", AddressMode::kZeroPage, 3 }),
  std::pair(0x25, OPCODE{"AND", AddressMode::kZeroPage, 3 }),
  std::pair(0x26, OPCODE{"ROL", AddressMode::kZeroPage, 5 }),
  std::pair(0x27, OPCODE{"RLA", AddressMode::kZeroPage, 5 }),
  std::pair(0x28, OPCODE{"PLP", AddressMode::kNone, 4 }),
  std::pair(0x29, OPCODE{"AND", AddressMode::kImmediate, 2 }),
  std::pair(0x2A, OPCODE{"ROL", AddressMode::kNone, 2 }),
  std::pair(0x2B, OPCODE{"ANC", AddressMode::kImmediate, 2 }),
  std::pair(0x2C, OPCODE{"BIT", AddressMode::kAbsolute, 4 }),
  std::pair(0x2D, OPCODE{"AND", AddressMode::kAbsolute, 4 }),
  std::pair(0x2E, OPCODE{"ROL", AddressMode::kAbsolute, 6 }),
  std::pair(0x2F, OPCODE{"RLA", AddressMode::kAbsolute, 6 }),
  std::pair(0x30, OPCODE{"BMI", AddressMode::kRelative, 2 }),
  std::pair(0x31, OPCODE{"AND", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0x33, OPCODE{"RLA", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0x34, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0x35, OPCODE{"AND", AddressMode::kZeroPageX, 4 }),
  std::pair(0x36, OPCODE{"ROL", AddressMode::kZeroPageX, 6 }),
  std::pair(0x37, OPCODE{"RLA", AddressMode::kZeroPageX, 6 }),
  std::pair(0x38, OPCODE{"SEC", AddressMode::kNone, 2 }),
  std::pair(0x39, OPCODE{"AND", AddressMode::kAbsoluteY, 4 }),
  std::pair(0x3A, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0x3B, OPCODE{"RLA", AddressMode::kAbsoluteY, 7 }),
  std::pair(0x3C, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x3D, OPCODE{"AND", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x3E, OPCODE{"ROL", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x3F, OPCODE{"RLA", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x40, OPCODE{"RTI", AddressMode::kNone, 6 }),
  std::pair(0x41, OPCODE{"EOR", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0x43, OPCODE{"SRE", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0x44, OPCODE{"NOP", AddressMode::kZeroPage, 3 }),
  std::pair(0x45, OPCODE{"EOR", AddressMode::kZeroPage, 3 }),
  std::pair(0x46, OPCODE{"LSR", AddressMode::kZeroPage, 5 }),
  std::pair(0x47, OPCODE{"SRE", AddressMode::kZeroPage, 5 }),
  std::pair(0x48, OPCODE{"PHA", AddressMode::kNone, 3 }),
  std::pair(0x49, OPCODE{"EOR", AddressMode::kImmediate, 2 }),
  std::pair(0x4A, OPCODE{"LSR", AddressMode::kNone, 2 }),
  std::pair(0x4B, OPCODE{"ALR", AddressMode::kImmediate, 2 }),
  std::pair(0x4C, OPCODE{"JMP", AddressMode::kAbsolute, 3 }),
  std::pair(0x4D, OPCODE{"EOR", AddressMode::kAbsolute, 4 }),
  std::pair(0x4E, OPCODE{"LSR", AddressMode::kAbsolute, 6 }),
  std::pair(0x4F, OPCODE{"SRE", AddressMode::kAbsolute, 6 }),
  std::pair(0x50, OPCODE{"BVC", AddressMode::kRelative, 2 }),
  std::pair(0x51, OPCODE{"EOR", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0x53, OPCODE{"SRE", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0x54, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0x55, OPCODE{"EOR", AddressMode::kZeroPageX, 4 }),
  std::pair(0x56, OPCODE{"LSR", AddressMode::kZeroPageX, 6 }),
  std::pair(0x57, OPCODE{"SRE", AddressMode::kZeroPageX, 6 }),
  std::pair(0x58, OPCODE{"CLI", AddressMode::kNone, 2 }),
  std::pair(0x59, OPCODE{"EOR", AddressMode::kAbsoluteY, 4 }),
  std::pair(0x5A, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0x5B, OPCODE{"SRE", AddressMode::kAbsoluteY, 7 }),
  std::pair(0x5C, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x5D, OPCODE{"EOR", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x5E, OPCODE{"LSR", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x5F, OPCODE{"SRE", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x60, OPCODE{"RTS", AddressMode::kNone, 6 }),
  std::pair(0x61, OPCODE{"ADC", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0x63, OPCODE{"RRA", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0x64, OPCODE{"NOP", AddressMode::kZeroPage, 3 }),
  std::pair(0x65, OPCODE{"ADC", AddressMode::kZeroPage, 3 }),
  std::pair(0x66, OPCODE{"ROR", AddressMode::kZeroPage, 5 }),
  std::pair(0x67, OPCODE{"RRA", AddressMode::kZeroPage, 5 }),
  std::pair(0x68, OPCODE{"PLA", AddressMode::kNone, 4 }),
  std::pair(0x69, OPCODE{"ADC", AddressMode::kImmediate, 2 }),
  std::pair(0x6A, OPCODE{"ROR", AddressMode::kNone, 2 }),
  std::pair(0x6B, OPCODE{"ARR", AddressMode::kImmediate, 2 }),
  std::pair(0x6C, OPCODE{"JMP", AddressMode::kIndirect, 5 }),
  std::pair(0x6D, OPCODE{"ADC", AddressMode::kAbsolute, 4 }),
  std::pair(0x6E, OPCODE{"ROR", AddressMode::kAbsolute, 6 }),
  std::pair(0x6F, OPCODE{"RRA", AddressMode::kAbsolute, 6 }),
  std::pair(0x70, OPCODE{"BVS", AddressMode::kRelative, 2 }),
  std::pair(0x71, OPCODE{"ADC", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0x73, OPCODE{"RRA", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0x74, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0x75, OPCODE{"ADC", AddressMode::kZeroPageX, 4 }),
  std::pair(0x76, OPCODE{"ROR", AddressMode::kZeroPageX, 6 }),
  std::pair(0x77, OPCODE{"RRA", AddressMode::kZeroPageX, 6 }),
  std::pair(0x78, OPCODE{"SEI", AddressMode::kNone, 2 }),
  std::pair(0x79, OPCODE{"ADC", AddressMode::kAbsoluteY, 4 }),
  std::pair(0x7A, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0x7B, OPCODE{"RRA", AddressMode::kAbsoluteY, 7 }),
  std::pair(0x7C, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x7D, OPCODE{"ADC", AddressMode::kAbsoluteX, 4 }),
  std::pair(0x7E, OPCODE{"ROR", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x7F, OPCODE{"RRA", AddressMode::kAbsoluteX, 7 }),
  std::pair(0x80, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0x81, OPCODE{"STA", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0x82, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0x83, OPCODE{"SAX", AddressMode::kImmediate, 2 }),
  std::pair(0x84, OPCODE{"STY", AddressMode::kZeroPage, 3 }),
  std::pair(0x85, OPCODE{"STA", AddressMode::kZeroPage, 3 }),
  std::pair(0x86, OPCODE{"STX", AddressMode::kZeroPage, 3 }),
  std::pair(0x87, OPCODE{"SAX", AddressMode::kZeroPage, 3 }),
  std::pair(0x88, OPCODE{"DEY", AddressMode::kNone, 2 }),
  std::pair(0x89, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0x8A, OPCODE{"TXA", AddressMode::kNone, 2 }),
  std::pair(0x8B, OPCODE{"XAA", AddressMode::kImmediate, 2 }),
  std::pair(0x8C, OPCODE{"STY", AddressMode::kAbsolute, 4 }),
  std::pair(0x8D, OPCODE{"STA", AddressMode::kAbsolute, 4 }),
  std::pair(0x8E, OPCODE{"STX", AddressMode::kAbsolute, 4 }),
  std::pair(0x8F, OPCODE{"SAX", AddressMode::kAbsolute, 4 }),
  std::pair(0x90, OPCODE{"BCC", AddressMode::kRelative, 2 }),
  std::pair(0x91, OPCODE{"STA", AddressMode::kIndirectZeroY, 6 }),
  std::pair(0x92, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0x93, OPCODE{"AHX", AddressMode::kIndirectZeroY, 6 }),
  std::pair(0x94, OPCODE{"STY", AddressMode::kZeroPageX, 4 }),
  std::pair(0x95, OPCODE{"STA", AddressMode::kZeroPageX, 4 }),
  std::pair(0x96, OPCODE{"STX", AddressMode::kZeroPageY, 4 }),
  std::pair(0x97, OPCODE{"SAX", AddressMode::kZeroPageY, 4 }),
  std::pair(0x98, OPCODE{"TYA", AddressMode::kNone, 2 }),
  std::pair(0x99, OPCODE{"STA", AddressMode::kAbsoluteY, 5 }),
  std::pair(0x9A, OPCODE{"TXS", AddressMode::kNone, 2 }),
  std::pair(0x9B, OPCODE{"TAS", AddressMode::kAbsoluteY, 5 }),
  std::pair(0x9C, OPCODE{"SHY", AddressMode::kAbsoluteX, 5 }),
  std::pair(0x9D, OPCODE{"STA", AddressMode::kAbsoluteX, 5 }),
  std::pair(0x9E, OPCODE{"SHX", AddressMode::kAbsoluteY, 5 }),
  std::pair(0x9F, OPCODE{"AHX", AddressMode::kAbsoluteY, 5 }),
  std::pair(0xA0, OPCODE{"LDY", AddressMode::kImmediate, 2 }),
  std::pair(0xA1, OPCODE{"LDA", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0xA2, OPCODE{"LDX", AddressMode::kImmediate, 2 }),
  std::pair(0xA3, OPCODE{"LAX", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0xA4, OPCODE{"LDY", AddressMode::kZeroPage, 3 }),
  std::pair(0xA5, OPCODE{"LDA", AddressMode::kZeroPage, 3 }),
  std::pair(0xA6, OPCODE{"LDX", AddressMode::kZeroPage, 3 }),
  std::pair(0xA7, OPCODE{"LAX", AddressMode::kZeroPage, 3 }),
  std::pair(0xA8, OPCODE{"TAY", AddressMode::kNone, 2 }),
  std::pair(0xA9, OPCODE{"LDA", AddressMode::kImmediate, 2 }),
  std::pair(0xAA, OPCODE{"TAX", AddressMode::kNone, 2 }),
  std::pair(0xAB, OPCODE{"LAX", AddressMode::kImmediate, 2 }),
  std::pair(0xAC, OPCODE{"LDY", AddressMode::kAbsolute, 4 }),
  std::pair(0xAD, OPCODE{"LDA", AddressMode::kAbsolute, 4 }),
  std::pair(0xAE, OPCODE{"LDX", AddressMode::kAbsolute, 4 }),
  std::pair(0xAF, OPCODE{"LAX", AddressMode::kAbsolute, 4 }),
  std::pair(0xB0, OPCODE{"BCS", AddressMode::kRelative, 2 }),
  std::pair(0xB1, OPCODE{"LDA", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0xB2, OPCODE{"KIL", AddressMode::kNone, 0 }),
  std::pair(0xB3, OPCODE{"LAX", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0xB4, OPCODE{"LDY", AddressMode::kZeroPageX, 4 }),
  std::pair(0xB5, OPCODE{"LDA", AddressMode::kZeroPageX, 4 }),
  std::pair(0xB6, OPCODE{"LDX", AddressMode::kZeroPageY, 4 }),
  std::pair(0xB7, OPCODE{"LAX", AddressMode::kZeroPageY, 4 }),
  std::pair(0xB8, OPCODE{"CLV", AddressMode::kNone, 2 }),
  std::pair(0xB9, OPCODE{"LDA", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xBA, OPCODE{"TSX", AddressMode::kNone, 2 }),
  std::pair(0xBB, OPCODE{"LAS", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xBC, OPCODE{"LDY", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xBD, OPCODE{"LDA", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xBE, OPCODE{"LDX", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xBF, OPCODE{"LAX", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xC0, OPCODE{"CPY", AddressMode::kImmediate, 2 }),
  std::pair(0xC1, OPCODE{"CMP", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0xC2, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0xC3, OPCODE{"DCP", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0xC4, OPCODE{"CPY", AddressMode::kZeroPage, 3 }),
  std::pair(0xC5, OPCODE{"CMP", AddressMode::kZeroPage, 3 }),
  std::pair(0xC6, OPCODE{"DEC", AddressMode::kZeroPage, 5 }),
  std::pair(0xC7, OPCODE{"DCP", AddressMode::kZeroPage, 5 }),
  std::pair(0xC8, OPCODE{"INY", AddressMode::kNone, 2 }),
  std::pair(0xC9, OPCODE{"CMP", AddressMode::kImmediate, 2 }),
  std::pair(0xCA, OPCODE{"DEX", AddressMode::kNone, 2 }),
  std::pair(0xCB, OPCODE{"AXS", AddressMode::kImmediate, 2 }),
  std::pair(0xCC, OPCODE{"CPY", AddressMode::kAbsolute, 4 }),
  std::pair(0xCD, OPCODE{"CMP", AddressMode::kAbsolute, 4 }),
  std::pair(0xCE, OPCODE{"DEC", AddressMode::kAbsolute, 6 }),
  std::pair(0xCF, OPCODE{"DCP", AddressMode::kAbsolute, 6 }),
  std::pair(0xD0, OPCODE{"BNE", AddressMode::kRelative, 2 }),
  std::pair(0xD1, OPCODE{"CMP", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0xD3, OPCODE{"DCP", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0xD4, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0xD5, OPCODE{"CMP", AddressMode::kZeroPageX, 4 }),
  std::pair(0xD6, OPCODE{"DEC", AddressMode::kZeroPageX, 6 }),
  std::pair(0xD7, OPCODE{"DCP", AddressMode::kZeroPageX, 6 }),
  std::pair(0xD8, OPCODE{"CLD", AddressMode::kNone, 2 }),
  std::pair(0xD9, OPCODE{"CMP", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xDA, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0xDB, OPCODE{"DCP", AddressMode::kAbsoluteY, 7 }),
  std::pair(0xDC, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xDD, OPCODE{"CMP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xDE, OPCODE{"DEC", AddressMode::kAbsoluteX, 7 }),
  std::pair(0xDF, OPCODE{"DCP", AddressMode::kAbsoluteX, 7 }),
  std::pair(0xE0, OPCODE{"CPX", AddressMode::kImmediate, 2 }),
  std::pair(0xE1, OPCODE{"SBC", AddressMode::kIndirectZeroX, 6 }),
  std::pair(0xE2, OPCODE{"NOP", AddressMode::kImmediate, 2 }),
  std::pair(0xE3, OPCODE{"ISC", AddressMode::kIndirectZeroX, 8 }),
  std::pair(0xE4, OPCODE{"CPX", AddressMode::kZeroPage, 3 }),
  std::pair(0xE5, OPCODE{"SBC", AddressMode::kZeroPage, 3 }),
  std::pair(0xE6, OPCODE{"INC", AddressMode::kZeroPage, 5 }),
  std::pair(0xE7, OPCODE{"ISC", AddressMode::kZeroPage, 5 }),
  std::pair(0xE8, OPCODE{"INX", AddressMode::kNone, 2 }),
  std::pair(0xE9, OPCODE{"SBC", AddressMode::kImmediate, 2 }),
  std::pair(0xEA, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0xEB, OPCODE{"SBC", AddressMode::kImmediate, 2 }),
  std::pair(0xEC, OPCODE{"CPX", AddressMode::kAbsolute, 4 }),
  std::pair(0xED, OPCODE{"SBC", AddressMode::kAbsolute, 4 }),
  std::pair(0xEE, OPCODE{"INC", AddressMode::kAbsolute, 6 }),
  std::pair(0xEF, OPCODE{"ISC", AddressMode::kAbsolute, 6 }),
  std::pair(0xF0, OPCODE{"BEQ", AddressMode::kRelative, 2 }),
  std::pair(0xF1, OPCODE{"SBC", AddressMode::kIndirectZeroY, 5 }),
  std::pair(0xF3, OPCODE{"ISC", AddressMode::kIndirectZeroY, 8 }),
  std::pair(0xF4, OPCODE{"NOP", AddressMode::kZeroPageX, 4 }),
  std::pair(0xF5, OPCODE{"SBC", AddressMode::kZeroPageX, 4 }),
  std::pair(0xF6, OPCODE{"INC", AddressMode::kZeroPageX, 6 }),
  std::pair(0xF7, OPCODE{"ISC", AddressMode::kZeroPageX, 6 }),
  std::pair(0xF8, OPCODE{"SED", AddressMode::kNone, 2 }),
  std::pair(0xF9, OPCODE{"SBC", AddressMode::kAbsoluteY, 4 }),
  std::pair(0xFA, OPCODE{"NOP", AddressMode::kNone, 2 }),
  std::pair(0xFB, OPCODE{"ISC", AddressMode::kAbsoluteY, 7 }),
  std::pair(0xFC, OPCODE{"NOP", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xFD, OPCODE{"SBC", AddressMode::kAbsoluteX, 4 }),
  std::pair(0xFE, OPCODE{"INC", AddressMode::kAbsoluteX, 7 }),
  std::pair(0xFF, OPCODE{"ISC", AddressMode::kAbsoluteX, 7 }),
};

#define NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND(name, func) \
  std::pair(name, std::bind(&func, this, std::placeholders::_1))

std::map<std::string, std::function<void(OPCODE &)>> opcode_functions_ = {
  // Offical
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("BRK", CPU::Break),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("SEI", CPU::SetInterruptDisable),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("CLD", CPU::ClearDecimal),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("LDA", CPU::LoadToAccumulator),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("BPL", CPU::BranchIfPositive),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("STA", CPU::StoreFromAccumulator),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("LDX", CPU::LoadToX),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("TXS", CPU::TransXToStackPointer),
  NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND("CMP", CPU::Compare),
};

#undef NES_EMULATOR_OPCODES_DEFINE_FUNCTION_BIND
