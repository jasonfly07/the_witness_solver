#include "Path.h"

bool Path::AddNode(Node *node)
{
  assert(m_PuzzlePtr != NULL);
  // The first node HAS to be a head
  if (m_Path.size() == 0)
  {
    assert(node->isHead);
  }

  // There're 2 cases at start: head is on edge & not on edge
  // if the head is on edge, set touchCount to 1
  if (m_Path.size() == 0 && node->isHead && node->onEdge)
  {
    m_TouchCount = 1;
  }

  // If leaveCount >= 1, and touchCount = leaveCount + 1
  // in the next step, a segment will be created
  if (m_Segmenting && m_LeaveCount >= 1 && m_TouchCount == m_LeaveCount + 1)
  {
    m_Segmenting = false;

    // Compute the node coord that's on the opposite side of the current step
    Vector2 currCoord = node->coord;
    Vector2 prevCoord = m_Path.end()[-1]->coord;
    Vector2 oppositeCoord = prevCoord * 2 - currCoord;

    // The block for seeding the segment will touch the side formed by
    // prevVec2 & oppositeVec2
    Vector2 seedBlockCoord;
    Side seedSide(&m_PuzzlePtr->GetNode(prevCoord), &m_PuzzlePtr->GetNode(oppositeCoord));
    if (seedSide.IsHorizontal())
    {
      if (seedSide.node1->coord.r == 0)
      {
        seedBlockCoord = seedSide.node1->coord;
      }
      else
      {
        seedBlockCoord = seedSide.node1->coord - Vector2(1, 0);
      }
    }
    else
    {
      if (seedSide.node1->coord.c == 0)
      {
        seedBlockCoord = seedSide.node1->coord;
      }
      else
      {
        seedBlockCoord = seedSide.node1->coord - Vector2(0, 1);
      }
    }

    // Perform segmentation with the seed
    BlockPtrSet segment;
    m_BlockMap.Segment(seedBlockCoord, segment);

    // Evalute this segment
    bool validPath = EvaluateSegment(segment);
    if (!validPath)
      return false;
  }

  // Cut the tie between 2 blocks if necessary
  if (m_Path.size() > 0)
  {
    CutBlockTie(*node, *(m_Path.end()[-1]));
  }

  // See if this step is leaving the edge
  if (m_Path.size() > 0)
  {
    if (!(node->onEdge) && m_Path.end()[-1]->onEdge)
    {
      m_LeaveCount++;
      m_Segmenting = true;
    }
  }

  // See if this step is touching the edge
  if (m_Path.size() > 0)
  {
    if (node->onEdge && !(m_Path.back()->onEdge))
    {
      m_TouchCount++;
    }
  }

  // Finally, insert the node into relevant containers
  m_VisitedNodes.insert(node);
  if (m_Path.size() > 0)
  {
    m_VisitedSides.insert(Side(node, m_Path.back()));
  }
  m_Path.push_back(node);
  if (node->isEssential)
    m_VisitedEssentialNodes.insert(node);
  if (node->isTail)
    m_VisitedTails.insert(node);
  return true;
}

void Path::Print() const
{
  std::cout << "Path : ";
  for (const auto &node : m_Path)
  {
    std::cout << node->coord << " ";
  }
  std::cout << std::endl;
}

void Path::CutBlockTie(const Node &node1, const Node &node2)
{
  assert(m_PuzzlePtr != NULL);

  // No need to proceed if side is on the border
  if (node1.coord.r == 0 && node2.coord.r == 0)
    return;
  if (node1.coord.c == 0 && node2.coord.c == 0)
    return;
  if (node1.coord.r == m_PuzzlePtr->NodeRows() - 1 && node2.coord.r == m_PuzzlePtr->NodeRows() - 1)
    return;
  if (node1.coord.c == m_PuzzlePtr->NodeCols() - 1 && node2.coord.c == m_PuzzlePtr->NodeCols() - 1)
    return;

  // Case 1: side is vertical
  if (node1.coord.c == node2.coord.c)
  {
    int R = std::min(node1.coord.r, node2.coord.r);
    int C = node1.coord.c;
    Block &block1 = m_BlockMap.GetBlock(R, C - 1);
    Block &block2 = m_BlockMap.GetBlock(R, C);
    m_BlockMap.CutTie(block1.coord, block2.coord);
  }
  // Case 2: side is horizontal
  else if (node1.coord.r == node2.coord.r)
  {
    int R = node1.coord.r;
    int C = std::min(node1.coord.c, node2.coord.c);
    Block &block1 = m_BlockMap.GetBlock(R - 1, C);
    Block &block2 = m_BlockMap.GetBlock(R, C);
    m_BlockMap.CutTie(block1.coord, block2.coord);
  }
}

bool Path::EvaluateSegment(const BlockPtrSet &segment)
{
  assert(m_PuzzlePtr != NULL);

  // Are there black & white blocks mixed together?
  // If yes, return false immediately
  if (m_PuzzlePtr->HasBlackWhite())
  {
    bool hasWhite = false;
    bool hasBlack = false;
    for (const auto &block : segment)
    {
      if (block->type == White)
      {
        hasWhite = true;
      }
      else if (block->type == Black)
      {
        hasBlack = true;
      }

      if (hasWhite && hasBlack)
      {
        return false;
      }
    }
  }

  // Find all the unvisited nodes in segment
  if (m_PuzzlePtr->HasEssentialNode())
  {
    NodePtrSet unvisitedNodes;
    for (const auto &blockPtr : segment)
    {
      Vector2 blockCoord = blockPtr->coord;
      for (Vector2 offset : {Vector2(0, 0), Vector2(0, 1), Vector2(1, 0), Vector2(1, 1)})
      {
        Vector2 nodeCoord = blockCoord + offset;
        if (!HasVisitedNode(nodeCoord))
        {
          unvisitedNodes.insert(&m_PuzzlePtr->GetNode(nodeCoord));
        }
      }
    }

    // Are there unvisited essential nodes?
    // If yes, return false immediately
    if (m_PuzzlePtr->HasEssentialNode())
    {
      for (const auto &nodePtr : unvisitedNodes)
      {
        if (nodePtr->isEssential)
        {
          return false;
        }
      }
    }
  }

  // Find all the unvisited sides in segment if needed
  if (m_PuzzlePtr->HasEssentialSide())
  {
    SideSet unvisitedSides;
    for (const auto &blockPtr : segment)
    {
      Vector2 blockCoord = blockPtr->coord;
      Node &corner1 = m_PuzzlePtr->GetNode(blockCoord);
      Node &corner2 = m_PuzzlePtr->GetNode(blockCoord + Vector2(0, 1));
      Node &corner3 = m_PuzzlePtr->GetNode(blockCoord + Vector2(1, 1));
      Node &corner4 = m_PuzzlePtr->GetNode(blockCoord + Vector2(1, 0));
      Side side1(&corner1, &corner2);
      Side side2(&corner2, &corner3);
      Side side3(&corner3, &corner4);
      Side side4(&corner4, &corner1);

      for (auto &side : {side1, side2, side3, side4})
      {
        if (!HasVisitedSide(side))
        {
          unvisitedSides.insert(side);
        }
      }
    }

    // Are there unvisited essential sides?
    // If yes, return false immediately
    if (m_PuzzlePtr->HasEssentialSide())
    {
      for (const auto &side : unvisitedSides)
      {
        if (m_PuzzlePtr->GetEssentialSides().count(side) == 1)
        {
          return false;
        }
      }
    }
  }

  // Are there tetris blocks & does the current segment satisfy them?
  if (m_PuzzlePtr->HasTetris())
  {
    TetrisVector tetrisVector;

    // Sum of area has to match the current segment
    size_t tetrisAreaSum = 0;
    const size_t segmentArea = segment.size();
    bool hasTetris = false;
    for (const auto &blockPtr : segment)
    {
      // TODO: update 3
      if (blockPtr->type >= 3)
      {
        hasTetris = true;
        Tetris tetris(blockPtr->type);
        tetrisAreaSum += tetris.area;
        if (tetrisAreaSum > segmentArea)
        {
          return false;
        }
        tetrisVector.push_back(tetris);
      }
    }
    if (hasTetris && tetrisAreaSum != segmentArea)
    {
      return false;
    }

    // Process if current segment has tetris pieces
    if (hasTetris)
    {
      // Create a bag of coords in segment for the next part
      Vector2Set segmentCoords;
      segmentCoords.reserve(segmentArea);
      for (const auto &blockPtr : segment)
      {
        segmentCoords.insert(blockPtr->coord);
      }

      // Check if all the pieces fit inside this segment
      if (!FitSegmentWithTetris(segmentCoords, tetrisVector))
      {
        return false;
      }
    }
  }

  // Return true if it survives all the way to the end
  return true;
}

bool Path::FitSegmentWithTetris(const Vector2Set &segmentCoords, const TetrisVector &tetrisVector)
{
  // Base case
  if (segmentCoords.size() == 0 && tetrisVector.size() == 0)
  {
    return true;
  }

  // Recursive case
  // For every block, see if we can fit & grow a tetris piece on it
  // We always pick the last piece of tetrisVector (easier to remove)
  for (const auto &segmentCoord : segmentCoords)
  {
    const Tetris &tetris = tetrisVector.back();
    bool canFit = true;
    for (const auto &tetrisCoordOffset : tetris.shape)
    {
      Vector2 tetrisCoord = segmentCoord + tetrisCoordOffset;
      if (segmentCoords.count(tetrisCoord) != 1)
      {
        canFit = false;
        break;
      }
    }

    // If it fits, we remove tetris from tetrisVector, associated coords from
    // segmentCoords, and continue the recursion
    if (canFit)
    {
      auto segmentCoordsReduced = segmentCoords;
      auto tetrisVectorReduced = tetrisVector;
      for (const auto &tetrisCoordOffset : tetris.shape)
      {
        Vector2 tetrisCoord = segmentCoord + tetrisCoordOffset;
        segmentCoordsReduced.erase(tetrisCoord);
      }
      tetrisVectorReduced.pop_back();
      return FitSegmentWithTetris(segmentCoordsReduced, tetrisVectorReduced);
    }
  }

  // Reaching this line means tetris cannot fit into current segment
  return false;
}

bool Path::ProcessRemainingSegments()
{
  // Look for unvisited block
  for (int r = 0; r < m_BlockMap.Rows(); r++)
  {
    for (int c = 0; c < m_BlockMap.Cols(); c++)
    {
      Block &block = m_BlockMap.GetBlock(r, c);
      // Once found, form a segment & evaluate it
      if (!block.visited)
      {
        BlockPtrSet segment;
        m_BlockMap.Segment(Vector2(r, c), segment);
        bool currResult = EvaluateSegment(segment);
        if (!currResult)
          return false;
      }
    }
  }
  return true;
}
