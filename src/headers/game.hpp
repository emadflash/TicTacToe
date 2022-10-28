#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>
#include <vector>

#include "grid.hpp"
#include "player.hpp"

class Game {
public:
  std::array<Rgba, 2> playerMap = {
      Rgba(0x00, 0xee, 0x00, 0x00),
      Rgba(0xff, 0xee, 0x00, 0x00),
  };

  Grid grid;
  Uint8 playerTurn = 0;
  bool isOver{false}, isDraw{false};

  explicit Game(Uint8 gridSize) : grid(Grid(gridSize, 0.10)) {}
  ~Game() {}

  void Render(Platform *platform) const;
  void ProcessEvent(Platform *platform);
  void Update(Platform *platform);

private:
  Vec2<int> clickPos;
  bool hasPlayerWon(Vec2<Uint8> cellPos, Uint8 playerId);
};
