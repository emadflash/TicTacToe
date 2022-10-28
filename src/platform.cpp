#include "headers/platform.hpp"
#include "headers/appdata.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <memory>

Platform::Platform(const char *title, int width, int height)
    : windowWidth(width), windowHeight(height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    isRunning = false;
    return;
  }

  window = SDL_CreateWindow(title, -1, -1, width, height, SDL_WINDOW_RESIZABLE);
  if (!window) {
    isRunning = false;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    isRunning = false;
    return;
  }

  appdata = std::make_unique<AppData>();
  isRunning = true;
  return;
}

Platform::~Platform() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Platform::ProcessEvent() {
  switch (event.type) {
  case SDL_QUIT: isRunning = false; break;
  case SDL_WINDOWEVENT: {
    switch (event.window.event) {
    case SDL_WINDOWEVENT_RESIZED: {
      SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    } break;
    }
  } break;

  case SDL_KEYDOWN: {
    switch (event.key.keysym.sym) {
    case SDLK_q: isRunning = false; break;
    }
  } break;
  }
}

void Platform::ClearBackground() const {
  SDL_SetRenderDrawColor(renderer, 0x02, 0x00, 0x14, 0x00);
  SDL_RenderClear(renderer);
}

void Platform::Update() {
}

void Platform::Render() const {
  SDL_RenderPresent(renderer);
  SDL_Delay(10);
}

void Platform::InitBackingRect(Vec2f startPos, Vec2f dim) {
  backingRect.x = startPos.x;
  backingRect.y = startPos.y;
  backingRect.w = dim.x;
  backingRect.h = dim.y;
}