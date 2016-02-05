#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"
#include <cassert>

// Generic object representing the puzzle
class Puzzle {
public:
  Puzzle() {}
  Puzzle(int nodeRow, int nodeCol) {
    ResetPuzzle(nodeRow, nodeCol);
  }

  // Reset (& initialize) the puzzle
  void ResetPuzzle(int nodeRow, int nodeCol);

  // Reset neighbors of nodes and blocks
  void ResetNodeMatrixConnectivity();
  void ResetBlockMatrixConnectivity();

  // Getters
  Node& GetNode(int r, int c);
  Node& GetNode(const Vector2& vec);
  inline size_t NodeRows() { return m_NodeMatrix.size(); }
  inline size_t NodeCols() { return m_NodeMatrix[0].size(); }
  inline NodeSet& GetHeads() { return m_NodeHeads; }
  inline NodeSet& GetTails() { return m_NodeTails; }
  inline std::vector<Path>& GetPaths() { return m_Paths; }

  Block& GetBlock(int r, int c);
  Block& GetBlock(const Vector2& vec);
  inline size_t BlockRows() { return m_BlockMatrix.size(); }
  inline size_t BlockCols() { return m_BlockMatrix[0].size(); }


  // Check the validity of a node coordinate
  inline bool ValidNodeCoord(const Vector2& v) { return ValidNodeCoord(v.r, v.c); }
  inline bool ValidNodeCoord(int r, int c) {
    return (r >= 0 && c >= 0 && r < NodeRows() && c < NodeCols()) ? true : false;
  }

  // Check the validity of a block coordinate
  inline bool ValidBlockCoord(const Vector2& v) { return ValidBlockCoord(v.r, v.c); }
  inline bool ValidBlockCoord(int r, int c) {
    return (r >= 0 && c >= 0 && r < BlockRows() && c < BlockCols()) ? true : false;
  }

  // Add heads or tails to the puzzle
  void AddHead(const Vector2& vec);
  void AddTail(const Vector2& vec);

  // Set the type of a block
  void SetBlockType(const Vector2& vec, BlockType type);

  // Add an obstacle between 2 adjacent nodes
  // This will remove node2 from node1's neighborSet and vice versa
  void AddNodeObstacle(const Vector2& vec1, const Vector2& vec2);

  // Set a node to be essential, which means the path has to pass through it
  void AddEssential(const Vector2& vec);

  // Solve the puzzle & return a valid path from any head to any tail
  // TODO: expand this function for more types of puzzle
  void Solve();

private:

  // We need to check essential count if there are essential nodes
  // in the puzzle
  bool PuzzleHasEssentialNode();

  // Evaluate whether a path has collected all the essential nodes.
  // Since the path is not allowed to step on the same node twice,
  // we only have to check whether the number of collected essential nodes
  // checks out
  bool PathHasCollectedAllEssentialNodes(const Path& path);

  // Check if the path has unvisited tails
  bool PathHasTailLeft(const Path& path);

  // all paths returned by the solver
  std::vector<Path> m_Paths;

  // 2 main matrices of the puzzle
  NodeMatrix  m_NodeMatrix;
  BlockMatrix m_BlockMatrix;

  // Heads & tails (starts & goals)
  NodeSet m_NodeHeads;
  NodeSet m_NodeTails;

  // Essential nodes
  NodeSet m_NodeEssentials;
};
