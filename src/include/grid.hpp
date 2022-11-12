#pragma once

#include "SDL.h"

#include "player.hpp"
#include "rgba.hpp"
#include "sdl_data.hpp"
#include "vec.hpp"

#include <array>

class Grid {
public:
  Uint8 m_size;
  Sint8 m_cells[3][3];

  Vec2f m_pos, m_cellWidth;
  Vec2<int> m_dim;
  float m_padding;
  float m_cellPadding;

  Grid() = default;
  Grid(Uint8 size, Vec2f pos, Vec2<int> dim) : m_size(size), m_pos(pos), m_dim(dim) {
    initGridState();
  }

  Grid(Uint8 size, Vec2f pos, Vec2<int> dim, float padding, float cellPadding)
      : m_size(size), m_pos(pos), m_dim(dim), m_padding(padding), m_cellPadding(cellPadding) {
    initGridState();
  }

  inline bool IsFull() const { return bool(m_filled_cells == m_size * m_size); }
  inline void SetPos(const Vec2f &pos) { m_pos = pos; }
  inline void SetDim(const Vec2<int> &dim) {
    m_dim.x = dim.x - (dim.x * m_padding);
    m_dim.y = dim.y - (dim.y * m_padding);
    m_cellWidth.x = m_dim.x / 3;
    m_cellWidth.y = m_dim.y / 3;
  }

  void Render(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const;
  bool ContainsPosition(const Vec2<int> &clickPos) const;
  Vec2<Uint8> GetCellFromClickPosition(const Vec2<int> &clickPos);
  void FillCell(const Vec2<Uint8> &cell, Uint8 playerId);
  void Reset();

private:
  Uint8 m_filled_cells = 0;

  void drawCell(SDL_Data &sdl, Vec2f pos, Vec2f dim, Rgba cell_color) const;
  void renderCells(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const;
  void initGridState();
};
