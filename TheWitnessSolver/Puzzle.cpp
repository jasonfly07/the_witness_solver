#include "Puzzle.h"

#include <cstdlib>
#include <stack>

Node& Puzzle::GetNode(int r, int c) {
  assert(ValidNodeCoord(Vector2(r, c)));
  return m_NodeMatrix[r][c];
}
Node& Puzzle::GetNode(const Vector2& vec) {
  assert(ValidNodeCoord(vec));
  return m_NodeMatrix[vec.r][vec.c];
}

Block& Puzzle::GetBlock(int r, int c) {
  assert(ValidBlockCoord(Vector2(r, c)));
  return m_BlockMatrix[r][c];
}
Block& Puzzle::GetBlock(const Vector2& vec) {
  assert(ValidBlockCoord(vec));
  return m_BlockMatrix[vec.r][vec.c];
}

void Puzzle::ResetPuzzle(int nodeRow, int nodeCol) {
  // Since there's at least one block, the min size of node matrix is 2x2
  assert(nodeRow > 1 && nodeCol > 1);

  // Set the size of node matrix
  m_NodeMatrix.clear();
  m_NodeMatrix.resize(nodeRow, std::vector<Node>(nodeCol));

  // Set the size of block matrix
  m_BlockMatrix.clear();
  m_BlockMatrix.resize(nodeRow - 1, std::vector<Block>(nodeCol - 1));

  // Initialize all the nodes
  for (int r = 0; r < NodeRows(); r++) {
    for (int c = 0; c < NodeCols(); c++) {
      Node& currNode = m_NodeMatrix[r][c];
      currNode.coord = Vector2(r, c);
    }
  }

  // Reset the neighbors of nodes & blocks
  ResetNodeMatrixConnectivity();
  ResetBlockMatrixConnectivity();

  // Initialize all the blocks
  for (int r = 0; r < nodeRow - 1; r++) {
    for (int c = 0; c < nodeCol - 1; c++) {
      Block& currBlock = m_BlockMatrix[r][c];
      currBlock.coord = Vector2(r, c);
    }
  }

  // Reset all auxiliary containers
  m_Paths.clear();
  m_NodeHeads.clear();
  m_NodeTails.clear();
  m_NodeEssentials.clear();
  m_SideEssentials.clear();

  // Reset some flags
  m_HasBlackWhiteBlocks = false;
}

void Puzzle::ResetNodeMatrixConnectivity() {
  for (int r = 0; r < NodeRows(); r++) {
    for (int c = 0; c < NodeCols(); c++) {
      Node& currNode = m_NodeMatrix[r][c];

      // Set reachable neighbors
      currNode.neighborSet.clear();
      Vector2 lCoord(r, c - 1);
      Vector2 rCoord(r, c + 1);
      Vector2 tCoord(r - 1, c);
      Vector2 bCoord(r + 1, c);
      if (ValidNodeCoord(lCoord)) currNode.neighborSet.insert(&GetNode(lCoord));
      if (ValidNodeCoord(rCoord)) currNode.neighborSet.insert(&GetNode(rCoord));
      if (ValidNodeCoord(tCoord)) currNode.neighborSet.insert(&GetNode(tCoord));
      if (ValidNodeCoord(bCoord)) currNode.neighborSet.insert(&GetNode(bCoord));
    }
  }
}

void Puzzle::ResetBlockMatrixConnectivity() {
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      Block& currBlock = m_BlockMatrix[r][c];

      // Set reachable neighbors
      currBlock.neighborSet.clear();
      Vector2 lCoord(r, c - 1);
      Vector2 rCoord(r, c + 1);
      Vector2 tCoord(r - 1, c);
      Vector2 bCoord(r + 1, c);
      if (ValidBlockCoord(lCoord)) currBlock.neighborSet.insert(&GetBlock(lCoord));
      if (ValidBlockCoord(rCoord)) currBlock.neighborSet.insert(&GetBlock(rCoord));
      if (ValidBlockCoord(tCoord)) currBlock.neighborSet.insert(&GetBlock(tCoord));
      if (ValidBlockCoord(bCoord)) currBlock.neighborSet.insert(&GetBlock(bCoord));
    }
  }
}

void Puzzle::ResetBlockMatrixVisitHistory() {
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      Block& currBlock = m_BlockMatrix[r][c];
      currBlock.visited = false;
    }
  }
}

void Puzzle::AddHead(const Vector2& vec) {
  // If vec is already a head, no need to proceed
  if (GetNode(vec).isHead) return;

  // If vec is already a tail, remove it from m_NodeTails first
  if (GetNode(vec).isTail) m_NodeTails.erase(&GetNode(vec));

  m_NodeHeads.insert(&GetNode(vec));
  GetNode(vec).isHead = true;
}

void Puzzle::AddTail(const Vector2& vec) {
  // If vec is already a tail, no need to proceed
  if (GetNode(vec).isTail) return;

  // If vec is already a head, remove it from m_NodeHeads first
  if (GetNode(vec).isHead) m_NodeHeads.erase(&GetNode(vec));

  m_NodeTails.insert(&GetNode(vec));
  GetNode(vec).isTail = true;
}

void Puzzle::AddNodeObstacle(const Vector2& vec1, const Vector2& vec2) {
  Node& node1 = GetNode(vec1);
  Node& node2 = GetNode(vec2);

  // Check if node1 & node2 are adjacent
  // TODO: this is probably unnecessary
  if (node1.neighborSet.count(&node2) == 0 ||
      node2.neighborSet.count(&node1) == 0) {
    return;
  }

  node1.neighborSet.erase(&node2);
  node2.neighborSet.erase(&node1);
}

void Puzzle::AddEssentialNode(const Vector2& vec) {
  Node& node = GetNode(vec);
  node.isEssential = true;
  m_NodeEssentials.insert(&node);
}

void Puzzle::SetBlockType(const Vector2& vec, BlockType type) {
  Block& block = GetBlock(vec);
  block.type = type;
}

void Puzzle::AddBlockObstacle(const Side& side) {
  AddBlockObstacle(side.node1->coord, side.node2->coord);
}

void Puzzle::AddBlockObstacle(const Vector2& vec1, const Vector2& vec2) {
  Node& node1 = GetNode(vec1);
  Node& node2 = GetNode(vec2);

  // No need to proceed if side is on the border
  if (node1.coord.r == 0 && node2.coord.r == 0) return;
  if (node1.coord.c == 0 && node2.coord.c == 0) return;
  if (node1.coord.r == NodeRows() - 1 && node2.coord.r == NodeRows() - 1) return;
  if (node1.coord.c == NodeCols() - 1 && node2.coord.c == NodeCols() - 1) return;

  // Case 1: side is vertical
  if (node1.coord.c == node2.coord.c) {
    int R = std::min(node1.coord.r, node2.coord.r);
    int C = node1.coord.c;
    Block& block1 = GetBlock(R, C - 1);
    Block& block2 = GetBlock(R, C);
    block1.neighborSet.erase(&block2);
    block2.neighborSet.erase(&block1);
  }
  // Case 2: side is horizontal
  else if (node1.coord.r == node2.coord.r) {
    int R = node1.coord.r;
    int C = std::min(node1.coord.c, node2.coord.c);
    Block& block1 = GetBlock(R - 1, C);
    Block& block2 = GetBlock(R, C);
    block1.neighborSet.erase(&block2);
    block2.neighborSet.erase(&block1);
  }
}

void Puzzle::CheckBlackWhiteBlocks() {
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      const Block& currBlock = GetBlock(r, c);
      if ((currBlock.type == Black) || (currBlock.type == White)) {
        m_HasBlackWhiteBlocks = true;
        return;
      }
    }
  }
  m_HasBlackWhiteBlocks = false;
}

void Puzzle::PreprocessBlackWhiteBlocks() {
  // For every block [r, c], process the sides (if valid):
  // 1. between [r, c] and [r, c + 1]
  // 2. between [r, c] and [r + 1, c]
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      const Block& currBlock = GetBlock(r, c);

      // 1. [r, c + 1]
      if (ValidBlockCoord(r, c + 1)) {
        const Block& rightBlock = GetBlock(r, c + 1);
        if ((currBlock.type == White && rightBlock.type == Black) ||
            (currBlock.type == Black && rightBlock.type == White)) {
          m_SideEssentials.insert(Side(&GetNode(r, c + 1), &GetNode(r + 1, c + 1)));
        }
      }

      // 2. [r + 1, c]
      if (ValidBlockCoord(r + 1, c)) {
        const Block& bottomBlock = GetBlock(r + 1, c);
        if ((currBlock.type == White && bottomBlock.type == Black) ||
            (currBlock.type == Black && bottomBlock.type == White)) {
          m_SideEssentials.insert(Side(&GetNode(r + 1, c), &GetNode(r + 1, c + 1)));
        }
      }
    }
  }
}


void Puzzle::Solve() {
  m_Paths.clear();

  // Check if there're black/white blocks to solve
  // If yes, record all the essential sides
  CheckBlackWhiteBlocks();
  if (m_HasBlackWhiteBlocks) {
    PreprocessBlackWhiteBlocks();
  }

  // Create the stack for DFS
  std::stack<Path> pathStack;
  for (const auto& head : m_NodeHeads) {
    Path path;
    path.AddNode(head);
    pathStack.push(path);
  }

  // Perform DFS
  while (!pathStack.empty()) {
    Path currPath = pathStack.top();
    pathStack.pop();

    // Perform additional evaluation if the current path
    // has reached a goal (tail)
    if (currPath.path.back()->isTail) {

      // Essential nodes evaluation
      if (PuzzleHasEssentialNode()) {
        // Give up on this path if it has insufficient essential node count
        if (!PathHasCollectedAllEssentialNodes(currPath)) {
          continue;
        }
      }

      // Block evaluation
      if (m_HasBlackWhiteBlocks) {

        // Give up on this path if it has insufficient essential block count
        if (!PathHasCollectedAllEssentialSides(currPath)) {
          continue;
        }

        // Perform segmentation on block matrix
        // For every segment, check if black/white count is correct
        BlockSetVector segments;
        SegmentBlockMap(currPath, segments);
        bool everySegmentHasCorrectCount = true;
        for (auto& segment : segments) {
          for (auto& block : segment) {
          }
          const bool currSegmentHasCorrectCount = HasValidBlackWhiteCount(segment);
          if (!currSegmentHasCorrectCount) {
            everySegmentHasCorrectCount = false;
            break;
          }
        }
        if (!everySegmentHasCorrectCount) {
          continue;
        }
      }

      // If currPath survives all the checks above, include it in m_Paths
      m_Paths.push_back(currPath);
    }

    // If the current path has no exit left, there's no need to further explore it
    if (!PathHasTailLeft(currPath)) {
      continue;
    }

    //std::cout << m_Paths.size() << std::endl;
    // Iterate through neighbors of the end of path
    for (const auto& neighbor : currPath.path.back()->neighborSet) {
      Path newPath = currPath;
      if (!currPath.HasVisitedNode(neighbor)) {
        newPath.AddNode(neighbor);
        pathStack.push(newPath);
      }
    }
  }
}

bool Puzzle::PuzzleHasEssentialNode() {
  return m_NodeEssentials.size() > 0 ? true : false;
}

bool Puzzle::PathHasCollectedAllEssentialNodes(const Path& path) {
  return path.visitedEssentialNodes.size() == m_NodeEssentials.size() ? true : false;
}

bool Puzzle::PathHasTailLeft(const Path& path) {
  return path.visitedTails.size() == m_NodeTails.size() ? false : true;
}

void Puzzle::SegmentBlockMap(const Path& path, BlockSetVector& segments) {

  for (int i = 0; i < path.path.size() - 1; i++) {
    const Node& node1 = *(path.path[i]);
    const Node& node2 = *(path.path[i + 1]);
    AddBlockObstacle(node1.coord, node2.coord);
  }

  segments.clear();
  for (int r = 0; r < BlockRows(); r++) {
    for (int c = 0; c < BlockCols(); c++) {
      Block& seedBlock = m_BlockMatrix[r][c];
      if (seedBlock.visited == true) continue;

      BlockSet segment;
      std::stack<Block*> blockStack;
      blockStack.push(&seedBlock);
      while (!blockStack.empty()) {
        Block& currBlock = *(blockStack.top());
        blockStack.pop();

        currBlock.visited = true;
        segment.insert(&currBlock);
        for (auto& neighbor : currBlock.neighborSet) {
          if (!neighbor->visited) {
            blockStack.push(neighbor);
          }
        }
      }
      segments.push_back(segment);
    }
  }

  // Reset the block map
  ResetBlockMatrixConnectivity();
  ResetBlockMatrixVisitHistory();
}

bool Puzzle::PathHasCollectedAllEssentialSides(const Path& path) {
  int essentialSideCount = 0;
  for (int i = 0; i < path.path.size() - 1; i++) {
    Side side(path.path[i], path.path[i + 1]);
    if (m_SideEssentials.count(side) == 1) {
      essentialSideCount++;
    }
  }
  return (essentialSideCount == m_SideEssentials.size()) ? true : false;
}


bool Puzzle::HasValidBlackWhiteCount(const BlockSet& segment) {
  bool hasWhite = false;
  bool hasBlack = false;
  for (const auto& block : segment) {
    if (block->type == White) {
      hasWhite = true;
    }
    else if (block->type == Black) {
      hasBlack = true;
    }
    if (hasWhite && hasBlack) {
      return false;
    }
  }
  return true;
}
