#include "headers/game.hpp"
#include "headers/platform.hpp"

#include <SDL2/SDL_mouse.h>

void Game::Render(Platform *platform) const {
  grid.Render(platform);
}

void Game::ProcessEvent(Platform *platform) {
  switch (platform->event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (platform->event.button.button == SDL_BUTTON_LEFT) {
      SDL_GetMouseState(&xClick, &yClick);
      grid.FillCell(xClick, yClick);
    }
  } break;
  }
}

void Game::Update(Platform *platform) {
  grid.Update(platform);
}
