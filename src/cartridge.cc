#include "cartridge.h"

#include <memory>
#include <fstream>
#include <iostream>

namespace nes {

std::shared_ptr<Cartridge> Cartridge::LoadRom(const std::string &path) {
  std::vector<uint8_t> rom_content;

  std::ifstream rom(path, std::ios::binary);
  if (rom.is_open() == false) {
    return nullptr;
  }
  rom_content = std::vector<uint8_t>((std::istreambuf_iterator<char>(rom)),
                             std::istreambuf_iterator<char>());
  if (rom_content.size() <= 0 ||
      std::string(rom_content.begin(), rom_content.begin() + 4) != "NES\x1a") {
    std::cerr << "Not a valid nes file: " << path << std::endl;
    return nullptr;
  }

  std::shared_ptr<Cartridge> cartridge = std::make_shared<Cartridge>();

  int program_rom_data_size = rom_content[4];
  int chr_rom_data_size = rom_content[5];
  cartridge->flags_6.all = rom_content[6];

  const int header_size = 16;
  const int trainer_size = 512;
  int program_rom_data_start = header_size;
  if (cartridge->flags_6.trainer == 1) {
    program_rom_data_start = header_size + trainer_size;
  }
  std::copy(rom_content.begin() + program_rom_data_start,
            rom_content.begin() + program_rom_data_start + program_rom_data_size * 16384,
            cartridge->program_rom_data_.begin());

  return cartridge;
}

}
