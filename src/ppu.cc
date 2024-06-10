#include "ppu.h"

namespace nes {

uint8_t PPU::Read(Registers reg) {
  uint8_t ret = 0;
  switch (reg) {
    case Registers::kPPUSTATUS: {
      ret = ppu_status.raw;
      ppu_status.vblank = 0;
      break;
    }
    default: {
      std::string msg = std::format("Not implementation register read: {}",
                                    static_cast<int>(reg));
      NES_ASSERT(false, msg);
      break;
    }
  }
  return ret;
}

void PPU::Write(uint8_t value, Registers reg) {
  switch (reg) {
    case Registers::kPPUCTRL: {
      ppu_ctrl.raw = value;
      break;
    }
    case Registers::kPPUMASK: {
      ppu_mask.raw = value;
      break;
    }
    default: {
      std::string msg = std::format("Not implementation register write: {}",
                                    static_cast<int>(reg));
      NES_ASSERT(false, msg);
      break;
    }
  }
}

void PPU::Tick() {
  bool loop_finish = false;
  while (!loop_finish) {
    /*
      The VBlank flag of the PPU is set at tick 1 (the second tick) of
      scanline 241, where the VBlank NMI also occurs. The PPU makes no memory
      accesses during these scanlines, so PPU memory can be freely accessed by
      the program.
     */
    if (cycle_ == 1 && scanline_ == 241) {
      ppu_status.vblank = 1;
      loop_finish = true;
    }
    cycle_++;

    if (cycle_ >= kCycleEnd) { // One scanline finish.
      scanline_++;
      cycle_ = 0;
      if (scanline_ >= kScanlineEnd) {
        one_frame_finished_ = true;
        scanline_ = -1;
        cycle_ = 0;
        break;
      }
    }
  }
}

}  // namespace nes
