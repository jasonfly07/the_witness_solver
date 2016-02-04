#include "stdafx.h"

#include "Puzzle.h"
#include <iostream>

int main() {
  // Simple maze
  Puzzle p1(5, 4);
  p1.AddHead(Vector2(4, 0));
  p1.AddTail(Vector2(0, 3));
  p1.AddObstacle(Vector2(3, 0), Vector2(4, 0));
  p1.AddObstacle(Vector2(3, 1), Vector2(4, 1));
  p1.AddObstacle(Vector2(1, 1), Vector2(2, 1));
  p1.AddObstacle(Vector2(1, 2), Vector2(2, 2));
  p1.AddObstacle(Vector2(1, 3), Vector2(2, 3));
  p1.AddObstacle(Vector2(0, 2), Vector2(1, 2));
  p1.AddObstacle(Vector2(0, 2), Vector2(0, 3));
  p1.AddObstacle(Vector2(0, 0), Vector2(0, 1));
  p1.Solve();
  assert(p1.GetPaths().size() == 14);
  // TODO: check if there're duplicated paths

  // Maze with essential nodes
  Puzzle p2(4, 4);
  p2.AddHead(Vector2(1, 1));
  p2.AddHead(Vector2(2, 2));
  p2.AddTail(Vector2(1, 0));
  p2.AddObstacle(Vector2(0, 0), Vector2(0, 1));
  p2.AddObstacle(Vector2(0, 0), Vector2(1, 0));
  p2.AddObstacle(Vector2(1, 2), Vector2(1, 3));
  p2.AddObstacle(Vector2(2, 2), Vector2(3, 2));
  p2.AddEssential(Vector2(2, 0));
  p2.AddEssential(Vector2(2, 1));
  p2.AddEssential(Vector2(0, 1));
  p2.AddEssential(Vector2(1, 2));
  p2.AddEssential(Vector2(1, 3));
  p2.AddEssential(Vector2(3, 3));
  p2.Solve();
  assert(p2.GetPaths().size() == 1);

  // Black & white separation
  Puzzle p3(5, 5);
  p3.SetBlockType(Vector2(0, 0), Black);
  p3.SetBlockType(Vector2(0, 3), Black);
  p3.SetBlockType(Vector2(1, 0), Black);
  p3.SetBlockType(Vector2(1, 1), Black);
  p3.SetBlockType(Vector2(1, 2), Black);
  p3.SetBlockType(Vector2(1, 3), Black);
  p3.SetBlockType(Vector2(2, 0), Black);
  p3.SetBlockType(Vector2(2, 2), Black);
  p3.SetBlockType(Vector2(2, 3), Black);
  p3.SetBlockType(Vector2(3, 3), Black);
  p3.SetBlockType(Vector2(0, 2), White);
  p3.SetBlockType(Vector2(2, 1), White);
  p3.SetBlockType(Vector2(3, 0), White);
  p3.SetBlockType(Vector2(3, 1), White);
  p3.SetBlockType(Vector2(3, 2), White);

  for (auto& block : p3.GetBlock(0, 2).neighborSet) {
    std::cout << block->coord << std::endl;
  }

  return 0;
}
