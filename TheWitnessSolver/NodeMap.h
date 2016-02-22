#pragma once
#include "stdafx.h"

#include "PuzzleElement.h"

class NodeMap {

public:

  // Reset everything
  void Reset(int row, int col);
  // Reset the neighbors of nodes
  void ResetConnectivity();

  // Getters
  Node& GetNode(int r, int c);
  Node& GetNode(const Vector2& vec);
  inline size_t Rows() const { return m_NodeMatrix.size(); }
  inline size_t Cols() const { return m_NodeMatrix[0].size(); }

  // Check the validity of a node coordinate
  inline bool ValidCoord(const Vector2& v) const { return ValidCoord(v.r, v.c); }
  inline bool ValidCoord(int r, int c) const {
    return (r >= 0 && c >= 0 && r < Rows() && c < Cols()) ? true : false;
  }

  // Set a node to be essential, which means the path has to pass through it
  void AddEssential(const Vector2& vec);

  // This will remove node2 from node1's neighborSet and vice versa
  void CutTie(const Vector2& vec1, const Vector2& vec2);

private:

  // Check if a node is on the edge; this is only used by Reset() in the beginning
  // If you want to check whether a node is on edge, just check the flag of the node
  bool IsOnEdge(const Node& node) const;

  NodeMatrix m_NodeMatrix;
};