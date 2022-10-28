#include "headers/grid.hpp"
#include "headers/common.hpp"
#include "headers/platform.hpp"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdint>
#include <iostream>

void Grid::updateMeasurements(Platform *platform) {
  // NOTE(madflash) - Grid Region
  // ______________
  // | __________ |
  // | |        | |
  // | |        | |
  // | |  Grid  | |
  // | |        | |
  // | |        | |
  // | |________| |
  // |____________|
  //
  // Empty Space around grid is padding

  // 10% padding from left/right
  // 20% padding from top/bottom
  startPos = Vec2f(platform->windowWidth * 0.10, platform->windowHeight * 0.20);

  float regionWidth = (platform->windowWidth * 0.60);   // width without padding
  float regionHeight = (platform->windowHeight * 0.60); // height without padding

  gridWidth = regionWidth - (regionWidth * 0.20);    // with padding
  gridHeight = regionHeight - (regionHeight * 0.20); // with padding

  gap = Vec2f(gridWidth / 3, gridHeight / 3);
}

void Grid::Update(Platform *platform) {
  updateMeasurements(platform);
}

void Grid::FillCell(float xClick, float yClick) {
  auto matchCol = [&]() -> Uint8 {
    for (int i = 0; i < cellCount; ++i) {
      auto xDim = Vec2f(startPos.x + i * gap.x, startPos.x + (i + 1) * gap.x);
      if (xClick > xDim.x && xClick < xDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  auto matchRow = [&]() -> Uint8 {
    for (Uint8 i = 0; i < cellCount; ++i) {
      auto yDim = Vec2f(startPos.y + i * gap.y, startPos.y + (i + 1) * gap.y);
      if (yClick > yDim.x && yClick < yDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  if (xClick >= startPos.x && xClick <= startPos.x + gridWidth && yClick >= startPos.y &&
      yClick <= startPos.y + gridHeight) {
    cellsFilled[matchRow()][matchCol()] = 1;
  }
}

void Grid::renderFilledCells(Platform *platform) const {
  for (Uint8 i = 1; i < 4; ++i) {
    for (Uint8 j = 1; j < 4; ++j) {
      if (cellsFilled[i - 1][j - 1] == 1) {
        Vec2f pos(startPos.x + j * gap.x, startPos.y + i * gap.y);
        Vec2f dim(pos.x - (pos.x + gap.x), pos.y - (pos.y + gap.y));

        platform->InitBackingRect(pos, dim);
        SDL_SetRenderDrawColor(platform->renderer, 0x00, 0xee, 0x00, 0xff);
        SDL_RenderFillRect(platform->renderer, &platform->backingRect);
      }
    }
  }
}

void Grid::Render(Platform *platform) const {
  SDL_SetRenderDrawColor(platform->renderer, 0xff, 0xff, 0xff, 0x00);

  for (int i = 1; i < cellCount; ++i) {
    SDL_RenderDrawLine(platform->renderer, startPos.x, startPos.y + i * gap.y,
                       startPos.x + gridWidth,
                       startPos.y + i * gap.y); // horizontonal line
    SDL_RenderDrawLine(platform->renderer, startPos.x + i * gap.x, startPos.y,
                       startPos.x + i * gap.x,
                       startPos.y + gridHeight); // vertical line
  }

  renderFilledCells(platform);
}
