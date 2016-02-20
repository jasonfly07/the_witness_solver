#include "Path.h"

bool Path::AddNode(Node* node) {
  // The first node HAS to be a head
  if (m_Path.size() == 0) {
    assert(node->isHead);
  }

  // There're 2 cases at start: head is on edge & not on edge
  // if the head is on edge, set touchCount to 1
  if (m_Path.size() == 0 && node->isHead && node->onEdge) {
    m_TouchCount = 1;
  }

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

    // Perform segmentation with the seed
    BlockPtrSet segment;
    m_BlockMap.Segment(seedBlockCoord, segment);

    // Evalute this segment
    bool validPath = EvaluateSegment(segment);
    if (!validPath) return false;
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
    if (node->onEdge && !(m_Path.back()->onEdge)) {
      m_TouchCount++;
    }
  }

  // Finally, insert the node into relevant containers
  m_VisitedNodes.insert(node);
  if (m_Path.size() > 0) {
    m_VisitedSides.insert(Side(node, m_Path.back()));
  }
  m_Path.push_back(node);
  if (node->isEssential) m_VisitedEssentialNodes.insert(node);
  if (node->isTail)      m_VisitedTails.insert(node);
  return true;
}

void Path::Print() const {
  std::cout << "Path : ";
  for (const auto& node : m_Path) {
    std::cout << node->coord << " ";
  }
  std::cout << std::endl;
}

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
    m_BlockMap.CutTie(block1.coord, block2.coord);
  }
  // Case 2: side is horizontal
  else if (node1.coord.r == node2.coord.r) {
    int R = node1.coord.r;
    int C = std::min(node1.coord.c, node2.coord.c);
    Block& block1 = m_BlockMap.GetBlock(R - 1, C);
    Block& block2 = m_BlockMap.GetBlock(R, C);
    m_BlockMap.CutTie(block1.coord, block2.coord);
  }
}

bool Path::EvaluateSegment(const BlockPtrSet& segment) {
  // Are there black & white blocks mixed together?
  // If yes, return false immediately
  if (m_PuzzlePtr->HasBlackWhite()) {
    bool hasWhite = false;
    bool hasBlack = false;
    for (const auto& block : segment) {
      if (block->type == White) {
        hasWhite = true;
      }
      else if (block->type == Black) {
        hasBlack = true;
      }
      if (hasWhite && hasBlack) {
        return false;
      }
    }
  }

  // Find all the unvisited nodes in segment
  // TODO: right now we always perform this search,
  // but it's probably better to only run this if necessary
  NodePtrSet unvisitedNodes;
  for (const auto& blockPtr : segment) {
    Vector2 blockCoord = blockPtr->coord;
    for (Vector2 offset : {Vector2(0, 0), Vector2(0, 1), Vector2(1, 0), Vector2(1, 1)}) {
      Vector2 nodeCoord = blockCoord + offset;
      if (!HasVisitedNode(nodeCoord)) {
        unvisitedNodes.insert(&m_PuzzlePtr->GetNode(nodeCoord));
      }
    }
  }

  // Are there unvisited essential nodes?
  // If yes, return false immediately
  if (m_PuzzlePtr->HasEssentialNode()) {
    for (const auto& nodePtr : unvisitedNodes) {
      if (nodePtr->isEssential) {
        return false;
      }
    }
  }

  // Are there unvisited tails & no tail up ahead?
  // If both true, return false immediately
  // TODO: verify that this check works
  //if (m_PuzzlePtr->HasEssentialNode()) {
  //  for (const auto& nodePtr : unvisitedNodes) {
  //    if (nodePtr->isTail) {
  //      m_MissedTailCount++;
  //    }
  //    if ((m_MissedTailCount + m_VisitedTails.size()) >= m_PuzzlePtr->GetTails().size()) {
  //      return false;
  //    }
  //  }
  //}

  // Find all the unvisited sides in segment if needed
  // TODO: add conditions
  if (m_PuzzlePtr->HasEssentialSide()) {
    SideSet unvisitedSides;
    for (const auto& blockPtr : segment) {
      Vector2 blockCoord = blockPtr->coord;
      Node& corner1 = m_PuzzlePtr->GetNode(blockCoord);
      Node& corner2 = m_PuzzlePtr->GetNode(blockCoord + Vector2(0, 1));
      Node& corner3 = m_PuzzlePtr->GetNode(blockCoord + Vector2(1, 1));
      Node& corner4 = m_PuzzlePtr->GetNode(blockCoord + Vector2(1, 0));
      Side side1(&corner1, &corner2);
      Side side2(&corner2, &corner3);
      Side side3(&corner3, &corner4);
      Side side4(&corner4, &corner1);

      for (auto& side : {side1, side2, side3, side4}) {
        if (!HasVisitedSide(side)) {
          unvisitedSides.insert(side);
        }
      }
    }

    // Are there unvisited essential sides?
    // If yes, return false immediately
    if (m_PuzzlePtr->HasEssentialSide()) {
      for (const auto& side : unvisitedSides) {
        if (m_PuzzlePtr->GetEssentialSides().count(side) == 1) {
          return false;
        }
      }
    }
  }

  // Return true if it survives all the way to the end
  return true;
}

bool Path::ProcessRemainingSegments() {
  // Look for unvisited block
  for (int r = 0; r < m_BlockMap.Rows(); r++) {
    for (int c = 0; c < m_BlockMap.Cols(); c++) {
      Block& block = m_BlockMap.GetBlock(r, c);
      // Once found, form a segment & evaluate it
      if (!block.visited) {
        BlockPtrSet segment;
        m_BlockMap.Segment(Vector2(r, c), segment);
        bool currResult = EvaluateSegment(segment);
        if (!currResult) return false;
      }
    }
  }
  return true;
}

void Path::Draw() {
  DisplayMatrix display;
  m_PuzzlePtr->CreateDisplayMatrix(display);

  // Add path to display
  for (int i = 0; i < m_Path.size() - 1; i++) {
    Vector2 p1Coord = m_Path[i]->coord;
    Vector2 p2Coord = m_Path[i + 1]->coord;
    if (p1Coord.r == p2Coord.r) {
      display[p1Coord.r * 2][p1Coord.c + p2Coord.c] = '-';
    }
    else if (p1Coord.c == p2Coord.c) {
      display[p1Coord.r + p2Coord.r][p1Coord.c * 2] = '|';
    }
  }

  // Drawing
  for (int r = 0; r < display.size(); r++) {
    for (int c = 0; c < display[0].size(); c++) {
      std::cout << display[r][c];
    }
    std::cout << std::endl;
  }
}
