#include "stdafx.h"
#include "Puzzle.h"

#include <iostream>

int main() {
  Puzzle p1(5, 4);

  p1.AddHead(Vector2(1, 2));
  p1.AddHead(Vector2(3, 0));
  p1.AddTail(Vector2(3, 0));
  p1.AddTail(Vector2(3, 1));
  p1.AddHead(Vector2(3, 1));
  p1.AddHead(Vector2(0, 2));

  for (auto& t : p1.GetHeads()) {
    std::cout << "head : " << t->coord << std::endl;
  }
  for (auto& t : p1.GetTails()) {
    std::cout << "tail : " << t->coord << std::endl;
  }

  std::cout << p1.GetNode(Vector2(0, 0)).isHead << std::endl;
  std::cout << p1.GetNode(Vector2(0, 0)).isTail << std::endl;

  return 0;
}
