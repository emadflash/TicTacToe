#pragma once

#include <SDL2/SDL.h>

#include "platform.hpp"
#include "player.hpp"
#include "rgba.hpp"
#include "vec.hpp"

class Grid {
public:
  Uint8 size;
  Sint8 cells[3][3];
  float cellPadding;

  explicit Grid(Uint8 size, float cellPadding) : size(size), cellPadding(cellPadding) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        cells[i][j] = -1;
      }
    }
  }

  inline bool IsFull() const { return bool(filled_cells == size * size); }
  void Update(Platform *platform);
  void Render(Platform *platform, std::array<Rgba, 2> playerMap) const;
  bool ContainsPosition(const Vec2<int> &clickPos) const;
  Vec2<Uint8> GetCellFromClickPosition(const Vec2<int> &clickPos);
  void FillCell(const Vec2<Uint8> &cell, Uint8 playerId);
  void Reset();

private:
  Vec2f startPos, gap;
  float gridWidth, gridHeight;
  Uint8 filled_cells = 0;

  void updateMeasurements(Platform *platform);
  void drawCell(Platform *platform, Vec2f pos, Vec2f dim, Rgba cell_color) const;
  void renderCells(Platform *platform, std::array<Rgba, 2> playerMap) const;
};
