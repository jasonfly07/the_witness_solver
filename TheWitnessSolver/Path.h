#pragma once
#include "PuzzleElement.h"
#include "Puzzle.h"

// A path object is used by the solver to record the history of searching
// It contains all node visited, essential node counts, etc.
class Path {
public:

  // A path is always initialized by specifying its "parent" puzzle
  Path(Puzzle& puzzle) {
    m_PuzzlePtr = &puzzle;
  }

  // Add a node to the path & update various containers
  void AddNode(Node* node);

  inline bool HasVisitedNode(Node* node) {
    return m_VisitedNodes.count(node) == 1 ? true : false;
  }

  // Print the path in sequence
  void Print() const;

private:

  // Same as BlockMap::CutTie(), but the inputs are 2 adjacent nodes
  // This utility is used by the path to update its own copy of block map
  void CutBlockTie(const Node& node1, const Node& node2);

  // Records the number of times the path touching/leaving the edge
  int m_TouchCount;
  int m_LeaveCount;

  // Containers for the history of exploring
  NodePtrSet    m_VisitedNodes;
  NodePtrSet    m_VisitedTails;
  NodePtrSet    m_VisitedEssentialNodes;

  // Stores all the visited nodes in sequence
  NodePtrVector m_Path;

  // This is the puzzle on which the path operates
  Puzzle* m_PuzzlePtr;

  // The path has its own copy of block map, so it can update the connectivity
  // & segment as the path grows
  BlockMap m_BlockMap;
};
typedef std::vector<Path> PathVector;
