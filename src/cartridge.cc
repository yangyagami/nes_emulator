#include "cartridge.h"

#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>

namespace nes {

std::shared_ptr<Cartridge> Cartridge::LoadRom(const std::string &path) {
  std::vector<uint8_t> rom_content;

  std::ifstream rom(path, std::ios::binary);
  if (rom.is_open() == false) {
    std::cerr << "No such file: " << path << std::endl;
    return nullptr;
  }
  rom_content = std::vector<uint8_t>((std::istreambuf_iterator<char>(rom)),
                             std::istreambuf_iterator<char>());

  const int header_size = 16;
  const int trainer_size = 512;

  if (rom_content.size() <= header_size ||
      std::string(rom_content.begin(), rom_content.begin() + 4) != "NES\x1a") {
    std::cerr << "Not a valid nes file: " << path << std::endl;
    return nullptr;
  }

  std::shared_ptr<Cartridge> cartridge = std::make_shared<Cartridge>();

  int program_rom_data_size = rom_content[4];
  int chr_rom_data_size = rom_content[5];
  cartridge->flags_6.all = rom_content[6];
  cartridge->flags_7.all = rom_content[7];
  cartridge->flags_8 = rom_content[8];
  cartridge->flags_9 = rom_content[9];
  cartridge->flags_10.all = rom_content[10];

  std::cout << std::endl;
  std::cout << "Cartridge info: " << std::endl;
  std::cout << "Program rom data size: " << program_rom_data_size << std::endl;
  std::cout << "Chr rom data size: " << chr_rom_data_size << std::endl;
  std::cout << "Flags6: " << static_cast<int>(cartridge->flags_6.all) << std::endl;
  std::cout << std::endl;

  int program_rom_data_start = header_size;
  if (cartridge->flags_6.trainer == 1) {
    std::copy(rom_content.begin() + header_size,
              rom_content.begin() + header_size + trainer_size,
              cartridge->trainer_.begin());
    program_rom_data_start = header_size + trainer_size;
  }
  cartridge->program_rom_data_.resize(program_rom_data_size * 16384);
  std::copy(rom_content.begin() + program_rom_data_start,
            rom_content.begin() + program_rom_data_start + program_rom_data_size * 16384,
            cartridge->program_rom_data_.begin());

  int chr_rom_data_start = program_rom_data_start + program_rom_data_size * 16384;
  cartridge->chr_rom_data_.resize(chr_rom_data_size * 8192);
  std::copy(rom_content.begin() + chr_rom_data_start,
            rom_content.begin() + chr_rom_data_start + chr_rom_data_size * 8192,
            cartridge->chr_rom_data_.begin());

  return cartridge;
}

}
