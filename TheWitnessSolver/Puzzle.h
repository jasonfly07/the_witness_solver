#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"
#include <cassert>

// Generic object representing the puzzle
class Puzzle {
public:
  Puzzle() {}
  Puzzle(int numRow, int numCol) {
    ResetPuzzle(numRow, numCol);
  }

  // Reset (& initialize) the puzzle
  void ResetPuzzle(int numRow, int numCol);

  // Getters
  inline size_t NodeRows() { return m_NodeMatrix.size(); }
  inline size_t NodeCols() { return m_NodeMatrix[0].size(); }
  inline Node& GetNode(int r, int c) { return m_NodeMatrix[r][c]; } // should we check the validity?
  inline Node& GetNode(const Vector2& vec) { return m_NodeMatrix[vec.r][vec.c]; }
  inline NodeSet& GetHeads() { return m_NodeHeads; }
  inline NodeSet& GetTails() { return m_NodeTails; }
  inline std::vector<Path>& GetPaths() { return m_Paths; }

  // Check the validity of a coordinate
  inline bool ValidCoord(const Vector2& v) { return ValidCoord(v.r, v.c); }
  inline bool ValidCoord(int r, int c) {
    return (r >= 0 && c >= 0 && r < NodeRows() && c < NodeCols()) ? true : false;
  }

  // Add heads or tails to the puzzle
  void AddHead(const Vector2& vec);
  void AddTail(const Vector2& vec);

  // Add an obstacle between 2 adjacent nodes
  // This will remove node2 from node1's neighborSet and vice versa
  void AddObstacle(const Vector2& vec1, const Vector2& vec2);

  // Set a node to be essential, which means the path has to pass through it
  void AddEssential(const Vector2& vec);

  // Solve the puzzle & return a valid path from any head to any tail
  // TODO: expand this function for more types of puzzle
  void Solve();

private:

  // all paths returned by the solver
  std::vector<Path> m_Paths;

  NodeMatrix m_NodeMatrix;


  // Heads & tails (starts & goals)
  NodeSet m_NodeHeads;
  NodeSet m_NodeTails;

  // Essential nodes
  NodeSet m_NodeEssentials;
};
