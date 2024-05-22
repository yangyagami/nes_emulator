// Copyright (c) 2023 杨思宇. All rights reserved.

#include "cpu.h"

namespace machine {

class Machine {
 public:
  Machine();
  ~Machine();
 private:
  std::array<uint8_t, 65536> memory_;

  CPU cpu_;
};

}  // namespace machine
