#include "stdafx.h"

#include "Puzzle.h"
#include "PuzzleSolver.h"
#include <iostream>
#include <stdexcept>

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds MilliSecond;

// Utility for run solver and profiling
static void SolvePuzzle(Puzzle& p) {
  std::chrono::time_point<HighResClock> start, end;
  start = HighResClock::now();
  PuzzleSolver ps(p, 1);
  ps.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << p.GetName() << " solved in " << ms.count() << " ms" << std::endl;

  // Draw the first solution
  ps.GetPaths()[0].Draw();
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

  SolvePuzzle(p);
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

  SolvePuzzle(p);
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

  SolvePuzzle(p);
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

  SolvePuzzle(p);
}

// Black & white separation
void PuzzleBW2() {
  Puzzle p(4, 4);
  p.SetName("puzzleBW2");
  p.AddHead(Vector2(3, 0));
  p.AddTail(Vector2(2, 0));
  p.SetBlockType(Vector2(0, 0), Black);
  p.SetBlockType(Vector2(0, 1), Black);
  p.SetBlockType(Vector2(0, 2), Black);
  p.SetBlockType(Vector2(1, 0), Black);
  p.SetBlockType(Vector2(1, 2), Black);
  p.SetBlockType(Vector2(1, 1), White);
  p.SetBlockType(Vector2(2, 0), White);
  p.SetBlockType(Vector2(2, 1), White);
  p.SetBlockType(Vector2(2, 2), White);

  SolvePuzzle(p);
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

  SolvePuzzle(p);
}

// Black & white separation
void PuzzleBW4() {
  Puzzle p(4, 4);
  p.SetName("puzzleBW4");
  p.AddHead(Vector2(3, 0));
  p.AddTail(Vector2(0, 3));
  p.SetBlockType(Vector2(0, 0), Black);
  p.SetBlockType(Vector2(0, 1), Black);
  p.SetBlockType(Vector2(0, 2), Black);
  p.SetBlockType(Vector2(1, 0), Black);
  p.SetBlockType(Vector2(1, 2), Black);
  p.SetBlockType(Vector2(1, 1), White);
  p.SetBlockType(Vector2(2, 0), White);
  p.SetBlockType(Vector2(2, 1), White);
  p.SetBlockType(Vector2(2, 2), White);

  SolvePuzzle(p);
}

// Black & white separation
void PuzzleBW5() {
  Puzzle p(5, 5);
  p.SetName("puzzleBW5");
  p.AddHead(Vector2(2, 2));
  p.AddTail(Vector2(0, 4));
  p.SetBlockType(Vector2(1, 1), Black);
  p.SetBlockType(Vector2(1, 2), Black);
  p.SetBlockType(Vector2(2, 1), Black);
  p.SetBlockType(Vector2(2, 2), Black);
  p.SetBlockType(Vector2(0, 0), White);
  p.SetBlockType(Vector2(0, 1), White);
  p.SetBlockType(Vector2(0, 2), White);
  p.SetBlockType(Vector2(0, 3), White);
  p.SetBlockType(Vector2(1, 3), White);
  p.SetBlockType(Vector2(2, 3), White);
  p.SetBlockType(Vector2(3, 3), White);

  SolvePuzzle(p);
}

// Black & white separation + essential nodes
void PuzzleEssentialBW1() {
  Puzzle p(8, 8);
  p.SetName("puzzleEssentialBW1");
  p.AddHead(Vector2(7, 0));
  p.AddHead(Vector2(2, 4));
  p.AddHead(Vector2(5, 2));
  p.AddHead(Vector2(4, 6));
  p.AddTail(Vector2(0, 0));
  p.AddTail(Vector2(0, 7));
  p.AddTail(Vector2(7, 7));
  p.SetBlockType(Vector2(0, 0), Black);
  p.SetBlockType(Vector2(0, 5), Black);
  p.SetBlockType(Vector2(1, 3), Black);
  p.SetBlockType(Vector2(1, 4), Black);
  p.SetBlockType(Vector2(5, 6), Black);
  p.SetBlockType(Vector2(6, 6), Black);
  p.SetBlockType(Vector2(0, 1), White);
  p.SetBlockType(Vector2(1, 0), White);
  p.SetBlockType(Vector2(0, 6), White);
  p.SetBlockType(Vector2(2, 3), White);
  p.SetBlockType(Vector2(2, 4), White);
  p.SetBlockType(Vector2(5, 2), White);
  p.SetBlockType(Vector2(6, 5), White);
  p.AddEssentialSide(Vector2(0, 6), Vector2(0, 7));
  p.AddEssentialSide(Vector2(1, 7), Vector2(0, 7));
  p.AddEssentialSide(Vector2(3, 7), Vector2(4, 7));
  p.AddEssentialSide(Vector2(4, 6), Vector2(4, 7));
  p.AddEssentialSide(Vector2(5, 1), Vector2(5, 2));
  p.AddEssentialSide(Vector2(6, 0), Vector2(7, 0));
  p.AddEssentialSide(Vector2(7, 0), Vector2(7, 1));
  p.AddEssentialSide(Vector2(7, 5), Vector2(7, 6));

  SolvePuzzle(p);
}


int main() {

  PuzzleSimpleMaze1();
  PuzzleEssential1();
  PuzzleEssential2();
  PuzzleBW1();
  PuzzleBW2();
  PuzzleBW3();
  PuzzleBW4();
  PuzzleBW5();
  PuzzleEssentialBW1();

  return 0;
}
