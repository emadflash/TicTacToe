#include "headers/game.hpp"
#include "headers/common.hpp"
#include "headers/platform.hpp"

#include <SDL2/SDL_mouse.h>

void Game::Render(Platform *platform) const {
  grid.Render(platform, playerMap);
}

bool Game::hasPlayerWon(const Vec2<Uint8> &cellPos, const Uint8 &playerId) {
  auto checkRow = [&]() {
    for (int i = 0; i < grid.size; ++i) {
      if (grid.cells[i][cellPos.y] != playerId) return false;
    }
    return true;
  };

  auto checkCol = [&]() {
    for (int i = 0; i < grid.size; ++i) {
      if (grid.cells[cellPos.x][i] != playerId) return false;
    }
    return true;
  };

  auto checkDiag = [&]() {
    if (cellPos.x == cellPos.y) {
      for (int i = 0; i < grid.size; ++i) {
        if (grid.cells[i][i] != playerId) return false;
      }
      return true;
    }
    return false;
  };

  auto checkAntiDiag = [&]() {
    if (cellPos.x + cellPos.y == grid.size - 1) {
      for (int i = 0; i < grid.size; ++i) {
        if (grid.cells[i][grid.size - i - 1] != playerId) return false;
      }
      return true;
    }
    return false;
  };

  return bool(checkRow() || checkCol() || checkDiag() || checkAntiDiag());
}

void Game::ProcessEvent(Platform *platform) {
  switch (platform->event.type) {
  case SDL_KEYDOWN: {
    if (platform->event.key.keysym.sym == SDLK_r && platform->lCtrlPressed) {
      INFO("Resetting game...");
      reset();
    }
  } break;

  case SDL_MOUSEBUTTONDOWN: {
    if (!isOver) {
      if (platform->event.button.button == SDL_BUTTON_LEFT) {
        SDL_GetMouseState(&clickPos.x, &clickPos.y);

        if (grid.ContainsPosition(clickPos)) {
          auto cell = grid.GetCellFromClickPosition(clickPos);
          grid.FillCell(cell, playerTurn);

          if (hasPlayerWon(cell, playerTurn)) {
            isOver = true;
            isDraw = false;
            INFO("Player %d Won", playerTurn);
          } else {
            if (grid.IsFull()) {
              isOver = true;
              isDraw = true;
              INFO("Game draw. No one won. Try Again!", playerTurn);
            }
            playerTurn = (playerTurn == 1) ? 0 : 1;
          }
        }
      }
    }
  } break;
  }
}

void Game::Update(Platform *platform) {
  grid.Update(platform);
}

void Game::initGameState() {
  playerTurn = 0;
  isOver = isDraw = false;
}

void Game::reset() {
  initGameState();
  grid.Reset();
}
