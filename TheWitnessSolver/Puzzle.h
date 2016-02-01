#pragma once
#include <cassert>
#include <iostream>
#include <unordered_set>
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
typedef std::vector<Vector2> Vector2List;

// A node on the grid.
// Contains coordinates, its reachable naighbors, and some extra info.
struct Node {
  Node() {
    coord = Vector2(0, 0);
    isEssential = false;
    isHead = false;
    isTail = false;
  }
  Node(int r, int c) {
    coord = Vector2(r, c);
    isEssential = false;
    isHead = false;
    isTail = false;
  }
  Vector2 coord;
  std::unordered_set<Node*> neighborSet;
  bool isEssential;
  bool isHead;
  bool isTail;
};
typedef std::unordered_set<Node*> NodeSet;
typedef std::vector<std::vector<Node>> NodeMatrix;

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

private:
  // TODO: eventually there'll be a m_BlockMatrix
  NodeMatrix m_NodeMatrix;

  // Heads & tails (starts & goals)
  NodeSet m_NodeHeads;
  NodeSet m_NodeTails;
};
