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
  m_BlockMatrix.resize(row, std::vector<Block>(col));

  // Initialize all the blocks
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < col; c++) {
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

void BlockMap::SetType(const Vector2& vec, BlockType type) {
  Block& block = GetBlock(vec);
  block.type = type;
}

void BlockMap::CutTie(const Vector2& vec1, const Vector2& vec2) {
  Block& block1 = GetBlock(vec1);
  Block& block2 = GetBlock(vec2);

  // Check if block1 & block2 are adjacent
  // TODO: this is probably unnecessary
  if (block1.neighborSet.count(&block2) == 0 ||
    block2.neighborSet.count(&block1) == 0) {
    return;
  }

  block1.neighborSet.erase(&block2);
  block2.neighborSet.erase(&block1);
}
