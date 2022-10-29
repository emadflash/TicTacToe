#pragma once

#include "SDL2/SDL.h"

#include "player.hpp"
#include "sdl_data.hpp"
#include "rgba.hpp"
#include "vec.hpp"

#include <array>

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
  void Update(const SDL_Data &sdl);
  void Render(SDL_Data &sdl , std::array<Rgba, 2> playerMap)const;
  bool ContainsPosition(const Vec2<int> &clickPos) const;
  Vec2<Uint8> GetCellFromClickPosition(const Vec2<int> &clickPos);
  void FillCell(const Vec2<Uint8> &cell, Uint8 playerId);
  void Reset();

private:
  Vec2f startPos, gap;
  float gridWidth, gridHeight;
  Uint8 filled_cells = 0;

  void updateMeasurements(const SDL_Data &sdl);
  void drawCell(SDL_Data &sdl, Vec2f pos, Vec2f dim, Rgba cell_color) const;
  void renderCells(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const;
};
