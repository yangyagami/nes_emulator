#include "ppu.h"

#include <iostream>

#include "raylib.h"
#include "utils.h"

namespace nes {

uint8_t PPU::Read(Registers reg) {
  uint8_t ret = 0;
  switch (reg) {
    case Registers::kPPUSTATUS: {
      ret = ppu_status.raw;
      ppu_status.vblank = 0;
      w_ = 0;
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
    case Registers::kPPUADDR: {
      if (w_ == 0) {
        w_ = 1;
        vram_address_ |= value;
        vram_address_ <<= 8;
      } else {
        w_ = 0;
        vram_address_ |= value;
      }
      break;
    }
    case Registers::kPPUDATA: {
      vram_[vram_address_++] = value;
      break;
    }
    case Registers::kPPUSCROLL: {
      if (w_ == 0) {
        scroll_x = value;
        w_ = 1;
      } else {
        scroll_y = value;
        w_ = 0;
      }
      break;
    }
    case Registers::kOAMADDR: {
      // TODO(yangsiyu): Full future implementation.
      oamaddr = value;
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
  // Pre-render scanline (-1 or 261)
  if (scanline_ == -1 || scanline_ == 261) {
    // TODO(yangsiyu):
    one_frame_finished_ = false;
  }

  // Visible scanlines (0-239)
  if (scanline_ >= 0 && scanline_ <= 239) {
    // TODO(yangsiyu): Render sth...
  }
  /*
    The VBlank flag of the PPU is set at tick 1 (the second tick) of
    scanline 241, where the VBlank NMI also occurs. The PPU makes no memory
    accesses during these scanlines, so PPU memory can be freely accessed by
    the program.
  */
  if (cycle_ == 1 && scanline_ == 241) {
    ppu_status.vblank = 1;

    if (ppu_ctrl.vblank) {
      nmi_request_ = true;
    }
  }

  cycle_++;

  if (cycle_ >= kCycleEnd) { // One scanline finish.
    scanline_++;
    cycle_ = 0;
    if (scanline_ >= kScanlineEnd) {
      one_frame_finished_ = true;
      scanline_ = -1;
      cycle_ = 0;
    }
  }
}

void PPU::ShowPatterns(int x, int y) {
  constexpr int kSize = 3;
  int row = 0;
  int column = 0;

  for (size_t i = 0; i <= 0x1FFF; i += 16) {
    int offset = 0;
    for (size_t j = i; j < i+8; j++) {
      uint8_t plane0 = vram_[j];
      uint8_t plane1 = vram_[j + 8];

      for (int bit_pos = 7; bit_pos >= 0; bit_pos--) {
        uint8_t plane0_cur_bit = (plane0 & (1 << bit_pos)) >> bit_pos;
        uint8_t plane1_cur_bit = (plane1 & (1 << bit_pos)) >> bit_pos;
        uint8_t color_idx = plane0_cur_bit + plane1_cur_bit * 2;
        auto color = BLACK;
        switch (color_idx) {
          case 1: {
            color = DARKBLUE;
            break;
          }
          case 2: {
            color = RED;
            break;
          }
          case 3: {
            color = WHITE;
            break;
          }
        }
        DrawRectangle(x + (column * 8 + 7 - bit_pos) * kSize,
                      y + (row * 8 + offset) * kSize, kSize, kSize, color);
      }
      offset++;
    }
    column++;
    if (column % 16 == 0) {
      row++;
      column = 0;
    }
  }
}

}  // namespace nes
