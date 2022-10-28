#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory>
#include <string>
#include <vector>

#include "headers/game.hpp"
#include "headers/platform.hpp"

int main() {
  auto platform = new Platform("Tic Tac Toe", 960, 640);
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

    platform->Update();
    platform->Render();
  }

  delete game;
  delete platform;

  return 0;
}
