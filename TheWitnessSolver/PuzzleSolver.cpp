#include "PuzzleSolver.h"

void PuzzleSolver::Solve() {

  // Clear the solution container
  m_Paths.clear();

  // Check if there're black/white blocks to solve
  // If yes, convert BW blocks pair to essential nodes
  m_HasBlackWhite = m_PuzzlePtr->CheckBlackWhiteBlocks();
  if (m_HasBlackWhite) {
    m_PuzzlePtr->PreprocessBlackWhiteBlocks();
  }

  // Create the stack for DFS
  std::stack<Path> pathStack;
  for (const auto& head : m_PuzzlePtr->GetHeads()) {
    Path path(m_PuzzlePtr);
    path.AddNode(head);
    pathStack.push(path);
  }

  // Perform DFS
  while (!pathStack.empty()) {
    Path currPath = pathStack.top();
    pathStack.pop();

    // Perform additional evaluation if the current path
    // has reached a goal (tail)
    if (currPath.GetPath().back()->isTail) {
      // Essential nodes evaluation
      if (m_PuzzlePtr->HasEssentialNode()) {
        // Give up on this path if it has insufficient essential node count
        if (!currPath.HasCollectedAllEssentialNodes()) {
          continue;
        }
      }

      // std::cout << "survived" << std::endl;
      // If currPath survives all the checks above, include it in m_Paths
      m_Paths.push_back(currPath);
    }

    // If the current path has no exit left, there's no need to further explore it
    if (!currPath.HasTailLeft()) {
      continue;
    }

    // Heuristic:
    // There're at most 3 unvisited neighbors, so 3 sides to explore
    // If none of them are essential sides, proceed as usual
    // If 1 of them is an (unvisited) essential side, we HAVE to take it
    // (otherwise there's no chance of stepping on it later)
    // If 2 or 3 of them are (unvisited) essential sides, this path is screwed
    int currEssentialSideCount = 0;
    Node& currNode = *(currPath.GetPath().back());
    for (const auto& neighbor : currPath.GetPath().back()->neighborSet) {
      if (!currPath.HasVisitedNode(neighbor)) {
        if (m_PuzzlePtr->GetEssentialSides().count(Side(&currNode, neighbor)) == 1) {
          currEssentialSideCount++;
        }
      }
    }
    if (currEssentialSideCount == 0) {
      for (const auto& neighbor : currPath.GetPath().back()->neighborSet) {
        if (!currPath.HasVisitedNode(neighbor)) {
          Path newPath(currPath);
          newPath.AddNode(neighbor);
          pathStack.push(newPath);
        }
      }
    }
    else if (currEssentialSideCount == 1) {
      for (const auto& neighbor : currPath.GetPath().back()->neighborSet) {
        if (!currPath.HasVisitedNode(neighbor)) {
          if (m_PuzzlePtr->GetEssentialSides().count(Side(&currNode, neighbor)) == 1) {
            Path newPath(currPath);
            newPath.AddNode(neighbor);
            pathStack.push(newPath);
          }
        }
      }
    }
    else {
      // If currEssentialSideCount > 1, do nothing
    }
  }
}