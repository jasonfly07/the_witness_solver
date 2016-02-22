#pragma once
#include "stdafx.h"

#include "Vector2.h"
#include <iostream>
#include <unordered_set>
#include <vector>

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
    onEdge = false;
    neighborOffsets.clear();
  }
  Vector2Set GetNeighborCoords() {
    Vector2Set neighborCoords;
    for (const auto& offset : neighborOffsets) {
      neighborCoords.insert(coord + offset);
    }
    return neighborCoords;
  }

  Vector2 coord;
  Vector2Set neighborOffsets;
  bool isEssential;
  bool isHead;
  bool isTail;
  bool onEdge;
};
typedef std::unordered_set<Node*> NodePtrSet;
typedef std::vector<Node*>        NodePtrVector;
typedef std::vector<std::vector<Node>> NodeMatrix;

// Block type
enum BlockType {
  // Default
  Empty,

  // Black & white separation
  White,
  Black,

  // Tetris (Oriented)
  // Angles are counter-clockwise
  // TODO: all BlockTypes >= 3 are tetris for now;
  // this is subject to change when more  non-tetris types are added
  Square1x1, Square2x2,
  Line1x2, Line2x1,
  Line1x3, Line3x1,
  Line1x4, Line4x1,
  L2x2_0, L2x2_90, L2x2_180, L2x2_270,
  L3x2_0, L3x2_90, L3x2_180, L3x2_270,
  L2x3_0, L2x3_90, L2x3_180, L2x3_270,
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
    type = Empty;
    neighborOffsets.clear();
    passed = false;
    visited = false;
  }
  Vector2Set GetNeighborCoords() {
    Vector2Set neighborCoords;
    for (const auto& offset : neighborOffsets) {
      neighborCoords.insert(coord + offset);
    }
    return neighborCoords;
  }

  Vector2 coord;
  Vector2Set neighborOffsets;
  BlockType type;
  bool passed;  // marked true if the whole segment passes every available check
  bool visited; // used by segmentation
};
typedef std::unordered_set<Block*>            BlockPtrSet;
typedef std::unordered_map<Block*, BlockType> BlockPtrHashMap;
typedef std::vector<BlockPtrSet>              BlockPtrSetVector;
typedef std::vector<std::vector<Block>>       BlockMatrix;

// A side is a line connecting 2 adjacent nodes
// When initialized, the order of node1 & node2 is rearranged
// ex. [1, 2] comes before [2, 2]
// ex. [1, 2] comes before [1, 3]
struct Side {
  Side() {}
  Side(Node* n1, Node* n2) {
    // Make sure the 2 nodes are adjacent
    ASSERT(n1->coord.DistTo(n2->coord) == 1);

    if (n1->coord.r < n2->coord.r) {
      node1 = n1;
      node2 = n2;
    }
    else if (n1->coord.r == n2->coord.r) {
      if (n1->coord.c <= n2->coord.c) {
        node1 = n1;
        node2 = n2;
      }
      else {
        node1 = n2;
        node2 = n1;
      }
    }
    else {
      node1 = n2;
      node2 = n1;
    }
  }

  // The side is vertical if not horizontal
  bool IsHorizontal() const {
    return node1->coord.r == node2->coord.r;
  }

  // TODO: we only need to check the first case now
  bool operator==(const Side& other) const {
    if ((node1->coord == other.node1->coord && node2->coord == other.node2->coord) ||
      (node1->coord == other.node2->coord && node2->coord == other.node1->coord)) {
      return true;
    }
    else return false;
  }

  bool operator!=(const Side& other) const {
    return !(*this == other);
  }

  Node* node1;
  Node* node2;
};
typedef std::unordered_set<Side> SideSet;

namespace std {
  template <>
  struct hash<Side> {
    size_t operator()(const Side& side) const {
      // Compute individual hash values for two data members and combine them using XOR and bit shifting
      return ((hash<Node*>()(side.node1) ^ (hash<Node*>()(side.node2) << 1)) >> 1);
    }
  };
}

// This is for drawing the puzzle
typedef std::vector<std::vector<char>> DisplayMatrix;
