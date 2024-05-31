#ifndef NES_EMULATOR_PPU_H_
#define NES_EMULATOR_PPU_H_

#include <stdint.h>

#include <array>
#include <format>
#include <string>

#include "raylib.h"
#include "utils.h"

namespace nes {

class PPU {
 public:
  enum class Registers {
    kPPUCTRL = 0,
    kPPUMASK,
    kPPUSTATUS,
    kOAMADDR,
    kOAMDATA,
    kPPUSCROLL,
    kPPUADDR,
    kPPUDATA,
    kOAMDMA
  };

  explicit PPU()
      : scanline_(-1),
        cycle_(0),
        one_frame_finished_(false) {
    ppu_ctrl.raw = 0;
    ppu_status.raw = 0;
  }
  ~PPU() {}

  uint8_t Access(Registers reg, bool write) {
    uint8_t ret = 0;
    switch (reg) {
    case Registers::kPPUSTATUS: {
      if (!write) {
        ret = ppu_status.raw;
        ppu_status.vblank = 0;
      } else {
        NES_ASSERT(false, "PPUSTATUS register could only read!");
      }
      break;
    }
    default: {
      std::string msg = std::format("Not implementation register access: {}",
                                    static_cast<int>(reg));
      NES_ASSERT(false, msg);
      break;
    }
    }
    return ret;
  }

  void Tick() {
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

 public:
  // PPU registers.
  /*
  Controller ($2000) > write
  Common name: PPUCTRL
  Description: PPU control register
  Access: write
  Various flags controlling PPU operation

  7  bit  0
  ---- ----
  VPHB SINN
  |||| ||||
  |||| ||++- Base nametable address
  |||| ||    (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
  |||| |+--- VRAM address increment per CPU read/write of PPUDATA
  |||| |     (0: add 1, going across; 1: add 32, going down)
  |||| +---- Sprite pattern table address for 8x8 sprites
  ||||       (0: $0000; 1: $1000; ignored in 8x16 mode)
  |||+------ Background pattern table address (0: $0000; 1: $1000)
  ||+------- Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1)
  |+-------- PPU master/slave select
  |          (0: read backdrop from EXT pins; 1: output color on EXT pins)
  +--------- Generate an NMI at the start of the
             vertical blanking interval (0: off; 1: on)
  */
  union {
    struct {
      uint8_t base_nametable_address : 2;
      uint8_t vram_address_increment : 1;
      uint8_t sprite_pattern_table_address : 1;
      uint8_t background_pattern_table_address : 1;
      uint8_t sprite_size : 1;
      uint8_t ppu_master_or_slave_select : 1;
      uint8_t vblank : 1;
    };
    uint8_t raw;
  } ppu_ctrl;

  /*
     Status ($2002) < read
     Common name: PPUSTATUS
     Description: PPU status register
     Access: read
     This register reflects the state of various functions inside the PPU. It is
     often used for determining timing. To determine when the PPU has reached a given
     pixel of the screen, put an opaque (non-transparent) pixel of sprite 0 there.

     7  bit  0
     ---- ----
     VSO. ....
     |||| ||||
     |||+-++++- PPU open bus. Returns stale PPU bus contents.
     ||+------- Sprite overflow. The intent was for this flag to be set
     ||         whenever more than eight sprites appear on a scanline, but a
     ||         hardware bug causes the actual behavior to be more complicated
     ||         and generate false positives as well as false negatives; see
     ||         PPU sprite evaluation. This flag is set during sprite
     ||         evaluation and cleared at dot 1 (the second dot) of the
     ||         pre-render line.
     |+-------- Sprite 0 Hit.  Set when a nonzero pixel of sprite 0 overlaps
     |          a nonzero background pixel; cleared at dot 1 of the pre-render
     |          line.  Used for raster timing.
     +--------- Vertical blank has started (0: not in vblank; 1: in vblank).
                Set at dot 1 of line 241 (the line *after* the post-render
                line); cleared after reading $2002 and at dot 1 of the
                pre-render line.
   */
  union {
    struct {
      uint8_t stale_bus_contents : 5;
      uint8_t sprite_overflow    : 1;
      uint8_t sprite_0_hit       : 1;
      uint8_t vblank             : 1;
    };
    uint8_t raw;
  } ppu_status;

 private:
  const int kCycleEnd = 341;
  const int kScanlineEnd = 262;

  int scanline_;
  int cycle_;

  bool one_frame_finished_;
};

} // namespace nes

#endif // NES_EMULATOR_PPU_H_
