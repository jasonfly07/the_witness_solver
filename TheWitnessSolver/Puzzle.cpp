#include "Puzzle.h"

#include <cstdlib>

void Puzzle::ResetPuzzle(int numRow, int numCol) {
  assert(numRow > 0 && numCol > 0);
  m_NodeMatrix.clear();
  m_NodeMatrix.resize(numRow, std::vector<Node>(numCol));

  // Set the reachable neighbor for every node
  for (int r = 0; r < numRow; r++) {
    for (int c = 0; c < numCol; c++) {
      Node& currNode = m_NodeMatrix[r][c];
      currNode.coord = Vector2(r, c);

      currNode.neighborSet.clear();
      Vector2 lCoord(r, c - 1);
      Vector2 rCoord(r, c + 1);
      Vector2 tCoord(r - 1, c);
      Vector2 bCoord(r + 1, c);
      if (ValidCoord(lCoord)) currNode.neighborSet.insert(&GetNode(lCoord));
      if (ValidCoord(rCoord)) currNode.neighborSet.insert(&GetNode(rCoord));
      if (ValidCoord(tCoord)) currNode.neighborSet.insert(&GetNode(tCoord));
      if (ValidCoord(bCoord)) currNode.neighborSet.insert(&GetNode(bCoord));
    }
  }

  // Reset heads & tails
  m_NodeHeads.clear();
  m_NodeTails.clear();
}

void Puzzle::AddHead(const Vector2& vec) {
  assert(ValidCoord(vec));
  // If vec is already a head, no need to proceed
  if (GetNode(vec).isHead) return;

  // If vec is already a tail, remove it from m_NodeTails first
  if (GetNode(vec).isTail) m_NodeTails.erase(&GetNode(vec));

  m_NodeHeads.insert(&GetNode(vec));
  GetNode(vec).isHead = true;
}

void Puzzle::AddTail(const Vector2& vec) {
  assert(ValidCoord(vec));
  // If vec is already a tail, no need to proceed
  if (GetNode(vec).isTail) return;

  // If vec is already a head, remove it from m_NodeHeads first
  if (GetNode(vec).isHead) m_NodeHeads.erase(&GetNode(vec));

  m_NodeTails.insert(&GetNode(vec));
  GetNode(vec).isTail = true;
}

void Puzzle::AddObstacle(const Vector2& vec1, const Vector2& vec2) {
  Node& node1 = GetNode(vec1);
  Node& node2 = GetNode(vec2);

  // Check if node1 & node2 are adjacent
  // TODO: this is probably unnecessary
  if (node1.neighborSet.count(&node2) == 0 ||
      node2.neighborSet.count(&node1) == 0) {
    return;
  }

  node1.neighborSet.erase(&node2);
  node2.neighborSet.erase(&node1);
}
