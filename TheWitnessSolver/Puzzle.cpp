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
