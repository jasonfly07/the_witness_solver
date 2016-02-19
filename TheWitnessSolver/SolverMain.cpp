#include "stdafx.h"

#include "Puzzle.h"
#include "PuzzleSolver.h"
#include <iostream>
#include <stdexcept>

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds MilliSecond;

// Utility for run solver and profiling
static void SolvePuzzle(Puzzle& p, int numSol) {
  std::chrono::time_point<HighResClock> start, end;
  start = HighResClock::now();
  PuzzleSolver ps(p);
  ps.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << p.GetName() << " solved in " << ms.count() << " ms, ";
  std::cout << "found " << ps.GetPaths().size() << " / " << numSol << " solutions. ";
  if (ps.GetPaths().size() != numSol) {
    std::cout << "Mismatch!" << std::endl;
  }
  else {
    std::cout << std::endl;
  }
}

// Simple maze
void PuzzleSimpleMaze1() {
  Puzzle p(5, 4);
  p.SetName("PuzzleSimpleMaze1");
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

  SolvePuzzle(p, 14);
}

// Maze with essential nodes
void PuzzleEssential1() {
  Puzzle p(4, 4);
  p.SetName("PuzzleEssential1");
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

  SolvePuzzle(p, 1);
}

// Maze with essential nodes
void PuzzleEssential2() {
  Puzzle p(5, 5);
  p.SetName("PuzzleEssential2");
  p.AddHead(Vector2(2, 2));
  p.AddTail(Vector2(0, 4));
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      p.AddEssentialNode(Vector2(r, c));
    }
  }

  SolvePuzzle(p, 48);
}

// Black & white separation
void PuzzleBW1() {
  Puzzle p(3, 3);
  p.SetName("PuzzleBW1");
  p.AddHead(Vector2(2, 0));
  p.AddTail(Vector2(0, 2));
  p.SetBlockType(Vector2(0, 0), Black);
  p.SetBlockType(Vector2(0, 1), Black);
  p.SetBlockType(Vector2(1, 0), Black);
  p.SetBlockType(Vector2(1, 1), White);

  SolvePuzzle(p, 1);
}

// Black & white separation
void PuzzleBW3() {
  Puzzle p(5, 5);
  p.SetName("PuzzleBW3");
  p.AddHead(Vector2(4, 0));
  p.AddTail(Vector2(0, 1));
  p.SetBlockType(Vector2(0, 0), Black);
  p.SetBlockType(Vector2(0, 3), Black);
  p.SetBlockType(Vector2(1, 0), Black);
  p.SetBlockType(Vector2(1, 1), Black);
  p.SetBlockType(Vector2(1, 2), Black);
  p.SetBlockType(Vector2(1, 3), Black);
  p.SetBlockType(Vector2(2, 0), Black);
  p.SetBlockType(Vector2(2, 2), Black);
  p.SetBlockType(Vector2(2, 3), Black);
  p.SetBlockType(Vector2(3, 3), Black);
  p.SetBlockType(Vector2(0, 2), White);
  p.SetBlockType(Vector2(2, 1), White);
  p.SetBlockType(Vector2(3, 0), White);
  p.SetBlockType(Vector2(3, 1), White);
  p.SetBlockType(Vector2(3, 2), White);

  SolvePuzzle(p, 2);
}

int main() {

  PuzzleSimpleMaze1();
  PuzzleEssential1();
  PuzzleEssential2();
  PuzzleBW1();
  //PuzzleBW3();


  return 0;
}
