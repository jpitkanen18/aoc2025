#pragma once
#include <string>
#include <typeinfo>
#include <vector>

using StringVector = std::vector<std::string>;

struct Vec2 {
  long x, y;
  Vec2(long x, long y) : x(x), y(y) {}

  friend bool operator==(Vec2 lhs, Vec2 rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Vec2& operator+=(const Vec2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }
};

class Strict {
};

class Lean {
};

template <typename Strictness = Strict>
struct Vec3 {
  long x, y, z;
  Vec3(long x, long y, long z) : x(x), y(y), z(z) {}

  friend bool operator==(Vec3 lhs, Vec3 rhs) {
    if (typeid(Strictness) == typeid(Strict))
      return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    else
      return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Vec3& operator+=(const Vec3& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
  }
};
