#pragma once
#include "stdafx.h"

#include <iostream>

// A 2d vector.
struct Vector2 {
  Vector2() {}
  Vector2(int r, int c) : r(r), c(c) {}

  // Manhattan distance
  int DistTo(const Vector2& other) const {
    return std::abs(r - other.r) + std::abs(c - other.c);
  }

  Vector2 operator+(const Vector2& other) const {
    return Vector2(r + other.r, c + other.c);
  }
  Vector2 operator-(const Vector2& other) const {
    return Vector2(r - other.r, c - other.c);
  }
  Vector2 operator*(int mul) const {
    return Vector2(r * mul, c * mul);
  }
  void operator=(const Vector2& other) {
    r = other.r;
    c = other.c;
    return;
  }
  bool operator==(const Vector2& other) const {
    return (r == other.r) && (c == other.c);
  }
  bool operator!=(const Vector2& other) const {
    return !(*this == other);
  }
  friend std::ostream& operator<< (std::ostream &out, const Vector2& vec) {
    out << "[" << vec.r << ", " << vec.c << "]";
    return out;
  }

  int r;
  int c;
};
typedef std::unordered_set<Vector2> Vector2Set;
typedef std::vector<Vector2> Vector2List;

namespace std {
  template <>
  struct hash<Vector2> {
    size_t operator()(const Vector2& v) const {
      // Cantor pairing; probably an overkill
      return (size_t)(0.5 * (v.r + v.c) * (v.r + v.c + 1) + v.c);
    }
  };
}
