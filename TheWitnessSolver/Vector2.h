#pragma once
#include "stdafx.h"

#include <iostream>

// A 2d vector.
struct Vector2 {
  Vector2() {}
  Vector2(int r, int c) : r(r), c(c) {}

  Vector2 operator+(const Vector2& other) {
    return Vector2(r + other.r, c + other.c);
  }
  Vector2 operator-(const Vector2& other) {
    return Vector2(r - other.r, c - other.c);
  }
  void operator=(const Vector2& other) {
    r = other.r;
    c = other.c;
    return;
  }
  bool operator==(const Vector2& other) {
    return (r == other.r) && (c == other.c);
  }
  bool operator!=(const Vector2& other) {
    return !(*this == other);
  }
  friend std::ostream& operator<< (std::ostream &out, const Vector2& vec) {
    out << "[" << vec.r << ", " << vec.c << "]";
    return out;
  }

  int r;
  int c;
};
