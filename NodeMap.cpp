#include "NodeMap.h"

Node& NodeMap::GetNode(int r, int c) {
  ASSERT(ValidCoord(Vector2(r, c)));
  return m_NodeMatrix[r][c];
}

Node& NodeMap::GetNode(const Vector2& vec) {
  ASSERT(ValidCoord(vec));
  return m_NodeMatrix[vec.r][vec.c];
}

void NodeMap::Reset(int row, int col) {
  // The min size of node matrix is 2x2
  ASSERT((row > 1 && col > 1));

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
      currNode.neighborOffsets.clear();
      Vector2 lOffset( 0, -1);
      Vector2 rOffset( 0,  1);
      Vector2 tOffset(-1,  0);
      Vector2 bOffset( 1,  0);
      if (ValidCoord(currNode.coord + lOffset)) currNode.neighborOffsets.insert(lOffset);
      if (ValidCoord(currNode.coord + rOffset)) currNode.neighborOffsets.insert(rOffset);
      if (ValidCoord(currNode.coord + tOffset)) currNode.neighborOffsets.insert(tOffset);
      if (ValidCoord(currNode.coord + bOffset)) currNode.neighborOffsets.insert(bOffset);
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
  if (node1.coord.DistTo(node2.coord) != 1) {
    return;
  }

  // HACK: use a side to re-arrange the order of nodes
  Side tempSide(&node1, &node2);
  if (tempSide.IsHorizontal()) {
    node1.neighborOffsets.erase(Vector2(0,  1));
    node2.neighborOffsets.erase(Vector2(0, -1));
  }
  else {
    node1.neighborOffsets.erase(Vector2( 1, 0));
    node2.neighborOffsets.erase(Vector2(-1, 0));
  }
}
