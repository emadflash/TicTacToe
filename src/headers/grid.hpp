#pragma once

#include <SDL2/SDL.h>

#include "platform.hpp"
#include "player.hpp"
#include "vec.hpp"

class Grid {
public:
  Uint8 cells[32][32];
  Uint8 cellCount;

  explicit Grid(Uint8 cellCount) : cellCount(cellCount) {}

  void Update(Platform *platform);
  void Render(Platform *platform) const;
  void FillCell(float xClick, float yClick);

private:
  Vec2f startPos, gap;
  float gridWidth, gridHeight;

  // TODO(madflash): Replace this with hashing
  Uint8 cellsFilled[3][3];

  void updateMeasurements(Platform *platform);
  void renderFilledCells(Platform *platform) const;
};
