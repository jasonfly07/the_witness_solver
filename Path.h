#pragma once
#include "PuzzleElement.h"
#include "Puzzle.h"
#include "Tetris.h"

// A path object is used by the solver to record the history of searching
// It contains all node visited, essential node counts, etc.
class Path
{
public:
  // A path is initialized by specifying its "parent" puzzle
  Path(Puzzle *puzzle)
  {
    assert(puzzle != NULL);

    m_TouchCount = 0;
    m_LeaveCount = 0;
    m_Segmenting = false;

    m_VisitedNodes.clear();
    m_VisitedTails.clear();
    m_VisitedEssentialNodes.clear();
    m_VisitedSides.clear();
    m_MissedTailCount = 0;

    m_Path.clear();
    m_PuzzlePtr = puzzle;
    m_BlockMap = puzzle->GetBlockMap();
  }

  // Copy constructor
  Path(const Path &other)
  {
    assert(other.m_PuzzlePtr != NULL);
    m_PuzzlePtr = other.m_PuzzlePtr;
    m_TouchCount = other.m_TouchCount;
    m_LeaveCount = other.m_LeaveCount;
    m_Segmenting = other.m_Segmenting;
    m_MissedTailCount = other.m_MissedTailCount;

    m_VisitedNodes = other.m_VisitedNodes;
    m_VisitedTails = other.m_VisitedTails;
    m_VisitedEssentialNodes = other.m_VisitedEssentialNodes;
    m_VisitedSides = other.m_VisitedSides;

    m_Path = other.m_Path;
    m_BlockMap = other.m_BlockMap;
  }

  // Add a node to the path & update various containers
  // The return value is a boolean indicating whether the current path is valid or not
  bool AddNode(Node *node);

  inline bool HasVisitedNode(Node *node) const
  {
    return m_VisitedNodes.count(node) == 1 ? true : false;
  }
  inline bool HasVisitedNode(Vector2 coord) const
  {
    assert(m_PuzzlePtr != NULL);
    return m_VisitedNodes.count(&m_PuzzlePtr->GetNode(coord)) == 1 ? true : false;
  }

  inline bool HasVisitedSide(Side side) const
  {
    return m_VisitedSides.count(side) == 1 ? true : false;
  }

  bool HasCollectedAllEssentialNodes() const
  {
    assert(m_PuzzlePtr != NULL);
    return m_PuzzlePtr->GetEssentialNodes().size() == m_VisitedEssentialNodes.size();
  }

  bool HasTailLeft() const
  {
    assert(m_PuzzlePtr != NULL);
    return m_PuzzlePtr->GetTails().size() == m_VisitedTails.size() ? false : true;
  }

  NodePtrVector &GetPath() { return m_Path; }

  // Deal with all unprocessed segments.
  // Once reaching a tail, a path would have either 1 or 2 unprocessed segments;
  // this method is for cleaning them up.
  // Don't run this until reaching a tail.
  bool ProcessRemainingSegments();

  // Print the path in sequence
  void Print() const;

  // Drawing
  void Draw();

private:
  // Same as BlockMap::CutTie(), but the inputs are 2 adjacent nodes
  // This utility is used by the path to update its own copy of block map
  void CutBlockTie(const Node &node1, const Node &node2);

  // Evaluate a segment
  bool EvaluateSegment(const BlockPtrSet &segment);

  // Given a list of segment coords & a list of tetris pieces,
  // evaluate whether the pieces form the segment.
  // This utility is used by EvaluateSegment() as part of its tetris evaluation.
  // Before calling this function, the area of segment is ensured to equal
  // that of the sum of tetris pieces.
  bool FitSegmentWithTetris(const Vector2Set &segmentCoords, const TetrisVector &tetrisVector);

  // Records the number of times the path touching/leaving the edge
  int m_TouchCount;
  int m_LeaveCount;
  bool m_Segmenting;

  // Containers for the history of exploring
  NodePtrSet m_VisitedNodes;
  NodePtrSet m_VisitedTails;
  NodePtrSet m_VisitedEssentialNodes;
  SideSet m_VisitedSides;
  int m_MissedTailCount;

  // Stores all the visited nodes in sequence
  NodePtrVector m_Path;

  // This is the puzzle on which the path operates
  Puzzle *m_PuzzlePtr;

  // The path has its own copy of block map, so it can update the connectivity
  // & segment as the path grows
  BlockMap m_BlockMap;
};
typedef std::vector<Path> PathVector;
