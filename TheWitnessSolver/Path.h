#pragma once
#include "PuzzleElement.h"
#include "Puzzle.h"

// A path object is used by the solver to record the history of searching
// It contains all node visited, essential node counts, etc.
class Path {
public:

  // A path is initialized by specifying its "parent" puzzle
  Path(Puzzle* puzzle) {
    m_PuzzlePtr = puzzle;
    m_TouchCount = 0;
    m_LeaveCount = 0;
    m_BlockMap = puzzle->GetBlockMap();
  }

  // Copy constructor
  Path(const Path& other) {
    m_PuzzlePtr = other.m_PuzzlePtr;
    m_TouchCount = other.m_TouchCount;
    m_LeaveCount = other.m_LeaveCount;

    m_VisitedNodes = other.m_VisitedNodes;
    m_VisitedTails = other.m_VisitedTails;
    m_VisitedEssentialNodes = other.m_VisitedEssentialNodes;

    m_Path = other.m_Path;
    m_BlockMap = other.m_BlockMap;
  }

  // Add a node to the path & update various containers
  void AddNode(Node* node);

  inline bool HasVisitedNode(Node* node) {
    return m_VisitedNodes.count(node) == 1 ? true : false;
  }

  bool HasCollectedAllEssentialNodes() {
    return m_PuzzlePtr->GetEssentialNodes().size() == m_VisitedEssentialNodes.size();
  }

  bool HasTailLeft() {
    return m_PuzzlePtr->GetTails().size() == m_VisitedTails.size() ? false : true;
  }

  NodePtrVector& GetPath() { return m_Path; }

  // Print the path in sequence
  void Print() const;

// private:

  // Same as BlockMap::CutTie(), but the inputs are 2 adjacent nodes
  // This utility is used by the path to update its own copy of block map
  void CutBlockTie(const Node& node1, const Node& node2);

  // Records the number of times the path touching/leaving the edge
  int m_TouchCount;
  int m_LeaveCount;

  // Containers for the history of exploring
  NodePtrSet m_VisitedNodes;
  NodePtrSet m_VisitedTails;
  NodePtrSet m_VisitedEssentialNodes;

  // Stores all the visited nodes in sequence
  NodePtrVector m_Path;

  // This is the puzzle on which the path operates
  Puzzle* m_PuzzlePtr;

  // The path has its own copy of block map, so it can update the connectivity
  // & segment as the path grows
  BlockMap m_BlockMap;
};
typedef std::vector<Path> PathVector;
