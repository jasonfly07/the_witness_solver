#include "stdafx.h"
#include "Puzzle.h"

#include <iostream>

int main() {
  Puzzle p1(5, 4);

  for (auto& vec : p1.m_NodeMatrix[3][1].neightborList) {
    std::cout << vec << std::endl;
  }
  

  return 0;
}

