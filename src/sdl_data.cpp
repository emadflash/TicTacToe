#include "headers/sdl_data.hpp"
#include "headers/common.hpp"

bool SDL_Data::Init(const char *title, int windowWidth, int windowHeight) {
  m_windowDim = Vec2<int>(windowWidth, windowHeight);
  m_windowTitle = std::string(title);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    ERR("Couldn't initialize SDL. SDL Error: %s", SDL_GetError());
    return false;
  }

#ifdef Debug
  m_windowTitle += " | DEBUG MODE";
#endif

  m_window = SDL_CreateWindow(m_windowTitle.c_str(), -1, -1, m_windowDim.x, m_windowDim.y,
                              SDL_WINDOW_RESIZABLE);
  if (!m_window) {
    ERR("Couldn't create SDL_Window, SDL Error:", SDL_GetError());
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  if (!m_renderer) {
    ERR("Couldn't create SDL_Renderer, SDL Error:", SDL_GetError());
    return false;
  }

  DEBUG("SDL initialized");
  return true;
}

SDL_Data::~SDL_Data() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
  DEBUG("SDL data destroyed");
}

void SDL_Data::InitBackingRect(const Vec2f &startPos, const Vec2f &dim) {
  m_backingRect.x = startPos.x;
  m_backingRect.y = startPos.y;
  m_backingRect.w = dim.x;
  m_backingRect.h = dim.y;
}
