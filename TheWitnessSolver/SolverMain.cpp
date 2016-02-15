#include "stdafx.h"

#include "Puzzle.h"
#include "PuzzleSolver.h"
#include <iostream>
#include <stdexcept>

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds MilliSecond;

// Simple maze
void PuzzleSimpleMaze1() {
  std::chrono::time_point<HighResClock> start, end;

  Puzzle p(5, 4);
  p.AddHead(Vector2(4, 0));
  p.AddTail(Vector2(0, 3));
  p.AddNodeObstacle(Vector2(3, 0), Vector2(4, 0));
  p.AddNodeObstacle(Vector2(3, 1), Vector2(4, 1));
  p.AddNodeObstacle(Vector2(1, 1), Vector2(2, 1));
  p.AddNodeObstacle(Vector2(1, 2), Vector2(2, 2));
  p.AddNodeObstacle(Vector2(1, 3), Vector2(2, 3));
  p.AddNodeObstacle(Vector2(0, 2), Vector2(1, 2));
  p.AddNodeObstacle(Vector2(0, 2), Vector2(0, 3));
  p.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));

  start = HighResClock::now();
  PuzzleSolver ps(p);
  ps.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleSimpleMaze1 solved in " << ms.count() << " ms" << std::endl;
  if (ps.GetPaths().size() != 14) {
    std::cout << "solution mismatch" << std::endl;
  }
}

// Maze with essential nodes
void PuzzleEssential1() {
  std::chrono::time_point<HighResClock> start, end;

  Puzzle p(4, 4);
  p.AddHead(Vector2(1, 1));
  p.AddHead(Vector2(2, 2));
  p.AddTail(Vector2(1, 0));
  p.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  p.AddNodeObstacle(Vector2(0, 0), Vector2(1, 0));
  p.AddNodeObstacle(Vector2(1, 2), Vector2(1, 3));
  p.AddNodeObstacle(Vector2(2, 2), Vector2(3, 2));
  p.AddEssentialNode(Vector2(2, 0));
  p.AddEssentialNode(Vector2(2, 1));
  p.AddEssentialNode(Vector2(0, 1));
  p.AddEssentialNode(Vector2(1, 2));
  p.AddEssentialNode(Vector2(1, 3));
  p.AddEssentialNode(Vector2(3, 3));

  start = HighResClock::now();
  PuzzleSolver ps(p);
  ps.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "PuzzleEssential1 solved in " << ms.count() << " ms" << std::endl;
  if (ps.GetPaths().size() != 1) {
    std::cout << "solution mismatch" << std::endl;
  }
}

// Maze with essential nodes
void PuzzleEssential2() {
  std::chrono::time_point<HighResClock> start, end;

  Puzzle p(5, 5);
  p.AddHead(Vector2(2, 2));
  p.AddTail(Vector2(0, 4));
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      p.AddEssentialNode(Vector2(r, c));
    }
  }

  start = HighResClock::now();
  PuzzleSolver ps(p);
  ps.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "PuzzleEssential2 solved in " << ms.count() << " ms" << std::endl;
  if (ps.GetPaths().size() != 48) {
    std::cout << "solution mismatch" << std::endl;
  }
}


int main() {

  //PuzzleSimpleMaze1();
  //PuzzleEssential1();
  //PuzzleEssential2();

  Puzzle p(4, 5);
  p.AddHead(Vector2(1, 1));
  p.AddTail(Vector2(3, 3));
  Path path(&p);
  path.AddNode(&p.GetNode(1, 1)); path.Print();
  path.AddNode(&p.GetNode(1, 0)); path.Print();
  path.AddNode(&p.GetNode(2, 0)); path.Print();
  path.AddNode(&p.GetNode(2, 1)); path.Print();
  path.AddNode(&p.GetNode(3, 1)); path.Print();
  path.AddNode(&p.GetNode(3, 2)); path.Print();
  path.AddNode(&p.GetNode(2, 2)); path.Print();
  path.AddNode(&p.GetNode(1, 2)); path.Print();
  path.AddNode(&p.GetNode(0, 2)); path.Print();
  path.AddNode(&p.GetNode(0, 3)); path.Print();
  path.AddNode(&p.GetNode(1, 3)); path.Print();
  path.AddNode(&p.GetNode(2, 3)); path.Print();
  path.AddNode(&p.GetNode(2, 4)); path.Print();
  path.AddNode(&p.GetNode(3, 4)); path.Print();
  path.AddNode(&p.GetNode(3, 3)); path.Print();

  std::cout << "herp derp" << std::endl;
  for (auto& t : path.m_BlockMap.GetBlock(0, 0).neighborSet) {
    std::cout << t->coord << std::endl;
  }

  return 0;
}
