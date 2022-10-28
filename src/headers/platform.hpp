#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory>

#include "appdata.hpp"
#include "vec.hpp"

class Platform {
public:
  bool isRunning;
  SDL_Renderer *renderer;
  SDL_Window *window;
  int windowWidth, windowHeight;
  SDL_Event event;
  SDL_Rect backingRect;
  std::unique_ptr<AppData> appdata;
  bool lCtrlPressed;

  Platform(const char *title, int width, int height);
  ~Platform();

  void ProcessEvent();
  void ClearBackground() const;
  void Update();
  void Render() const;
  void InitBackingRect(Vec2f startPos, Vec2f dim);
};
