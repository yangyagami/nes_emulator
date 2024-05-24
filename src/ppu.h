#ifndef NES_EMULATOR_PPU_H_
#define NES_EMULATOR_PPU_H_

#include <array>

#include "raylib.h"

namespace nes {

class PPU {
 public:
  explicit PPU() : scanline_(0), cycle_(0) {}
  ~PPU() {}

  void Tick() {
    while (true) {
      cycle_++;

      if (cycle_ >= kCycleEnd) { // One scanline finish.
        scanline_++;
        cycle_ = 0;
        if (scanline_ >= kScanlineEnd) {
          scanline_ = 0;
          cycle_ = 0;
          break;
        }
      }

      // Draw one pixel.
      std::array<decltype(BLUE), 4> colors = {GRAY, BLACK, LIGHTGRAY, WHITE};
      int color_idx = GetRandomValue(0, colors.size());
      const int kPixelSize = 8;
      DrawRectangle(cycle_ * kPixelSize, scanline_ * kPixelSize, kPixelSize,
                    kPixelSize, colors[color_idx]);
    }
  }

 private:
  const int kCycleEnd = 341;
  const int kScanlineEnd = 262;

  int scanline_;
  int cycle_;
};

}  // namespace nes

#endif  // NES_EMULATOR_PPU_H_
