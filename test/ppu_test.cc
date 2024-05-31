#include <format>
#include <iostream>

#include "raylib.h"

#include "ppu.h"

int main() {
  InitWindow(800, 600, "ppu_test");
  SetTargetFPS(60);

  nes::PPU ppu;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ppu.Tick();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
