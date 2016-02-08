#include "stdafx.h"

#include "Puzzle.h"
#include <iostream>

int main() {
  // Simple maze
  Puzzle p1(5, 4);
  p1.AddHead(Vector2(4, 0));
  p1.AddTail(Vector2(0, 3));
  p1.AddNodeObstacle(Vector2(3, 0), Vector2(4, 0));
  p1.AddNodeObstacle(Vector2(3, 1), Vector2(4, 1));
  p1.AddNodeObstacle(Vector2(1, 1), Vector2(2, 1));
  p1.AddNodeObstacle(Vector2(1, 2), Vector2(2, 2));
  p1.AddNodeObstacle(Vector2(1, 3), Vector2(2, 3));
  p1.AddNodeObstacle(Vector2(0, 2), Vector2(1, 2));
  p1.AddNodeObstacle(Vector2(0, 2), Vector2(0, 3));
  p1.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  p1.Solve();
  assert(p1.GetPaths().size() == 14);
  std::cout << "puzzle 1 solved" << std::endl;
  // TODO: check if there're duplicated paths

  // Maze with essential nodes
  Puzzle p2(4, 4);
  p2.AddHead(Vector2(1, 1));
  p2.AddHead(Vector2(2, 2));
  p2.AddTail(Vector2(1, 0));
  p2.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  p2.AddNodeObstacle(Vector2(0, 0), Vector2(1, 0));
  p2.AddNodeObstacle(Vector2(1, 2), Vector2(1, 3));
  p2.AddNodeObstacle(Vector2(2, 2), Vector2(3, 2));
  p2.AddEssentialNode(Vector2(2, 0));
  p2.AddEssentialNode(Vector2(2, 1));
  p2.AddEssentialNode(Vector2(0, 1));
  p2.AddEssentialNode(Vector2(1, 2));
  p2.AddEssentialNode(Vector2(1, 3));
  p2.AddEssentialNode(Vector2(3, 3));
  p2.Solve();
  assert(p2.GetPaths().size() == 1);
  std::cout << "puzzle 2 solved" << std::endl;

  // Black & white separation
  Puzzle p3(3, 3);
  p3.AddHead(Vector2(2, 0));
  p3.AddTail(Vector2(0, 2));
  p3.SetBlockType(Vector2(0, 0), Black);
  p3.SetBlockType(Vector2(0, 1), Black);
  p3.SetBlockType(Vector2(1, 0), Black);
  p3.SetBlockType(Vector2(1, 1), White);
  p3.Solve();
  assert(p3.GetPaths().size() == 1);
  std::cout << "puzzle 3 solved" << std::endl;

  // Black & white separation
  Puzzle p4(4, 4);
  p4.AddHead(Vector2(3, 0));
  p4.AddTail(Vector2(2, 0));
  p4.SetBlockType(Vector2(0, 0), Black);
  p4.SetBlockType(Vector2(0, 1), Black);
  p4.SetBlockType(Vector2(0, 2), Black);
  p4.SetBlockType(Vector2(1, 0), Black);
  p4.SetBlockType(Vector2(1, 2), Black);
  p4.SetBlockType(Vector2(1, 1), White);
  p4.SetBlockType(Vector2(2, 0), White);
  p4.SetBlockType(Vector2(2, 1), White);
  p4.SetBlockType(Vector2(2, 2), White);
  p4.Solve();
  assert(p4.GetPaths().size() == 1);
  std::cout << "puzzle 4 solved" << std::endl;

  // Black & white separation
  Puzzle p5(5, 5);
  p5.AddHead(Vector2(4, 0));
  p5.AddTail(Vector2(0, 1));
  p5.SetBlockType(Vector2(0, 0), Black);
  p5.SetBlockType(Vector2(0, 3), Black);
  p5.SetBlockType(Vector2(1, 0), Black);
  p5.SetBlockType(Vector2(1, 1), Black);
  p5.SetBlockType(Vector2(1, 2), Black);
  p5.SetBlockType(Vector2(1, 3), Black);
  p5.SetBlockType(Vector2(2, 0), Black);
  p5.SetBlockType(Vector2(2, 2), Black);
  p5.SetBlockType(Vector2(2, 3), Black);
  p5.SetBlockType(Vector2(3, 3), Black);
  p5.SetBlockType(Vector2(0, 2), White);
  p5.SetBlockType(Vector2(2, 1), White);
  p5.SetBlockType(Vector2(3, 0), White);
  p5.SetBlockType(Vector2(3, 1), White);
  p5.SetBlockType(Vector2(3, 2), White);
  p5.Solve();
  std::cout << p5.GetPaths().size() << std::endl;
  std::cout << "puzzle 5 solved" << std::endl;

  return 0;
}
