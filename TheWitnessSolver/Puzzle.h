#pragma once
#include <cassert>
#include <iostream>
#include <vector>

// A 2d vector.
struct Vector2 {
  Vector2() {}
  Vector2(int r, int c) : r(r), c(c) {}

  Vector2 operator+(const Vector2& other) {
    return Vector2(r + other.r, c + other.c);
  }
  Vector2 operator-(const Vector2& other) {
    return Vector2(r - other.r, c - other.c);
  }
  void operator=(const Vector2& other) {
    r = other.r;
    c = other.c;
    return;
  }
  friend std::ostream& operator<< (std::ostream &out, Vector2& vec) {
    out << "[" << vec.r << ", " << vec.c << "]";
    return out;
  }

  int r;
  int c;
};

//ostream& operator<< (ostream &out, Point &cPoint)
//{
//  // Since operator<< is a friend of the Point class, we can access
//  // Point's members directly.
//  out << "(" << cPoint.m_dX << ", " <<
//    cPoint.m_dY << ", " <<
//    cPoint.m_dZ << ")";
//  return out;
//}

// A node on the grid. 
// Contains coordinates, its reachable naighbors, and some extra info.
struct Node {
  Node() {}
  Node(int r, int c) {
    coord = Vector2(r, c);
    essential = false;
  }
  Vector2 coord;
  std::vector<Vector2> neightborList;
  bool essential;
};

typedef std::vector<std::vector<Node>> NodeMatrix;

// Generic object representing the puzzle
struct Puzzle {
  Puzzle() {}
  Puzzle(int numRow, int numCol) {
    ResetPuzzle(numRow, numCol);
  }

  void ResetPuzzle(int numRow, int numCol) {
    assert(numRow > 0 && numCol > 0);
    m_NodeMatrix.clear();
    m_NodeMatrix.resize(numRow, std::vector<Node>(numCol));
    for (int r = 0; r < numRow; r++) {
      for (int c = 0; c < numCol; c++) {
        Node& currNode = m_NodeMatrix[r][c];
        currNode.coord = Vector2(r, c);

        currNode.neightborList.clear();
        currNode.neightborList.reserve(4);
        Vector2 lCoord(r, c - 1);
        Vector2 rCoord(r, c + 1);
        Vector2 tCoord(r - 1, c);
        Vector2 bCoord(r + 1, c);
        if (ValidCoord(lCoord)) currNode.neightborList.push_back(lCoord);
        if (ValidCoord(rCoord)) currNode.neightborList.push_back(rCoord);
        if (ValidCoord(tCoord)) currNode.neightborList.push_back(tCoord);
        if (ValidCoord(bCoord)) currNode.neightborList.push_back(bCoord);
      }
    }
  }

  // Getters
  inline size_t NodeRows() { return m_NodeMatrix.size(); }
  inline size_t NodeCols() { return m_NodeMatrix[0].size(); }

  bool ValidCoord(int r, int c) {
    return (r >= 0 && c >= 0 && r < NodeRows() && c < NodeCols()) ? true : false;
  }
  bool ValidCoord(Vector2& v) {
    return ValidCoord(v.r, v.c);
  }

  // TODO: eventually there'll be a m_BlockMatrix
  NodeMatrix m_NodeMatrix;
};