#include "headers/grid.hpp"
#include "headers/common.hpp"
#include "headers/rgba.hpp"
#include "headers/sdl_data.hpp"

#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"

void Grid::updateMeasurements(const SDL_Data &sdl) {
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
  startPos = Vec2f(sdl.m_windowDim.x * 0.10, sdl.m_windowDim.y * 0.20);

  float regionWidth = (sdl.m_windowDim.x * 0.60);  // width without padding
  float regionHeight = (sdl.m_windowDim.y * 0.60); // height without padding

  gridWidth = regionWidth - (regionWidth * 0.20);    // with padding
  gridHeight = regionHeight - (regionHeight * 0.20); // with padding

  gap = Vec2f(gridWidth / 3, gridHeight / 3);
}

void Grid::Update(const SDL_Data &sdl) {
  updateMeasurements(sdl);
}

void Grid::Reset() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cells[i][j] = -1;
    }
  }
  filled_cells = 0;
}

bool Grid::ContainsPosition(const Vec2<int> &clickPos) const {
  return bool(clickPos.x >= startPos.x && clickPos.x <= startPos.x + gridWidth &&
              clickPos.y >= startPos.y && clickPos.y <= startPos.y + gridHeight);
}

Vec2<Uint8> Grid::GetCellFromClickPosition(const Vec2<int> &clickPos) {
  DEBUG_ASSERT(ContainsPosition(clickPos));

  auto matchCol = [&]() -> Uint8 {
    for (int i = 0; i < size; ++i) {
      auto xDim = Vec2f(startPos.x + i * gap.x, startPos.x + (i + 1) * gap.x);
      if (clickPos.x > xDim.x && clickPos.x < xDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  auto matchRow = [&]() -> Uint8 {
    for (Uint8 i = 0; i < size; ++i) {
      auto yDim = Vec2f(startPos.y + i * gap.y, startPos.y + (i + 1) * gap.y);
      if (clickPos.y > yDim.x && clickPos.y < yDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  return Vec2<Uint8>(matchRow(), matchCol());
}

void Grid::FillCell(const Vec2<Uint8> &cell, Uint8 playerId) {
  if (cells[cell.x][cell.y] == -1) {
    cells[cell.x][cell.y] = playerId;
    filled_cells += 1;
  }
}

// Applies padding and then draws the cell
void Grid::drawCell(SDL_Data &sdl, Vec2f pos, Vec2f dim, Rgba cell_color) const {
  pos.x = pos.x + dim.x * cellPadding;
  pos.y = pos.y + dim.y * cellPadding;

  sdl.InitBackingRect(pos,
                      Vec2f(dim.x - (dim.x * 2 * cellPadding), dim.y - (dim.y * 2 * cellPadding)));
  SDL_SetRenderDrawColor(sdl.m_renderer, cell_color.x, cell_color.y, cell_color.z, cell_color.a);
  SDL_RenderFillRect(sdl.m_renderer, &sdl.m_backingRect);
}

void Grid::renderCells(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const {
  for (Uint8 i = 1; i < 4; ++i) {
    for (Uint8 j = 1; j < 4; ++j) {
      auto id = cells[i - 1][j - 1];
      if (id != -1) {
        Vec2f pos(startPos.x + j * gap.x, startPos.y + i * gap.y);
        Vec2f dim(pos.x - (pos.x + gap.x), pos.y - (pos.y + gap.y));

        drawCell(sdl, pos, dim, playerMap[id]);
      }
    }
  }
}

void Grid::Render(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const {
  SDL_SetRenderDrawColor(sdl.m_renderer, 0xff, 0xff, 0xff, 0x00);

  for (int i = 1; i < size; ++i) {
    SDL_RenderDrawLine(sdl.m_renderer, startPos.x, startPos.y + i * gap.y, startPos.x + gridWidth,
                       startPos.y + i * gap.y); // horizontonal line
    SDL_RenderDrawLine(sdl.m_renderer, startPos.x + i * gap.x, startPos.y, startPos.x + i * gap.x,
                       startPos.y + gridHeight); // vertical line
  }

  renderCells(sdl, playerMap);
}
