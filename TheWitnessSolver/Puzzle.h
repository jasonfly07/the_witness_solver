#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"
#include <cassert>

// This object contains all the information about a puzzle before solving.
// A puzzle consists of a node matrix and a block matrix.
// The goal of the puzzle is to find a path from one of the heads to one of the tails,
// while also fulfilling specific requirements in the process.
class Puzzle {
public:
  Puzzle() {}
  Puzzle(int nodeRow, int nodeCol) {
    ResetPuzzle(nodeRow, nodeCol);
  }

  // Reset (& initialize) the puzzle
  void ResetPuzzle(int nodeRow, int nodeCol);
  void ResetNodeMatrixConnectivity();
  void ResetBlockMatrixConnectivity();

  // Getters
  Node& GetNode(int r, int c);
  Node& GetNode(const Vector2& vec);
  inline size_t NodeRows() { return m_NodeMatrix.size(); }
  inline size_t NodeCols() { return m_NodeMatrix[0].size(); }
  inline NodePtrSet& GetHeads() { return m_NodeHeads; }
  inline NodePtrSet& GetTails() { return m_NodeTails; }

  Block& GetBlock(int r, int c);
  Block& GetBlock(const Vector2& vec);
  inline size_t BlockRows() { return m_BlockMatrix.size(); }
  inline size_t BlockCols() { return m_BlockMatrix[0].size(); }
  BlockMatrix& GetBlockMatrix() { return m_BlockMatrix; }

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

  // Set a side to be essential
  void AddEssentialSide(const Vector2& vec1, const Vector2& vec2);

  // Set the type of a block
  void SetBlockType(const Vector2& vec, BlockType type);

  // Check if a node is on the edge
  bool IsOnEdge(const Node& node);

private:

  // 2 main matrices of the puzzle
  NodeMatrix  m_NodeMatrix;
  BlockMatrix m_BlockMatrix;

  // Heads & tails (starts & goals)
  NodePtrSet m_NodeHeads;
  NodePtrSet m_NodeTails;

  // Essentials
  NodePtrSet m_NodeEssentials;
  SideSet    m_SideEssentials;

  bool m_HasBlackWhiteBlocks;
};