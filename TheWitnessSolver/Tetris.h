#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"

// To recap:
// Square1x1, Square2x2,
// Line1x2, Line2x1,
// Line1x3, Line3x1,
// Line1x4, Line4x1,
// L2x2_0, L2x2_90, L2x2_180, L2x2_270,
// L3x2_0, L3x2_90, L3x2_180, L3x2_270,
// L2x3_0, L2x3_90, L2x3_180, L2x3_270,

// Used for constructing tetris blocks & retrieving relevant information
struct Tetris {
  Tetris(BlockType type) {
    switch (type) {
    case Square1x1:
      area = 1; boxArea = 1;
      boxRow = 1; boxCol = 1;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      break;
    case Square2x2:
      area = 4; boxArea = 4;
      boxRow = 2; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      break;

    case Line1x2:
      area = 2; boxArea = 2;
      boxRow = 1; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(0, 1));
      break;
    case Line1x3:
      area = 3; boxArea = 3;
      boxRow = 1; boxCol = 3;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(0, 2));
      shape.push_back(Vector2(0, 1));
      break;
    case Line1x4:
      area = 4; boxArea = 4;
      boxRow = 1; boxCol = 4;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(0, 3));
      shape.push_back(Vector2(0, 1));
      shape.push_back(Vector2(0, 2));
      break;

    case Line2x1:
      area = 2; boxArea = 2;
      boxRow = 2; boxCol = 1;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(1, 0));
      break;
    case Line3x1:
      area = 3; boxArea = 3;
      boxRow = 3; boxCol = 1;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(2, 0));
      shape.push_back(Vector2(1, 0));
      break;
    case Line4x1:
      area = 4; boxArea = 4;
      boxRow = 4; boxCol = 1;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(3, 0));
      shape.push_back(Vector2(1, 0));
      shape.push_back(Vector2(2, 0));
      break;

    case L2x2_0:
      area = 3; boxArea = 4;
      boxRow = 2; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(1, 1));
      shape.push_back(Vector2(1, 0));
      break;
    case L2x2_90:
      area = 3; boxArea = 4;
      boxRow = 2; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-1, 1));
      shape.push_back(Vector2( 0, 1));
      break;
    case L2x2_180:
      area = 3; boxArea = 4;
      boxRow = 2; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(1, 1));
      shape.push_back(Vector2(0, 1));
      break;
    case L2x2_270:
      area = 3; boxArea = 4;
      boxRow = 2; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-1, 1));
      shape.push_back(Vector2(-1, 0));
      break;

    case L3x2_0:
      area = 4; boxArea = 6;
      boxRow = 3; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(2, 1));
      shape.push_back(Vector2(1, 0));
      shape.push_back(Vector2(2, 0));
      break;
    case L3x2_90:
      area = 4; boxArea = 6;
      boxRow = 2; boxCol = 3;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-1, 2));
      shape.push_back(Vector2( 0, 1));
      shape.push_back(Vector2( 0, 2));
      break;
    case L3x2_180:
      area = 4; boxArea = 6;
      boxRow = 3; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(2, 1));
      shape.push_back(Vector2(0, 1));
      shape.push_back(Vector2(1, 1));
      break;
    case L3x2_270:
      area = 4; boxArea = 6;
      boxRow = 2; boxCol = 3;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-1, 2));
      shape.push_back(Vector2(-1, 0));
      shape.push_back(Vector2(-1, 1));
      break;

    case L2x3_0:
      area = 4; boxArea = 6;
      boxRow = 2; boxCol = 3;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(1, 2));
      shape.push_back(Vector2(1, 0));
      shape.push_back(Vector2(1, 1));
      break;
    case L2x3_90:
      area = 4; boxArea = 6;
      boxRow = 3; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-2, 1));
      shape.push_back(Vector2( 0, 1));
      shape.push_back(Vector2(-1, 1));
      break;
    case L2x3_180:
      area = 4; boxArea = 6;
      boxRow = 2; boxCol = 3;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2(0, 0));
      shape.push_back(Vector2(1, 2));
      shape.push_back(Vector2(0, 1));
      shape.push_back(Vector2(0, 2));
      break;
    case L2x3_270:
      area = 4; boxArea = 6;
      boxRow = 3; boxCol = 2;
      shape.clear(); shape.reserve(area);
      shape.push_back(Vector2( 0, 0));
      shape.push_back(Vector2(-2, 1));
      shape.push_back(Vector2(-1, 0));
      shape.push_back(Vector2(-2, 0));
      break;

    default:
      ASSERT(false);
      break;
    }
  }

  size_t area;

  // TODO: are these actually useful?
  size_t boxArea, boxRow, boxCol;

  // Starting from a seed, the list stores all the coord offset to construct a block
  // For example, L2x2_0 would be [0, 0], [0, 1], [1, 0]
  // (Heuristic) The order of the offsets are arranged so we always test the
  // farthest reach in the beginning, so we don't waste time growing the shape block-by-block
  Vector2List shape;
};