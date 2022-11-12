#pragma once

#include "SDL.h"
#include "vec.hpp"

class SDL_Data {
public:
  std::string m_windowTitle;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  Vec2<int> m_windowDim;
  SDL_Event m_event;
  SDL_Rect m_backingRect;

  SDL_Data() = default;
  ~SDL_Data();
  bool Init(const char *title, int windowWidth, int windowHeight);
  void InitBackingRect(const Vec2f &startPos, const Vec2f &dim);
};
