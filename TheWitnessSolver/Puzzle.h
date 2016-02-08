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

  // Reset the visited flags in block matrix
  void ResetBlockMatrixVisitHistory();

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

  // Add an obstacle between 2 adjacent nodes
  // This will remove node2 from node1's neighborSet and vice versa
  void AddNodeObstacle(const Vector2& vec1, const Vector2& vec2);

  // Set a node to be essential, which means the path has to pass through it
  void AddEssentialNode(const Vector2& vec);

  // Set the type of a block
  void SetBlockType(const Vector2& vec, BlockType type);

  // Add an obstacle between 2 blocks
  // This will remove block2 from block1's neighborSet and vice versa
  void AddBlockObstacle(const Vector2& vec1, const Vector2& vec2);
  void AddBlockObstacle(const Side& side);

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

  // Scan through the puzzle and see if there are black/white blocks to be solved.
  // The result will be stored in m_HasBlackWhiteBlocks,
  // so this should be done only once before solving
  void CheckBlackWhiteBlocks();

  // If m_HasBlackWhiteBlocks = true, we can apply some heuristics to
  // the pathfinding (all sides between black & white must be visited)
  // This should be done only once before solving
  void PreprocessBlackWhiteBlocks();

  // Given a path, perform segmentation on the block map
  // The output is list of BlockSet (segments)
  // Since this operation will destroy the connectivity of block map,
  // we have to reset the connectivity at the end
  void SegmentBlockMap(const Path& path, BlockSetVector& segments);

  // Check if a path has visited all essential sides, as required by the
  // black/white blocks.
  // TODO: this could be optimzied in the same way as
  // PathHasCollectedAllEssentialNodes().
  bool PathHasCollectedAllEssentialSides(const Path& path);

  // Check the black/white count of a segment.
  // By the rule, a segment cannot have both white and black blocks
  bool HasValidBlackWhiteCount(const BlockSet& segment);

  // all paths returned by the solver
  std::vector<Path> m_Paths;

  // 2 main matrices of the puzzle
  NodeMatrix  m_NodeMatrix;
  BlockMatrix m_BlockMatrix;

  // Heads & tails (starts & goals)
  NodeSet m_NodeHeads;
  NodeSet m_NodeTails;

  // Essentials
  NodeSet m_NodeEssentials;
  SideSet m_SideEssentials;

  bool m_HasBlackWhiteBlocks;
};
