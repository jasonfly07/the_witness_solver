#pragma once
#include "stdafx.h"

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

// A node on the node map.
// Contains coordinates, its reachable naighbors, and some extra info.
struct Node {
  Node() {
    InitNode(0, 0);
  }
  Node(int r, int c) {
    InitNode(r, c);
  }
  void InitNode(int r, int c) {
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
typedef std::vector<Node*> NodeVector;
typedef std::vector<std::vector<Node>> NodeMatrix;

// A path object is used by the solver to record the history of searching
// It contains all node visited, essential counts, etc.
struct Path {

  Path() {}

  void AddNode(Node* node) {
    visited.insert(node);
    path.push_back(node);
    if (node->isEssential) visitedEssentials.insert(node);
    if (node->isTail)      visitedTails.insert(node);
  }

  bool HasVisited(Node* node) {
    return visited.count(node) == 1 ? true : false;
  }

  NodeSet visited;
  NodeSet visitedTails;
  NodeSet visitedEssentials;
  NodeVector path;
};

// A block on the block map.
struct Block {
  Block() {
    InitBlock(0, 0);
  }
  Block(int r, int c) {
    InitBlock(r, c);
  }
  void InitBlock(int r, int c) {
    coord = Vector2(r, c);
  }

  Vector2 coord;
};