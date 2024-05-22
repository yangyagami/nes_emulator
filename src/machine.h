// Copyright (c) 2023 杨思宇. All rights reserved.

#ifndef NES_EMULATOR_MACHINE_H_
#define NES_EMULATOR_MACHINE_H_

#include "cpu.h"

namespace nes {

class Machine {
 public:
  Machine();
  ~Machine();
 private:
  std::array<uint8_t, 65536> memory_;

  CPU cpu_;
};

}  // namespace nes

#endif  // NES_EMULATOR_MACHINE_H_
