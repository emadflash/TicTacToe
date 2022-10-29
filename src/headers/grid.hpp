#pragma once

#include "SDL2/SDL.h"

#include "player.hpp"
#include "rgba.hpp"
#include "sdl_data.hpp"
#include "vec.hpp"

#include <array>

class Grid {
public:
  Uint8 m_size;
  Sint8 m_cells[3][3];
  float m_cellPadding;

  explicit Grid(Uint8 size, float cellPadding) : m_size(size), m_cellPadding(cellPadding) {
    initGridState();
  }

  inline bool IsFull() const { return bool(m_filled_cells == m_size * m_size); }
  void Update(const SDL_Data &sdl);
  void Render(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const;
  bool ContainsPosition(const Vec2<int> &clickPos) const;
  Vec2<Uint8> GetCellFromClickPosition(const Vec2<int> &clickPos);
  void FillCell(const Vec2<Uint8> &cell, Uint8 playerId);
  void Reset();

private:
  Vec2f m_startPos, m_gap;
  float m_gridWidth, m_gridHeight;
  Uint8 m_filled_cells = 0;

  void updateMeasurements(const SDL_Data &sdl);
  void drawCell(SDL_Data &sdl, Vec2f pos, Vec2f dim, Rgba cell_color) const;
  void renderCells(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const;
  void initGridState();
};
