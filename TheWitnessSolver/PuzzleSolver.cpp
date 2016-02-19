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

      // Make a copy, since a path can still continue exploring after reaching a tail
      Path endPath = currPath;

      // At this point there would be 1 - 2 unprocessed segments.
      // Find them and process them.
      bool validEndPath = endPath.ProcessRemainingSegments();

      if (validEndPath) {
        // Additional essential nodes evaluation
        if (m_PuzzlePtr->HasEssentialNode()) {
          // Give up on this path if it has insufficient essential node count
          if (!endPath.HasCollectedAllEssentialNodes()) {
            continue;
          }
        }

        // If currPath survives all the checks above, include it in m_Paths
        //std::cout << "survived" << std::endl;
        m_Paths.push_back(endPath);
        if (m_MaxNumSolutions != -1 && m_Paths.size() == m_MaxNumSolutions) {
          return;
        }
      }
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
    for (const auto& neighborCoord : currPath.GetPath().back()->GetNeighborCoords()) {
      Node& neighbor = m_PuzzlePtr->GetNode(neighborCoord);
      if (!currPath.HasVisitedNode(&neighbor)) {
        if (m_PuzzlePtr->GetEssentialSides().count(Side(&currNode, &neighbor)) == 1) {
          currEssentialSideCount++;
        }
      }
    }
    if (currEssentialSideCount == 0) {
      for (const auto& neighborCoord : currPath.GetPath().back()->GetNeighborCoords()) {
        Node& neighbor = m_PuzzlePtr->GetNode(neighborCoord);
        if (!currPath.HasVisitedNode(&neighbor)) {
          Path newPath(currPath);
          if(newPath.AddNode(&neighbor)) {
            pathStack.push(newPath);
          }
        }
      }
    }
    else if (currEssentialSideCount == 1) {
      for (const auto& neighborCoord : currPath.GetPath().back()->GetNeighborCoords()) {
        Node& neighbor = m_PuzzlePtr->GetNode(neighborCoord);
        if (!currPath.HasVisitedNode(&neighbor)) {
          if (m_PuzzlePtr->GetEssentialSides().count(Side(&currNode, &neighbor)) == 1) {
            Path newPath(currPath);
            if (newPath.AddNode(&neighbor)) {
              pathStack.push(newPath);
            }
          }
        }
      }
    }
    else {
      // If currEssentialSideCount > 1, do nothing
    }
  }
}