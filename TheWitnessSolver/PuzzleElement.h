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

// A node on the node matrix.
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
    neighborSet.clear();
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
// It contains all node visited, essential node counts, etc.
struct Path {

  Path() {}

  void AddNode(Node* node) {
    visited.insert(node);
    path.push_back(node);
    if (node->isEssential) visitedEssentialNodes.insert(node);
    if (node->isTail)      visitedTails.insert(node);
  }

  bool HasVisited(Node* node) {
    return visited.count(node) == 1 ? true : false;
  }

  NodeSet visited;
  NodeSet visitedTails;
  NodeSet visitedEssentialNodes;
  NodeVector path;
};

// Block type
enum BlockType {
  Empty,
  White,
  Black
};

// A block on the block matrix.
struct Block {
  Block() {
    InitBlock(0, 0);
  }
  Block(int r, int c) {
    InitBlock(r, c);
  }
  void InitBlock(int r, int c) {
    coord = Vector2(r, c);
    type  = Empty;
    clusterID = -1;
    neighborSet.clear();
  }

  std::unordered_set<Block*> neighborSet;
  BlockType type;
  Vector2 coord;
  int clusterID;
};
typedef std::vector<std::vector<Block>> BlockMatrix;
// A side is a line connecting 2 adjacent nodes
struct Side {
  Side() {}
  Side(Node* n1, Node* n2) {
    node1 = n1;
    node2 = n2;
  }
  bool operator==(const Side& other) {
    if ((node1->coord == other.node1->coord && node2->coord == other.node2->coord) ||
        (node1->coord == other.node2->coord && node2->coord == other.node1->coord)) {
      return true;
    }
    else return false;
  }
  bool operator!=(const Side& other) {
    return !(*this == other);
  }

  Node* node1;
  Node* node2;
};
