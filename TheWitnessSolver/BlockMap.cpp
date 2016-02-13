#include "BlockMap.h"

Block& BlockMap::GetBlock(int r, int c) {
  assert(ValidCoord(Vector2(r, c)));
  return m_BlockMatrix[r][c];
}

Block& BlockMap::GetBlock(const Vector2& vec) {
  assert(ValidCoord(vec));
  return m_BlockMatrix[vec.r][vec.c];
}

void BlockMap::Reset(int row, int col) {
  // The min size of node matrix is 1x1
  assert(row > 0 && col > 0);

  // Set the size of block matrix
  m_BlockMatrix.clear();
  m_BlockMatrix.resize(row - 1, std::vector<Block>(col - 1));

  // Initialize all the blocks
  for (int r = 0; r < row - 1; r++) {
    for (int c = 0; c < col - 1; c++) {
      Block& currBlock = m_BlockMatrix[r][c];
      currBlock.coord = Vector2(r, c);
    }
  }

  // Reset the neighbors of blocks
  ResetConnectivity();
}

void BlockMap::ResetConnectivity() {
  for (int r = 0; r < Rows(); r++) {
    for (int c = 0; c < Cols(); c++) {
      Block& currBlock = m_BlockMatrix[r][c];

      // Set reachable neighbors
      currBlock.neighborSet.clear();
      Vector2 lCoord(r, c - 1);
      Vector2 rCoord(r, c + 1);
      Vector2 tCoord(r - 1, c);
      Vector2 bCoord(r + 1, c);
      if (ValidCoord(lCoord)) currBlock.neighborSet.insert(&GetBlock(lCoord));
      if (ValidCoord(rCoord)) currBlock.neighborSet.insert(&GetBlock(rCoord));
      if (ValidCoord(tCoord)) currBlock.neighborSet.insert(&GetBlock(tCoord));
      if (ValidCoord(bCoord)) currBlock.neighborSet.insert(&GetBlock(bCoord));
    }
  }
}

void BlockMap::SetBlockType(const Vector2& vec, BlockType type) {
  Block& block = GetBlock(vec);
  block.type = type;
}