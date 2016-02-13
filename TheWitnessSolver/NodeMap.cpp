#include "NodeMap.h"

Node& NodeMap::GetNode(int r, int c) {
  assert(ValidCoord(Vector2(r, c)));
  return m_NodeMatrix[r][c];
}

Node& NodeMap::GetNode(const Vector2& vec) {
  assert(ValidCoord(vec));
  return m_NodeMatrix[vec.r][vec.c];
}

void NodeMap::Reset(int row, int col) {
  // The min size of node matrix is 2x2
  assert(row > 1 && col > 1);

  // Set the size of node matrix
  m_NodeMatrix.clear();
  m_NodeMatrix.resize(row, std::vector<Node>(col));

  // Initialize all the nodes
  for (int r = 0; r < Rows(); r++) {
    for (int c = 0; c < Cols(); c++) {
      Node& currNode = m_NodeMatrix[r][c];
      currNode.coord = Vector2(r, c);
      if (IsOnEdge(currNode)) {
        currNode.onEdge = true;
      }
    }
  }

  // Reset the neighbors of nodes
  ResetConnectivity();
}

void NodeMap::ResetConnectivity() {
  for (int r = 0; r < Rows(); r++) {
    for (int c = 0; c < Cols(); c++) {
      Node& currNode = m_NodeMatrix[r][c];

      // Set reachable neighbors
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
}

void NodeMap::AddEssential(const Vector2& vec) {
  Node& node = GetNode(vec);
  node.isEssential = true;
}


bool NodeMap::IsOnEdge(const Node& node) const {
  if (node.coord.r == 0 || node.coord.c == 0 ||
      node.coord.r == Rows() - 1 || node.coord.c == Cols() - 1) {
    return true;
  }
  else return false;
}

void NodeMap::CutTie(const Vector2& vec1, const Vector2& vec2) {
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
