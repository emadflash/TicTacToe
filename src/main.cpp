#include "SDL2/SDL.h"
#include <memory>
#include <string>
#include <vector>

#include "headers/common.hpp"
#include "headers/game.hpp"

int main() {
  Game game("Tic Tac Toe", 960, 640);
  if (!game.m_isRunning) {
    ERR("Exiting due to failure...");
    return -1;
  }

  game.Run();
  return 0;
}
