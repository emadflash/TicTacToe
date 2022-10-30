#include "headers/grid.hpp"
#include "headers/common.hpp"
#include "headers/rgba.hpp"
#include "headers/sdl_data.hpp"

#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"

void Grid::initGridState() {
  for (int i = 0; i < m_size; ++i) {
    for (int j = 0; j < m_size; ++j) {
      m_cells[i][j] = -1;
    }
  }
  m_filled_cells = 0;
}

void Grid::Reset() {
  initGridState();
}

bool Grid::ContainsPosition(const Vec2<int> &clickPos) const {
  return bool(clickPos.x >= m_pos.x && clickPos.x <= m_pos.x + m_dim.x && clickPos.y >= m_pos.y &&
              clickPos.y <= m_pos.y + m_dim.y);
}

Vec2<Uint8> Grid::GetCellFromClickPosition(const Vec2<int> &clickPos) {
  DEBUG_ASSERT(ContainsPosition(clickPos));

  auto matchCol = [&]() -> Uint8 {
    for (int i = 0; i < m_size; ++i) {
      auto xDim = Vec2f(m_pos.x + i * m_cellWidth.x, m_pos.x + (i + 1) * m_cellWidth.x);
      if (clickPos.x > xDim.x && clickPos.x < xDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  auto matchRow = [&]() -> Uint8 {
    for (Uint8 i = 0; i < m_size; ++i) {
      auto yDim = Vec2f(m_pos.y + i * m_cellWidth.y, m_pos.y + (i + 1) * m_cellWidth.y);
      if (clickPos.y > yDim.x && clickPos.y < yDim.y) {
        return i;
      }
    }
    UNREACHABLE();
  };

  return Vec2<Uint8>(matchRow(), matchCol());
}

void Grid::FillCell(const Vec2<Uint8> &cell, Uint8 playerId) {
  if (m_cells[cell.x][cell.y] == -1) {
    m_cells[cell.x][cell.y] = playerId;
    m_filled_cells += 1;
  }
}

// Applies padding and then draws the cell
void Grid::drawCell(SDL_Data &sdl, Vec2f pos, Vec2f dim, Rgba cell_color) const {
  pos.x = pos.x + dim.x * m_cellPadding;
  pos.y = pos.y + dim.y * m_cellPadding;

  sdl.InitBackingRect(
      pos, Vec2f(dim.x - (dim.x * 2 * m_cellPadding), dim.y - (dim.y * 2 * m_cellPadding)));
  SDL_SetRenderDrawColor(sdl.m_renderer, cell_color.x, cell_color.y, cell_color.z, cell_color.a);
  SDL_RenderFillRect(sdl.m_renderer, &sdl.m_backingRect);
}

void Grid::renderCells(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const {
  for (Uint8 i = 1; i < 4; ++i) {
    for (Uint8 j = 1; j < 4; ++j) {
      auto id = m_cells[i - 1][j - 1];
      if (id != -1) {
        Vec2f pos(m_pos.x + j * m_cellWidth.x, m_pos.y + i * m_cellWidth.y);
        Vec2f dim(pos.x - (pos.x + m_cellWidth.x), pos.y - (pos.y + m_cellWidth.y));

        drawCell(sdl, pos, dim, playerMap[id]);
      }
    }
  }
}

void Grid::Render(SDL_Data &sdl, std::array<Rgba, 2> playerMap) const {
  SDL_SetRenderDrawColor(sdl.m_renderer, 0xff, 0xff, 0xff, 0x00);

  for (int i = 1; i < m_size; ++i) {
    SDL_RenderDrawLine(sdl.m_renderer, m_pos.x, m_pos.y + i * m_cellWidth.y, m_pos.x + m_dim.x,
                       m_pos.y + i * m_cellWidth.y); // horizontonal line
    SDL_RenderDrawLine(sdl.m_renderer, m_pos.x + i * m_cellWidth.x, m_pos.y,
                       m_pos.x + i * m_cellWidth.x,
                       m_pos.y + m_dim.y); // vertical line
  }

  renderCells(sdl, playerMap);
}
