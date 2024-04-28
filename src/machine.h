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

}
