#include <stdio.h>

#include <array>
#include <iostream>
#include <memory>
#include <functional>

#include "raylib.h"

#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"

void DebugCPU(nes::CPU &cpu) {
  int offset = 10;

  DrawText("Registers:", 10, offset, 20, BLACK);

  DrawText("A: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x", cpu.a()), 10 + 50, offset, 20, BLACK);

  DrawText("X: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x", cpu.x()), 10 + 50, offset, 20, BLACK);

  DrawText("Y: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x", cpu.y()), 10 + 50, offset, 20, BLACK);

  DrawText("PC: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x", cpu.pc()), 10 + 50, offset, 20, BLACK);

  DrawText("SP: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x", cpu.s()), 10 + 50, offset, 20, BLACK);

  DrawText("P: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("0x%02x N:%d O:%d - B:%d D:%d I:%d Z:%d C:%d",
                      cpu.p, cpu.p.negative, cpu.p.overflow,
                      cpu.p.b, cpu.p.decimal, cpu.p.interrupt_disable,
                      cpu.p.zero, cpu.p.carry),
           10 + 50, offset, 20, BLACK);
}

void DebugMemory(const std::array<uint8_t, 65536> &memory, int start_pos = 0) {
  const int start_x = 300;
  int x = start_x;
  int y = 10;

  DrawText("Memory:", x - 60, y, 20, BLACK);

  y += 40;
  int count = 0;
  for (size_t i = start_pos; i < memory.size(); i++) {
    if (count == 0) {
      DrawText(TextFormat("%04x: ", i), x - 60, y, 20, BLACK);
    }
    count++;
    DrawText(TextFormat("%02x", memory[i]), x, y, 20, BLACK);
    x += 40;
    if ((count + 1) % 16 == 0) {
      x = start_x;
      y += 40;
      count = 0;
    }
  }
}

int main() {
  std::cout << "Begin cpu test" << std::endl;

  std::array<uint8_t, 65536> memory = {0};

  nes::PPU ppu;
  nes::CPU cpu(memory,
               std::bind(&nes::PPU::Read, &ppu, std::placeholders::_1),
               std::bind(&nes::PPU::Write, &ppu, std::placeholders::_1,
                         std::placeholders::_2));

  cpu.OnPowerUp();
  cpu.OnReset();

  InitWindow(1600, 960, "CPU test");

  // SetTargetFPS(60);

  std::shared_ptr<nes::Cartridge> cartridge =
      nes::Cartridge::LoadRom("Super Mario Bros (PC10).nes");
  if (cartridge == nullptr) {
    std::cerr << "Load cartridge failed!" << std::endl;
    return 1;
  }

  cpu.OnCartridgeInsert(cartridge);
  ppu.OnCartridgeInsert(cartridge);

  bool single_step = true;

  auto execute = [&](){
    for (int i = 0; i < 3; i++) {
      ppu.Tick();
      if (ppu.nmi_request()) {
        cpu.NMI();
      }
    }

    cpu.Tick();
  };

  while (!WindowShouldClose()) {
    if (!single_step) {
      do {
        execute();
      } while (!ppu.one_frame_finished());
    } else if (IsKeyPressed(KEY_D)) {
      execute();
    }

    if (IsKeyPressed(KEY_C)) {
      single_step = !single_step;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    ppu.ShowPatterns(1200, 20);


    DebugCPU(cpu);
    // DebugMemory(memory, 0x8000);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
