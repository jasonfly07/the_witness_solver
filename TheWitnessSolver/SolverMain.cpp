#include "stdafx.h"

#include "Puzzle.h"
#include <iostream>

int main() {
  // Simple maze
  //Puzzle p1(5, 4);
  //p1.AddHead(Vector2(4, 0));
  //p1.AddTail(Vector2(0, 3));
  //p1.AddObstacle(Vector2(3, 0), Vector2(4, 0));
  //p1.AddObstacle(Vector2(3, 1), Vector2(4, 1));
  //p1.AddObstacle(Vector2(1, 1), Vector2(2, 1));
  //p1.AddObstacle(Vector2(1, 2), Vector2(2, 2));
  //p1.AddObstacle(Vector2(1, 3), Vector2(2, 3));
  //p1.AddObstacle(Vector2(0, 2), Vector2(1, 2));
  //p1.AddObstacle(Vector2(0, 2), Vector2(0, 3));
  //p1.AddObstacle(Vector2(0, 0), Vector2(0, 1));
  //p1.Solve();
  //auto& path = p1.GetPaths()[11];
  //for (auto& node : path.path) {
  //  std::cout << node->coord << std::endl;
  //}
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
  auto& path = p2.GetPaths()[0];
  for (auto& node : path.path) {
    std::cout << node->coord << std::endl;
  }

  return 0;
}
