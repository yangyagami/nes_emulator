#include <algorithm>
#include <iostream>
#include <array>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>

#include "raylib.h"

#include "cpu.h"

void DebugCPU(nes::CPU &cpu) {
  int offset = 10;

  DrawText("Registers:", 10, offset, 20, BLACK);

  DrawText("A: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("%u", cpu.a()), 10 + 50, offset, 20, BLACK);

  DrawText("X: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("%u", cpu.x()), 10 + 50, offset, 20, BLACK);

  DrawText("Y: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("%u", cpu.y()), 10 + 50, offset, 20, BLACK);

  DrawText("PC: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("%u", cpu.pc()), 10 + 50, offset, 20, BLACK);

  DrawText("SP: ", 10, offset += 30, 20, BLACK);
  DrawText(TextFormat("%u", cpu.s()), 10 + 50, offset, 20, BLACK);
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
    DrawText(TextFormat("%02x", 0), x, y, 20, BLACK);
    x += 40;
    if ((count + 1) % 16 == 0) {
      x = start_x;
      y += 40;
      count = 0;
    }
  }
}

std::vector<uint8_t> LoadRom(const std::string &rom_path) {
  std::vector<uint8_t> ret;

  std::ifstream rom(rom_path, std::ios::binary);
  if (rom.is_open() == false) {
    return ret;
  }
  ret = std::vector<uint8_t>((std::istreambuf_iterator<char>(rom)),
                             std::istreambuf_iterator<char>());
  return ret;
}

int main() {
  std::cout << "Begin cpu test" << std::endl;

  std::array<uint8_t, 65536> memory = { 0 };

  nes::CPU cpu(memory);

  InitWindow(1000, 600, "CPU test");

  SetTargetFPS(60);

  std::vector<uint8_t> rom = LoadRom("registers.nes");

  if (rom.size() <= 0 ||
      std::string(rom.begin(), rom.begin() + 4) != "NES\x1a") {
    // TODO(yangsiyu): Invalid rom file.
    return 1;
  }

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_D)) {
      cpu.Tick();
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DebugCPU(cpu);

    DebugMemory(memory);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
