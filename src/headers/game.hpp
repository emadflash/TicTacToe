#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "grid.hpp"
#include "player.hpp"

class Game {
public:
  Grid grid;
  std::vector<Player> players;

  explicit Game(Uint8 cellCount) : grid(Grid(cellCount)) {}
  ~Game() {}

  void Render(Platform *platform) const;
  void ProcessEvent(Platform *platform);
  void Update(Platform *platform);

private:
  int xClick, yClick;
};
