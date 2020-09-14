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

  // Reset the puzzle & clear all containers
  void ResetPuzzle(int nodeRow, int nodeCol);

  // Regenerate the puzzle using current containers & flags
  void Regenerate();

  // Getters
  inline Node& GetNode(int r, int c)       { return m_NodeMap.GetNode(r, c); }
  inline Node& GetNode(const Vector2& vec) { return m_NodeMap.GetNode(vec);  }
  inline size_t NodeRows() const { return m_NodeMap.Rows(); }
  inline size_t NodeCols() const { return m_NodeMap.Cols(); }

  inline Block& GetBlock(int r, int c)       { return m_BlockMap.GetBlock(r, c); }
  inline Block& GetBlock(const Vector2& vec) { return m_BlockMap.GetBlock(vec); }
  inline size_t BlockRows() const { return m_BlockMap.Rows(); }
  inline size_t BlockCols() const { return m_BlockMap.Cols(); }

  inline NodePtrSet& GetHeads() { return m_NodeHeads; }
  inline NodePtrSet& GetTails() { return m_NodeTails; }
  inline NodePtrSet& GetEssentialNodes() { return m_NodeEssentials; }
  inline SideSet& GetEssentialSides() { return m_SideEssentials; }

  inline size_t HeadCount() const { return m_NodeHeads.size(); }
  inline size_t TailCount() const { return m_NodeTails.size(); }
  inline size_t EssentialNodeCount() const { return m_NodeEssentials.size(); }
  inline size_t EssentialSideCount() const { return m_SideEssentials.size(); }


  inline BlockMap& GetBlockMap() { return m_BlockMap; }

  inline void SetName(const std::string& name) { m_Name = name; }
  inline std::string GetName() { return m_Name; }


  // Check the validity of coordinates
  inline bool ValidNodeCoord(const Vector2& v) const  { return m_NodeMap.ValidCoord(v);     }
  inline bool ValidNodeCoord(int r, int c) const      { return m_NodeMap.ValidCoord(r, c);  }
  inline bool ValidBlockCoord(const Vector2& v) const { return m_BlockMap.ValidCoord(v);    }
  inline bool ValidBlockCoord(int r, int c) const     { return m_BlockMap.ValidCoord(r, c); }

  // Adders for various puzzle elements
  void AddHead(const Vector2& vec);
  void AddTail(const Vector2& vec);
  void AddObstacleSide(const Vector2& vec1, const Vector2& vec2);
  void AddEssentialNode(const Vector2& vec);
  void AddEssentialSide(const Vector2& vec1, const Vector2& vec2);
  void AddSpecialBlock(const Vector2& vec, BlockType type);

  inline bool HasBlackWhite() const { return m_HasBlackWhite; }
  inline bool HasTetris() const { return m_HasTetris; }

  inline bool HasEssentialNode() {
    return m_NodeEssentials.size() > 0;
  }
  inline bool HasEssentialSide() {
    return m_SideEssentials.size() > 0;
  }

  // Drawing
  void CreateDisplayMatrix(DisplayMatrix& display);
  void Draw();

private:

  // Utility for Regenerate();
  bool CheckBlackWhite();
  bool CheckTetris();
  void ConvertBlackWhiteToEssentialSides();

  // 2 main maps of the puzzle
  NodeMap  m_NodeMap;
  BlockMap m_BlockMap;

  // Heads & tails (starts & goals)
  NodePtrSet m_NodeHeads;
  NodePtrSet m_NodeTails;

  // Essentials
  NodePtrSet m_NodeEssentials;
  SideSet    m_SideEssentials;

  // Side obstacles
  SideSet m_SideObstacles;

  // Special blocks
  BlockPtrHashMap m_SpecialBlocks;

  // Name of puzzle
  std::string m_Name;

  // Additional flags
  bool m_HasBlackWhite;
  bool m_HasTetris;
};