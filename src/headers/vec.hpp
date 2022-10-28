#pragma once

#include <iostream>

template <typename T> class Vec2 {
public:
  T x = 0, y = 0;

  Vec2() = default;
  Vec2(T x, T y) : x(x), y(y) {}

  friend std::ostream &operator<<(std::ostream &os, const Vec2 &v);
};

class Vec2f {
public:
  float x = 0, y = 0;

  Vec2f() = default;
  Vec2f(float x, float y) : x(x), y(y) {}

  friend std::ostream &operator<<(std::ostream &os, const Vec2f &v);
};
