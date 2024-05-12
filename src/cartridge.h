#ifndef NES_EMULATOR_CARTRIDGE_H_
#define NES_EMULATOR_CARTRIDGE_H_

#include <memory>
#include <vector>
#include <string>

namespace nes {

class Cartridge {
 public:
  static std::shared_ptr<Cartridge> LoadRom(const std::string &path);
 private:
  union {
    struct {
      uint8_t nametable_arrangement : 1;
      uint8_t extern_program_memory : 1;
      uint8_t trainer : 1;
      uint8_t alternative_nametable_layout : 1;
    };
    uint8_t all;
  } flags_6;

  std::vector<uint8_t> program_rom_data_;
  std::vector<uint8_t> chr_rom_data_;
};

}

#endif  // NES_EMULATOR_CARTRIDGE_H_
