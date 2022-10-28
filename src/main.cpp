#include "SDL2/SDL.h"
#include <memory>
#include <string>
#include <vector>

#include "headers/common.hpp"
#include "headers/game.hpp"
#include "headers/platform.hpp"

int main() {
  auto platform = new Platform("Tic Tac Toe", 960, 640);
  if (!platform->isRunning) {
    ERR("Exiting due to failure...");
    return -1;
  }

  auto game = new Game(3);

  platform->ClearBackground();

  while (platform->isRunning) {
    platform->ClearBackground();

    while (SDL_PollEvent(&platform->event)) {
      platform->ProcessEvent();
      game->ProcessEvent(platform);
    }

    game->Update(platform);
    game->Render(platform);

    platform->Render();
  }

  delete game;
  delete platform;

  return 0;
}
