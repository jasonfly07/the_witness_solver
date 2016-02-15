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
      currBlock.neighborOffsets.clear();
      Vector2 lOffset(0, -1);
      Vector2 rOffset(0, 1);
      Vector2 tOffset(-1, 0);
      Vector2 bOffset(1, 0);
      if (ValidCoord(currBlock.coord + lOffset)) currBlock.neighborOffsets.insert(lOffset);
      if (ValidCoord(currBlock.coord + rOffset)) currBlock.neighborOffsets.insert(rOffset);
      if (ValidCoord(currBlock.coord + tOffset)) currBlock.neighborOffsets.insert(tOffset);
      if (ValidCoord(currBlock.coord + bOffset)) currBlock.neighborOffsets.insert(bOffset);
    }
  }
}

void BlockMap::SetType(const Vector2& vec, BlockType type) {
  Block& block = GetBlock(vec);
  block.type = type;
}

void BlockMap::CutTie(const Vector2& vec1, const Vector2& vec2) {
  // Check if vec1 & vec2 are adjacent
  if (vec1.DistTo(vec2) != 1) {
    return;
  }

  Block* blockPtr1 = &GetBlock(vec1);
  Block* blockPtr2 = &GetBlock(vec2);
  if (vec1.r > vec2.r || vec1.c > vec2.c) {
    blockPtr1 = &GetBlock(vec2);
    blockPtr2 = &GetBlock(vec1);
  }

  if (blockPtr1->coord.r == blockPtr2->coord.r) {
    blockPtr1->neighborOffsets.erase(Vector2(0, 1));
    blockPtr2->neighborOffsets.erase(Vector2(0, -1));
  }
  else {
    blockPtr1->neighborOffsets.erase(Vector2(1, 0));
    blockPtr2->neighborOffsets.erase(Vector2(-1, 0));
  }
}

void BlockMap::Segment(Block& seed, BlockPtrSet& segment) {
  std::stack<Block*> blockStack;
  blockStack.push(&seed);
  while (!blockStack.empty()) {
    Block& currBlock = *(blockStack.top());
    blockStack.pop();

    currBlock.visited = true;
    segment.insert(&currBlock);
    for (const auto& neighborCoord : currBlock.GetNeighborCoords()) {
      Block& neighbor = GetBlock(neighborCoord);
      if (!neighbor.visited) {
        blockStack.push(&neighbor);
      }
    }
  }
}

