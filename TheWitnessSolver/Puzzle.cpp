#include "Puzzle.h"

void Puzzle::ResetPuzzle(int nodeRow, int nodeCol) {
  assert(nodeRow > 1 && nodeCol > 1);

  m_NodeMap.Reset(nodeRow, nodeCol);
  m_BlockMap.Reset(nodeRow - 1, nodeCol - 1);

  // Reset all auxiliary containers
  m_NodeHeads.clear();
  m_NodeTails.clear();
  m_NodeEssentials.clear();
  m_SideEssentials.clear();

  m_HasBlackWhiteBlocks = false;
}

void Puzzle::AddHead(const Vector2& vec) {
  // If vec is already a head, no need to proceed
  if (GetNode(vec).isHead) return;

  // If vec is already a tail, remove it from m_NodeTails first
  if (GetNode(vec).isTail) m_NodeTails.erase(&GetNode(vec));

  m_NodeHeads.insert(&GetNode(vec));
  GetNode(vec).isHead = true;
}

void Puzzle::AddTail(const Vector2& vec) {
  // If vec is already a tail, no need to proceed
  if (GetNode(vec).isTail) return;

  // If vec is already a head, remove it from m_NodeHeads first
  if (GetNode(vec).isHead) m_NodeHeads.erase(&GetNode(vec));

  m_NodeTails.insert(&GetNode(vec));
  GetNode(vec).isTail = true;
}

void Puzzle::AddNodeObstacle(const Vector2& vec1, const Vector2& vec2) {
  m_NodeMap.CutTie(vec1, vec2);
}

void Puzzle::AddEssentialNode(const Vector2& vec) {
  Node& node = GetNode(vec);
  node.isEssential = true;
  m_NodeEssentials.insert(&node);
}

void Puzzle::AddEssentialSide(const Vector2& vec1, const Vector2& vec2) {
  m_SideEssentials.insert(Side(&GetNode(vec1), &GetNode(vec2)));
}

void Puzzle::SetBlockType(const Vector2& vec, BlockType type) {
  m_BlockMap.SetType(vec, type);
}

bool Puzzle::CheckBlackWhiteBlocks() {
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      const Block& currBlock = GetBlock(r, c);
      if ((currBlock.type == Black) || (currBlock.type == White)) {
        m_HasBlackWhiteBlocks = true;
        return true;
      }
    }
  }

  m_HasBlackWhiteBlocks = false;
  return false;
}

void Puzzle::PreprocessBlackWhiteBlocks() {
  // For every block [r, c], process the sides (if valid):
  // 1. between [r, c] and [r, c + 1]
  // 2. between [r, c] and [r + 1, c]
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      const Block& currBlock = GetBlock(r, c);

      // 1. [r, c + 1]
      if (ValidBlockCoord(r, c + 1)) {
        const Block& rightBlock = GetBlock(r, c + 1);
        if ((currBlock.type == White && rightBlock.type == Black) ||
            (currBlock.type == Black && rightBlock.type == White)) {
          m_SideEssentials.insert(Side(&GetNode(r, c + 1), &GetNode(r + 1, c + 1)));
        }
      }

      // 2. [r + 1, c]
      if (ValidBlockCoord(r + 1, c)) {
        const Block& bottomBlock = GetBlock(r + 1, c);
        if ((currBlock.type == White && bottomBlock.type == Black) ||
            (currBlock.type == Black && bottomBlock.type == White)) {
          m_SideEssentials.insert(Side(&GetNode(r + 1, c), &GetNode(r + 1, c + 1)));
        }
      }
    }
  }
}

void Puzzle::CreateDisplayMatrix(DisplayMatrix& display) {
  display.clear();
  display.resize(NodeRows() * 2 - 1, std::vector<char>(NodeCols() * 2 - 1));

  for (int r = 0; r < display.size(); r++) {
    for (int c = 0; c < display[0].size(); c++) {
      display[r][c] = ' ';
    }
  }

  // Essential nodes
  for (const auto& essentialNode : m_NodeEssentials) {
    Vector2 eCoord = essentialNode->coord;
    display[eCoord.r * 2][eCoord.c * 2] = 'e';
  }

  // Heads & tails
  for (const auto& head : m_NodeHeads) {
    Vector2 hCoord = head->coord;
    display[hCoord.r * 2][hCoord.c * 2] = 'H';
  }
  for (const auto& tail : m_NodeTails) {
    Vector2 tCoord = tail->coord;
    display[tCoord.r * 2][tCoord.c * 2] = 'T';
  }

  // Blocks
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      Block& currBlock = GetBlock(r, c);
      if (currBlock.type == Black) {
        display[r * 2 + 1][c * 2 + 1] = 'B';
      }
      else if (currBlock.type == White) {
        display[r * 2 + 1][c * 2 + 1] = 'W';
      }
      else {
        display[r * 2 + 1][c * 2 + 1] = 'O';
      }
    }
  }
}

void Puzzle::Draw() {
  DisplayMatrix display;
  CreateDisplayMatrix(display);
  // Drawing
  for (int r = 0; r < display.size(); r++) {
    for (int c = 0; c < display[0].size(); c++) {
      std::cout << display[r][c];
    }
    std::cout << std::endl;
  }
}
