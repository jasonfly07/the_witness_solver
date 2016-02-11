#pragma once
#include "PuzzleElement.h"

// A path object is used by the solver to record the history of searching
// It contains all node visited, essential node counts, etc.
struct Path {

  // Since we're gonna maintain a block matrix for every path, we have to specify it
  // when initializing a path
  Path(const BlockMatrix& blockMat) {
    blockMatrix = blockMat;
    touchCount = 0;
    leaveCount = 0;
  }

  void AddNode(Node* node) {
    // There're 2 cases at start: head is on edge & not on edge
    // if the head is on edge, set touchCount to 1
    if (path.size() == 0 && node->isHead) {
      touchCount = 1;
    }

    // See if this step is leaving the edge
    if (path.size() > 0) {
      if (!(node->onEdge) && path.end()[-1]->onEdge) {
        leaveCount++;
      }
    }

    // See if this step is touching the edge
    if (path.size() > 0) {
      if (node->onEdge && !(path.end()[-1]->onEdge)) {
        touchCount++;
      }
    }

    // TODO:
    // If leaveCount >= 1, and touchCount = leaveCount + 1
    // in the next step, a segment will be created

    // Finally, insert the node into relevant containers
    visitedNodes.insert(node);
    path.push_back(node);
    if (node->isEssential) visitedEssentialNodes.insert(node);
    if (node->isTail)      visitedTails.insert(node);
  }

  bool HasVisitedNode(Node* node) {
    return visitedNodes.count(node) == 1 ? true : false;
  }

  void Print() const {
    std::cout << "touch = " << touchCount;
    std::cout << ", leave = " << leaveCount << std::endl;
    std::cout << "path : ";
    for (const auto& node : path) {
      std::cout << node->coord << " ";
    }
    std::cout << std::endl;
  }

  // Records the number of times the path touching/leaving the edge
  int touchCount;
  int leaveCount;

  NodeSet visitedNodes;
  NodeSet visitedTails;
  NodeSet visitedEssentialNodes;
  NodeVector path;

  BlockMatrix blockMatrix;
};