#include "headers/game.hpp"
#include "headers/common.hpp"

Game::Game(const char *title, int width, int height, Uint8 gridSize)
    : m_grid(Grid(gridSize, 0.20)) {
  if (!m_sdl.Init(title, width, height)) {
    m_isRunning = false;
    ERR("Cound't initialize sdl. Exiting...");
    return;
  }

  m_isRunning = true;
  initGameState();
  return;
}

Game::~Game() {
  DEBUG("Cleanup successful");
}

void Game::initGameState() {
  m_playerTurn = 0;
  m_isOver = m_isDraw = false;
}

void Game::reset() {
  initGameState();
  m_grid.Reset();
}

bool Game::hasPlayerWon(const Vec2<Uint8> &cellPos, const Uint8 &playerId) {
  auto checkRow = [&]() {
    for (int i = 0; i < m_grid.m_size; ++i) {
      if (m_grid.m_cells[i][cellPos.y] != playerId) return false;
    }
    return true;
  };

  auto checkCol = [&]() {
    for (int i = 0; i < m_grid.m_size; ++i) {
      if (m_grid.m_cells[cellPos.x][i] != playerId) return false;
    }
    return true;
  };

  auto checkDiag = [&]() {
    if (cellPos.x == cellPos.y) {
      for (int i = 0; i < m_grid.m_size; ++i) {
        if (m_grid.m_cells[i][i] != playerId) return false;
      }
      return true;
    }
    return false;
  };

  auto checkAntiDiag = [&]() {
    if (cellPos.x + cellPos.y == m_grid.m_size - 1) {
      for (int i = 0; i < m_grid.m_size; ++i) {
        if (m_grid.m_cells[i][m_grid.m_size - i - 1] != playerId) return false;
      }
      return true;
    }
    return false;
  };

  return bool(checkRow() || checkCol() || checkDiag() || checkAntiDiag());
}

void Game::ProcessEvent() {
  switch (m_sdl.m_event.type) {
  case SDL_QUIT: m_isRunning = false; break;
  case SDL_WINDOWEVENT: {
    switch (m_sdl.m_event.window.event) {
    case SDL_WINDOWEVENT_RESIZED: {
      SDL_GetWindowSize(m_sdl.m_window, &m_sdl.m_windowDim.x, &m_sdl.m_windowDim.y);
    } break;
    }
  } break;

  case SDL_KEYDOWN: {
    switch (m_sdl.m_event.key.keysym.sym) {
    case SDLK_q: m_isRunning = false; break;
    case SDLK_LCTRL: m_isLCTRLPressed = true; break;
    case SDLK_r: {
      if (m_isLCTRLPressed) {
        INFO("Resetting game...");
        reset();
      }
    } break;
    }
  } break;

  case SDL_KEYUP: {
    switch (m_sdl.m_event.key.keysym.sym) {
    case SDLK_LCTRL: m_isLCTRLPressed = false; break;
    }
    break;
  }

  case SDL_MOUSEBUTTONDOWN: {
    if (!m_isOver) {
      if (m_sdl.m_event.button.button == SDL_BUTTON_LEFT) {
        SDL_GetMouseState(&m_clickPos.x, &m_clickPos.y);

        if (m_grid.ContainsPosition(m_clickPos)) {
          auto cell = m_grid.GetCellFromClickPosition(m_clickPos);
          m_grid.FillCell(cell, m_playerTurn);

          if (hasPlayerWon(cell, m_playerTurn)) {
            m_isOver = true;
            m_isDraw = false;
            INFO("Player %d Won", m_playerTurn);
          } else {
            if (m_grid.IsFull()) {
              m_isOver = true;
              m_isDraw = true;
              INFO("Game draw. No one won. Try Again!", m_playerTurn);
            }
            m_playerTurn = (m_playerTurn == 1) ? 0 : 1;
          }
        }
      }
    }
  } break;
  }
}

void Game::Update() {
  m_grid.Update(m_sdl);
}

void Game::Render() {
  m_grid.Render(m_sdl, playerMap);
  SDL_RenderPresent(m_sdl.m_renderer);
}

void Game::Run() {
  Uint32 fps = 60;
  Uint32 frameTime = 0;
  Uint32 elapsed = 0;

  while (m_isRunning) {
    elapsed = SDL_GetTicks();
    washBackground();

    while (SDL_PollEvent(&m_sdl.m_event)) {
      ProcessEvent();
    }

    Update();
    Render();

    frameTime = SDL_GetTicks() - elapsed;
    if (1000 / fps > frameTime) {
      SDL_Delay((1000 / fps) - frameTime);
    }
  }

  SDL_Delay(20);
}
