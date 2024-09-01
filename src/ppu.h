#ifndef NES_EMULATOR_PPU_H_
#define NES_EMULATOR_PPU_H_

#include <memory>
#include <stdint.h>

#include <array>
#include <format>
#include <string>

#include "raylib.h"
#include "utils.h"
#include "cartridge.h"

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
      : w_(0),
        scroll_x(0),
        scroll_y(0),
        scanline_(-1),
        cycle_(0),
        one_frame_finished_(false),
        nmi_request_(false),
        vram_address_(0) {
    ppu_ctrl.raw = 0;
    ppu_status.raw = 0;
  }
  ~PPU() {}

  bool one_frame_finished() const { return one_frame_finished_; }

  void Write(uint8_t value, Registers reg);
  uint8_t Read(Registers reg);
  void Tick();

  void OnCartridgeInsert(std::shared_ptr<Cartridge> cartridge) {
    std::copy(cartridge->chr_rom_data().begin(),
              cartridge->chr_rom_data().end(), vram_.begin());
  }

  void ShowPatterns(int x, int y);

  bool nmi_request() {
    bool ret = nmi_request_;

    if (ret) {
      nmi_request_ = false;
    }

    return ret;
  }

 public:
  uint8_t w_;

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

  /*
    Mask ($2001) > write
    Common name: PPUMASK
    Description: PPU mask register
    Access: write
    This register controls the rendering of sprites and backgrounds, as well as
    colour effects.

    7  bit  0
    ---- ----
    BGRs bMmG
    |||| ||||
    |||| |||+- Greyscale (0: normal color, 1: produce a greyscale display)
    |||| ||+-- 1: Show background in leftmost 8 pixels of screen, 0: Hide
    |||| |+--- 1: Show sprites in leftmost 8 pixels of screen, 0: Hide
    |||| +---- 1: Show background
    |||+------ 1: Show sprites
    ||+------- Emphasize red (green on PAL/Dendy)
    |+-------- Emphasize green (red on PAL/Dendy)
    +--------- Emphasize blue
  */
  union {
    struct {
      uint8_t grey_scale         : 1;
      uint8_t show_bg_in_left    : 1;
      uint8_t show_sp_in_left    : 1;
      uint8_t show_bg            : 1;
      uint8_t show_sp            : 1;
      uint8_t emphasize_red      : 1;
      uint8_t emphasize_green    : 1;
      uint8_t emphasize_blue     : 1;
    };
    uint8_t raw;
  } ppu_mask;

  uint8_t scroll_x;
  uint8_t scroll_y;

 private:
  const int kCycleEnd = 341;
  const int kScanlineEnd = 262;

  int scanline_;
  int cycle_;

  bool one_frame_finished_;

  bool nmi_request_;

  std::array<uint8_t, 0x4000> vram_;
  uint16_t vram_address_;
};

} // namespace nes

#endif // NES_EMULATOR_PPU_H_
