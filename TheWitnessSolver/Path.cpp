#include "Path.h"

void Path::AddNode(Node* node) {
  // The first node HAS to be a head
  if (m_Path.size() == 0) {
    assert(node->isHead);
  }

  // There're 2 cases at start: head is on edge & not on edge
  // if the head is on edge, set touchCount to 1
  if (m_Path.size() == 0 && node->isHead && node->onEdge) {
    m_TouchCount = 1;
  }

  // TODO:
  // If leaveCount >= 1, and touchCount = leaveCount + 1
  // in the next step, a segment will be created
  if (m_Segmenting && m_LeaveCount >= 1 && m_TouchCount == m_LeaveCount + 1) {
    m_Segmenting = false;

    // Compute the node coord that's on the opposite side of the current step
    Vector2 currCoord = node->coord;
    Vector2 prevCoord = m_Path.end()[-1]->coord;
    Vector2 oppositeCoord = prevCoord * 2 - currCoord;

    // The block for seeding the segment will touch the side formed by
    // prevVec2 & oppositeVec2
    Vector2 seedBlockCoord;
    Side seedSide(&m_PuzzlePtr->GetNode(prevCoord), &m_PuzzlePtr->GetNode(oppositeCoord));
    if (seedSide.IsHorizontal()) {
      if (seedSide.node1->coord.r == 0) {
        seedBlockCoord = seedSide.node1->coord;
      }
      else {
        seedBlockCoord = seedSide.node1->coord - Vector2(1, 0);
      }
    }
    else {
      if (seedSide.node1->coord.c == 0) {
        seedBlockCoord = seedSide.node1->coord;
      }
      else {
        seedBlockCoord = seedSide.node1->coord - Vector2(0, 1);
      }
    }
    std::cout << "a segment is formed with block seed " << seedBlockCoord << std::endl;
  }

  // Cut the tie between 2 blocks if necessary
  if (m_Path.size() > 0) {
    CutBlockTie(*node, *(m_Path.end()[-1]));
  }

  // See if this step is leaving the edge
  if (m_Path.size() > 0) {
    if (!(node->onEdge) && m_Path.end()[-1]->onEdge) {
      m_LeaveCount++;
      m_Segmenting = true;
    }
  }

  // See if this step is touching the edge
  if (m_Path.size() > 0) {
    if (node->onEdge && !(m_Path.end()[-1]->onEdge)) {
      m_TouchCount++;
    }
  }

  // Finally, insert the node into relevant containers
  m_VisitedNodes.insert(node);
  m_Path.push_back(node);
  if (node->isEssential) m_VisitedEssentialNodes.insert(node);
  if (node->isTail)      m_VisitedTails.insert(node);
}

void Path::Print() const {
  std::cout << "touch = " << m_TouchCount;
  std::cout << ", leave = " << m_LeaveCount << std::endl;
  std::cout << "path : ";
  for (const auto& node : m_Path) {
    std::cout << node->coord << " ";
  }
  std::cout << std::endl;
}

//void Path::ProcessSegment() {
//
//}

void Path::CutBlockTie(const Node& node1, const Node& node2) {

  // No need to proceed if side is on the border
  if (node1.coord.r == 0 && node2.coord.r == 0) return;
  if (node1.coord.c == 0 && node2.coord.c == 0) return;
  if (node1.coord.r == m_PuzzlePtr->NodeRows() - 1 && node2.coord.r == m_PuzzlePtr->NodeRows() - 1) return;
  if (node1.coord.c == m_PuzzlePtr->NodeCols() - 1 && node2.coord.c == m_PuzzlePtr->NodeCols() - 1) return;

  // Case 1: side is vertical
  if (node1.coord.c == node2.coord.c) {
    int R = std::min(node1.coord.r, node2.coord.r);
    int C = node1.coord.c;
    Block& block1 = m_BlockMap.GetBlock(R, C - 1);
    Block& block2 = m_BlockMap.GetBlock(R, C);
    block1.neighborSet.erase(&block2);
    block2.neighborSet.erase(&block1);
  }
  // Case 2: side is horizontal
  else if (node1.coord.r == node2.coord.r) {
    int R = node1.coord.r;
    int C = std::min(node1.coord.c, node2.coord.c);
    Block& block1 = m_BlockMap.GetBlock(R - 1, C);
    Block& block2 = m_BlockMap.GetBlock(R, C);
    block1.neighborSet.erase(&block2);
    block2.neighborSet.erase(&block1);
  }
}
