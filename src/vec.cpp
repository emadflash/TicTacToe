#include "headers/vec.hpp"

template <typename T> std::ostream &operator<<(std::ostream &os, const Vec2<T> &v) {
  os << '(' << v.x << ", " << v.y << ')';
  return os;
}

std::ostream &operator<<(std::ostream &os, const Vec2f &v) {
  os << '(' << v.x << ", " << v.y << ')';
  return os;
}
