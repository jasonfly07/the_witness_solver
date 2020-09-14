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
  inline size_t Rows() const { return m_BlockMatrix.size(); }
  inline size_t Cols() const { return m_BlockMatrix[0].size(); }

  // Check the validity of a block coordinate
  inline bool ValidCoord(const Vector2& v) const { return ValidCoord(v.r, v.c); }
  inline bool ValidCoord(int r, int c) const {
    return (r >= 0 && c >= 0 && r < Rows() && c < Cols()) ? true : false;
  }

  // Set the type of a block
  void SetType(const Vector2& vec, BlockType type);

  // This will remove block2 from block1's neighborSet and vice versa
  void CutTie(const Vector2& vec1, const Vector2& vec2);

  // Given a seed block, return all the connected blocks as a single segment
  void Segment(Block& seed, BlockPtrSet& segment);
  void Segment(const Vector2& v, BlockPtrSet& segment) {
    Segment(GetBlock(v), segment);
  }

private:

  BlockMatrix m_BlockMatrix;
};