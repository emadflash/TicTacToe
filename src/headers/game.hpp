#pragma once

#include "SDL2/SDL.h"

#include <memory>
#include <unordered_map>
#include <vector>

#include "grid.hpp"

class Game {
public:
  std::array<Rgba, 2> playerMap = {
      Rgba(0x00, 0xee, 0x00, 0x00),
      Rgba(0xff, 0xee, 0x00, 0x00),
  };

  bool m_isRunning;
  Grid m_grid;
  Uint8 m_playerTurn = 0;
  bool m_isOver{false}, m_isDraw{false};

  explicit Game(const char *title, int width, int height, Uint8 gridSize);
  ~Game();

  void Render();
  void ProcessEvent();
  void Update();
  void Run();

private:
  SDL_Data m_sdl;
  Vec2<int> m_clickPos;
  bool m_isLCTRLPressed;

  void initGameState();
  bool hasPlayerWon(const Vec2<Uint8> &cellPos, const Uint8 &playerId);
  void reset();
  inline void washBackground() const {
    SDL_SetRenderDrawColor(m_sdl.m_renderer, 0x02, 0x00, 0x14, 0x00);
    SDL_RenderClear(m_sdl.m_renderer);
  }
};
