#pragma once
#include "stdafx.h"

#include "BlockMap.h"
#include "NodeMap.h"
#include "PuzzleElement.h"


// This object contains all the information about a puzzle before solving.
// A puzzle consists of a node map and a block map.
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

  // Getters
  inline Node& GetNode(int r, int c)       { return m_NodeMap.GetNode(r, c); }
  inline Node& GetNode(const Vector2& vec) { return m_NodeMap.GetNode(vec);  }
  inline size_t NodeRows() const { return m_NodeMap.Rows(); }
  inline size_t NodeCols() const { return m_NodeMap.Cols(); }
  inline NodePtrSet& GetHeads() { return m_NodeHeads; }
  inline NodePtrSet& GetTails() { return m_NodeTails; }
  inline NodePtrSet& GetEssentialNodes() { return m_NodeEssentials; }
  inline SideSet& GetEssentialSides() { return m_SideEssentials; }

  inline Block& GetBlock(int r, int c)       { return m_BlockMap.GetBlock(r, c); }
  inline Block& GetBlock(const Vector2& vec) { return m_BlockMap.GetBlock(vec); }
  inline size_t BlockRows() const { return m_BlockMap.Rows(); }
  inline size_t BlockCols() const { return m_BlockMap.Cols(); }

  inline BlockMap& GetBlockMap() { return m_BlockMap; }

  // Check the validity of coordinates
  inline bool ValidNodeCoord(const Vector2& v) const  { return m_NodeMap.ValidCoord(v);     }
  inline bool ValidNodeCoord(int r, int c) const      { return m_NodeMap.ValidCoord(r, c);  }
  inline bool ValidBlockCoord(const Vector2& v) const { return m_BlockMap.ValidCoord(v);    }
  inline bool ValidBlockCoord(int r, int c) const     { return m_BlockMap.ValidCoord(r, c); }

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

  // Check if the puzzle has black & white puzzles
  // Expensive, so this should only be called once before solving
  // When this function is run, we'll update m_HasBlackWhiteBlocks
  bool CheckBlackWhiteBlocks();
  void PreprocessBlackWhiteBlocks();
  bool HasBlackWhite() const { return m_HasBlackWhiteBlocks; }

  bool HasEssentialNode() {
    return m_NodeEssentials.size() > 0;
  }

private:

  // 2 main maps of the puzzle
  NodeMap  m_NodeMap;
  BlockMap m_BlockMap;

  // Heads & tails (starts & goals)
  NodePtrSet m_NodeHeads;
  NodePtrSet m_NodeTails;

  // Essentials
  NodePtrSet m_NodeEssentials;
  SideSet    m_SideEssentials;

  bool m_HasBlackWhiteBlocks;
};