#include "stdafx.h"
#include "Puzzle.h"

#include <iostream>

int main() {
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
  for (auto& node : p1.GetPath()) {
    std::cout << node->coord << std::endl;
  }

  //Puzzle p1(2, 3);
  //p1.AddHead(Vector2(0, 0));
  //p1.AddTail(Vector2(1, 2));
  //p1.AddObstacle(Vector2(0, 1), Vector2(1, 1));
  //p1.Solve();

  return 0;
}
