#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"

class BlockMap {

public:

  // Reset everything
  void Reset(int row, int col);
  // Reset the neighbors of nodes
  void ResetConnectivity();

  // Getters
  Block& GetBlock(int r, int c);
  Block& GetBlock(const Vector2& vec);
  inline size_t Rows() { return m_BlockMatrix.size(); }
  inline size_t Cols() { return m_BlockMatrix[0].size(); }

  // Check the validity of a block coordinate
  inline bool ValidCoord(const Vector2& v) { return ValidCoord(v.r, v.c); }
  inline bool ValidCoord(int r, int c) {
    return (r >= 0 && c >= 0 && r < Rows() && c < Cols()) ? true : false;
  }

  // Set the type of a block
  void SetBlockType(const Vector2& vec, BlockType type);

private:

  BlockMatrix m_BlockMatrix;
};