#include "Puzzle.h"

void Puzzle::ResetPuzzle(int nodeRow, int nodeCol)
{
  ASSERT((nodeRow > 1 && nodeCol > 1));

  m_NodeMap.Reset(nodeRow, nodeCol);
  m_BlockMap.Reset(nodeRow - 1, nodeCol - 1);

  // Reset all containers & flags
  m_NodeHeads.clear();
  m_NodeTails.clear();
  m_NodeEssentials.clear();
  m_SideEssentials.clear();
  m_SideObstacles.clear();
  m_SpecialBlocks.clear();
  m_Name = "";
  m_HasBlackWhite = false;
}

void Puzzle::Regenerate()
{
  // Set heads & tails
  for (auto &nodePtr : m_NodeHeads)
  {
    nodePtr->isHead = true;
  }
  for (auto &nodePtr : m_NodeTails)
  {
    nodePtr->isTail = true;
  }

  // Set essentials
  for (auto &nodePtr : m_NodeEssentials)
  {
    nodePtr->isEssential = true;
  }

  // Set obstacles
  for (auto &side : m_SideObstacles)
  {
    m_NodeMap.CutTie(side.node1->coord, side.node2->coord);
  }

  // Set blocks
  for (auto &blockTypePair : m_SpecialBlocks)
  {
    m_BlockMap.SetType(blockTypePair.first->coord, blockTypePair.second);
  }

  // Check if there are black & white blocks
  // If yes, dump all sides that touch B & W on both sides to m_SideEssentials
  m_HasBlackWhite = CheckBlackWhite();
  if (m_HasBlackWhite)
  {
    ConvertBlackWhiteToEssentialSides();
  }

  // Check if there are tetris blocks
  m_HasTetris = CheckTetris();
}

void Puzzle::AddHead(const Vector2 &vec)
{
  // If vec is already a tail, remove it from m_NodeTails first
  if (m_NodeTails.count(&GetNode(vec)) == 1)
  {
    m_NodeTails.erase(&GetNode(vec));
  }
  m_NodeHeads.insert(&GetNode(vec));
}

void Puzzle::AddTail(const Vector2 &vec)
{
  // If vec is already a head, remove it from m_NodeHeads first
  if (m_NodeHeads.count(&GetNode(vec)) == 1)
  {
    m_NodeHeads.erase(&GetNode(vec));
  }
  m_NodeTails.insert(&GetNode(vec));
}

void Puzzle::AddObstacleSide(const Vector2 &vec1, const Vector2 &vec2)
{
  // If side is already essential, remove it from m_SideEssentials first
  Side currSide(&GetNode(vec1), &GetNode(vec2));
  if (m_SideEssentials.count(currSide) == 1)
  {
    m_SideEssentials.erase(currSide);
  }
  m_SideObstacles.insert(currSide);
}

void Puzzle::AddEssentialNode(const Vector2 &vec)
{
  m_NodeEssentials.insert(&GetNode(vec));
}

void Puzzle::AddEssentialSide(const Vector2 &vec1, const Vector2 &vec2)
{
  // If side is already an obstacle, remove it from m_SideObstacles first
  Side currSide(&GetNode(vec1), &GetNode(vec2));
  if (m_SideObstacles.count(currSide) == 1)
  {
    m_SideObstacles.erase(currSide);
  }
  m_SideEssentials.insert(currSide);
}

void Puzzle::AddSpecialBlock(const Vector2 &vec, BlockType type)
{
  m_SpecialBlocks.erase(&GetBlock(vec));
  m_SpecialBlocks.insert({&GetBlock(vec), type});
}

bool Puzzle::CheckBlackWhite()
{
  for (int r = 0; r < BlockRows(); r++)
  {
    for (int c = 0; c < BlockCols(); c++)
    {
      const Block &currBlock = GetBlock(r, c);
      if ((currBlock.type == Black) || (currBlock.type == White))
      {
        return true;
      }
    }
  }
  return false;
}

bool Puzzle::CheckTetris()
{
  for (int r = 0; r < BlockRows(); r++)
  {
    for (int c = 0; c < BlockCols(); c++)
    {
      const Block &currBlock = GetBlock(r, c);
      if ((int)currBlock.type >= 3)
      {
        return true;
      }
    }
  }
  return false;
}

void Puzzle::ConvertBlackWhiteToEssentialSides()
{
  // For every block [r, c], process the sides (if valid):
  // 1. between [r, c] and [r, c + 1]
  // 2. between [r, c] and [r + 1, c]
  for (int r = 0; r < BlockRows(); r++)
  {
    for (int c = 0; c < BlockCols(); c++)
    {
      const Block &currBlock = GetBlock(r, c);

      // 1. [r, c + 1]
      if (ValidBlockCoord(r, c + 1))
      {
        const Block &rightBlock = GetBlock(r, c + 1);
        if ((currBlock.type == White && rightBlock.type == Black) ||
            (currBlock.type == Black && rightBlock.type == White))
        {
          m_SideEssentials.insert(Side(&GetNode(r, c + 1), &GetNode(r + 1, c + 1)));
        }
      }

      // 2. [r + 1, c]
      if (ValidBlockCoord(r + 1, c))
      {
        const Block &bottomBlock = GetBlock(r + 1, c);
        if ((currBlock.type == White && bottomBlock.type == Black) ||
            (currBlock.type == Black && bottomBlock.type == White))
        {
          m_SideEssentials.insert(Side(&GetNode(r + 1, c), &GetNode(r + 1, c + 1)));
        }
      }
    }
  }
}
