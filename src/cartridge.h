// Copyright (c) 2023 杨思宇. All rights reserved.

#ifndef NES_EMULATOR_CARTRIDGE_H_
#define NES_EMULATOR_CARTRIDGE_H_

#include <memory>
#include <vector>
#include <string>
#include <array>

namespace nes {

class Cartridge {
 public:
  static std::shared_ptr<Cartridge> LoadRom(const std::string &path);

  const std::vector<uint8_t> &program_rom_data() { return program_rom_data_; }
  const std::vector<uint8_t> &chr_rom_data() { return chr_rom_data_; }

 private:
  union {
    struct {
      uint8_t nametable_arrangement : 1;
      uint8_t extern_program_memory : 1;  // ($6000 - 7FFF)
      uint8_t trainer : 1;  // (512-byte trainer at $7000-$71FF (stored before PRG data)
      uint8_t alternative_nametable_layout : 1;
    };
    uint8_t all;
  } flags_6;

  union {
    struct {
      uint8_t vs_unisystem : 1;
      uint8_t playchoice_10 : 1;  // (8 KB of Hint Screen data stored after CHR data)
      uint8_t nes_2_0 : 2;  // If equal to 2, flags 8-15 are in NES 2.0 format.
    };
    uint8_t all;
  } flags_7;

  uint8_t flags_8;  // PRG RAM size

  uint8_t flags_9;  // 0 bit: TV system (0: NTSC; 1: PAL), remain bit: Reserved, set to zero.

  /*
This byte is not part of the official specification, and relatively few
emulators honor it.

The PRG RAM Size value (stored in byte 8) was recently added to the official
specification; as such, virtually no ROM images in circulation make use of it.

Older versions of the iNES emulator ignored bytes 7-15, and several ROM
management tools wrote messages in there. Commonly, these will be filled with
"DiskDude!", which results in 64 being added to the mapper number.

A general rule of thumb: if the last 4 bytes are not all zero, and the header is
not marked for NES 2.0 format, an emulator should either mask off the upper 4
bits of the mapper number or simply refuse to load the ROM.
   */
  union {
    struct {
      uint8_t tv_system : 2;  // TV system (0: NTSC; 2: PAL; 1/3: dual compatible)
      uint8_t not_used : 2;
      uint8_t program_ram : 1;  // PRG RAM ($6000-$7FFF) (0: present; 1: not present)
      uint8_t board_flag : 1;  // 0: Board has no bus conflicts; 1: Board has bus conflicts
    };
    uint8_t all;
  } flags_10;

  std::array<uint8_t, 512> trainer_;
  std::vector<uint8_t> program_rom_data_;
  std::vector<uint8_t> chr_rom_data_;

};

}  // namespace nes

#endif  // NES_EMULATOR_CARTRIDGE_H_
