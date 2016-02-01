#include "Puzzle.h"

#include <cstdlib>
#include <stack>

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

void Puzzle::Solve() {
  // Reset the visited map
  m_Visited.clear();
  m_Visited.resize(NodeRows(), std::vector<bool>(NodeCols()));
  for (int r = 0; r < NodeRows(); r++) {
    for (int c = 0; c < NodeCols(); c++) {
      m_Visited[r][c] = false;
    }
  }

  // Reset all the from nodes
  for (int r = 0; r < NodeRows(); r++) {
    for (int c = 0; c < NodeCols(); c++) {
      GetNode(Vector2(r, c)).from = NULL;
    }
  }

  // Create the stack for DFS
  std::stack<Node*> dfsStack;
  for (const auto& head : m_NodeHeads) {
    dfsStack.push(head);
  }

  // Perform DFS
  Node* finalNode = NULL;
  while (!dfsStack.empty()) {
    Node* currNode = dfsStack.top();
    dfsStack.pop();
    SetVisited(*currNode);

    if (currNode->isTail) {
      finalNode = currNode;
      break;
    }

    for (const auto& neighbor : currNode->neighborSet) {
      if (!HasVisited(*neighbor)) {
        neighbor->from = currNode;
        dfsStack.push(neighbor);
      }
    }
  }

  // Trace back the path
  std::stack<Node*> pathStack;
  Node* iter = finalNode;
  while (iter != NULL) {
    pathStack.push(iter);
    iter = iter->from;
  }
  m_Path.clear();
  while (!pathStack.empty()) {
    m_Path.push_back(pathStack.top());
    pathStack.pop();
  }
}
