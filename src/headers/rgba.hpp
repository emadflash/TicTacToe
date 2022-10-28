#pragma once

#include <SDL2/SDL_stdinc.h>

class Rgba {
public:
  Uint8 x, y, z, a;
  Rgba() = default;
  Rgba(Uint8 x, Uint8 y, Uint8 z, Uint8 a) : x(x), y(y), z(z), a(a) {}
};
