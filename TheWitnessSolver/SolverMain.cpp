#include "stdafx.h"

#include "Puzzle.h"
#include <iostream>

int main() {

  typedef std::chrono::high_resolution_clock HighResClock;
  typedef std::chrono::milliseconds MilliSecond;
  std::chrono::time_point<HighResClock> start, end;

  // Simple maze
  Puzzle puzzleSimpleMaze1(5, 4);
  puzzleSimpleMaze1.AddHead(Vector2(4, 0));
  puzzleSimpleMaze1.AddTail(Vector2(0, 3));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(3, 0), Vector2(4, 0));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(3, 1), Vector2(4, 1));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(1, 1), Vector2(2, 1));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(1, 2), Vector2(2, 2));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(1, 3), Vector2(2, 3));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(0, 2), Vector2(1, 2));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(0, 2), Vector2(0, 3));
  puzzleSimpleMaze1.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  start = HighResClock::now();
  puzzleSimpleMaze1.Solve();
  end = HighResClock::now();
  auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleSimpleMaze1 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleSimpleMaze1.GetPaths().size() != 14) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Maze with essential nodes
  Puzzle puzzleEssential1(4, 4);
  puzzleEssential1.AddHead(Vector2(1, 1));
  puzzleEssential1.AddHead(Vector2(2, 2));
  puzzleEssential1.AddTail(Vector2(1, 0));
  puzzleEssential1.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  puzzleEssential1.AddNodeObstacle(Vector2(0, 0), Vector2(1, 0));
  puzzleEssential1.AddNodeObstacle(Vector2(1, 2), Vector2(1, 3));
  puzzleEssential1.AddNodeObstacle(Vector2(2, 2), Vector2(3, 2));
  puzzleEssential1.AddEssentialNode(Vector2(2, 0));
  puzzleEssential1.AddEssentialNode(Vector2(2, 1));
  puzzleEssential1.AddEssentialNode(Vector2(0, 1));
  puzzleEssential1.AddEssentialNode(Vector2(1, 2));
  puzzleEssential1.AddEssentialNode(Vector2(1, 3));
  puzzleEssential1.AddEssentialNode(Vector2(3, 3));
  start = HighResClock::now();
  puzzleEssential1.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleEssential1 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleEssential1.GetPaths().size() != 1) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Maze with essential nodes
  Puzzle puzzleEssential2(5, 5);
  puzzleEssential2.AddHead(Vector2(2, 2));
  puzzleEssential2.AddTail(Vector2(0, 4));
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      puzzleEssential2.AddEssentialNode(Vector2(r, c));
    }
  }
  start = HighResClock::now();
  puzzleEssential2.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleEssential2 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleEssential2.GetPaths().size() != 48) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Black & white separation
  Puzzle puzzleBW1(3, 3);
  puzzleBW1.AddHead(Vector2(2, 0));
  puzzleBW1.AddTail(Vector2(0, 2));
  puzzleBW1.SetBlockType(Vector2(0, 0), Black);
  puzzleBW1.SetBlockType(Vector2(0, 1), Black);
  puzzleBW1.SetBlockType(Vector2(1, 0), Black);
  puzzleBW1.SetBlockType(Vector2(1, 1), White);
  start = HighResClock::now();
  puzzleBW1.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleBW1 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleBW1.GetPaths().size() != 1) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Black & white separation
  Puzzle puzzleBW2(4, 4);
  puzzleBW2.AddHead(Vector2(3, 0));
  puzzleBW2.AddTail(Vector2(2, 0));
  puzzleBW2.SetBlockType(Vector2(0, 0), Black);
  puzzleBW2.SetBlockType(Vector2(0, 1), Black);
  puzzleBW2.SetBlockType(Vector2(0, 2), Black);
  puzzleBW2.SetBlockType(Vector2(1, 0), Black);
  puzzleBW2.SetBlockType(Vector2(1, 2), Black);
  puzzleBW2.SetBlockType(Vector2(1, 1), White);
  puzzleBW2.SetBlockType(Vector2(2, 0), White);
  puzzleBW2.SetBlockType(Vector2(2, 1), White);
  puzzleBW2.SetBlockType(Vector2(2, 2), White);
  start = HighResClock::now();
  puzzleBW2.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleBW2 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleBW2.GetPaths().size() != 1) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Black & white separation
  Puzzle puzzleBW3(5, 5);
  puzzleBW3.AddHead(Vector2(4, 0));
  puzzleBW3.AddTail(Vector2(0, 1));
  puzzleBW3.SetBlockType(Vector2(0, 0), Black);
  puzzleBW3.SetBlockType(Vector2(0, 3), Black);
  puzzleBW3.SetBlockType(Vector2(1, 0), Black);
  puzzleBW3.SetBlockType(Vector2(1, 1), Black);
  puzzleBW3.SetBlockType(Vector2(1, 2), Black);
  puzzleBW3.SetBlockType(Vector2(1, 3), Black);
  puzzleBW3.SetBlockType(Vector2(2, 0), Black);
  puzzleBW3.SetBlockType(Vector2(2, 2), Black);
  puzzleBW3.SetBlockType(Vector2(2, 3), Black);
  puzzleBW3.SetBlockType(Vector2(3, 3), Black);
  puzzleBW3.SetBlockType(Vector2(0, 2), White);
  puzzleBW3.SetBlockType(Vector2(2, 1), White);
  puzzleBW3.SetBlockType(Vector2(3, 0), White);
  puzzleBW3.SetBlockType(Vector2(3, 1), White);
  puzzleBW3.SetBlockType(Vector2(3, 2), White);
  start = HighResClock::now();
  puzzleBW3.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleBW3 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleBW3.GetPaths().size() != 2) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Black & white separation
  Puzzle puzzleBW4(4, 4);
  puzzleBW4.AddHead(Vector2(3, 0));
  puzzleBW4.AddTail(Vector2(0, 3));
  puzzleBW4.SetBlockType(Vector2(0, 0), Black);
  puzzleBW4.SetBlockType(Vector2(0, 1), Black);
  puzzleBW4.SetBlockType(Vector2(0, 2), Black);
  puzzleBW4.SetBlockType(Vector2(1, 0), Black);
  puzzleBW4.SetBlockType(Vector2(1, 2), Black);
  puzzleBW4.SetBlockType(Vector2(1, 1), White);
  puzzleBW4.SetBlockType(Vector2(2, 0), White);
  puzzleBW4.SetBlockType(Vector2(2, 1), White);
  puzzleBW4.SetBlockType(Vector2(2, 2), White);
  start = HighResClock::now();
  puzzleBW4.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleBW4 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleBW4.GetPaths().size() != 2) {
    std::cout << "solution mismatch" << std::endl;
  }

  // Black & white separation
  Puzzle puzzleBW5(5, 5);
  puzzleBW5.AddHead(Vector2(2, 2));
  puzzleBW5.AddTail(Vector2(0, 4));
  puzzleBW5.SetBlockType(Vector2(1, 1), Black);
  puzzleBW5.SetBlockType(Vector2(1, 2), Black);
  puzzleBW5.SetBlockType(Vector2(2, 1), Black);
  puzzleBW5.SetBlockType(Vector2(2, 2), Black);
  puzzleBW5.SetBlockType(Vector2(0, 0), White);
  puzzleBW5.SetBlockType(Vector2(0, 1), White);
  puzzleBW5.SetBlockType(Vector2(0, 2), White);
  puzzleBW5.SetBlockType(Vector2(0, 3), White);
  puzzleBW5.SetBlockType(Vector2(1, 3), White);
  puzzleBW5.SetBlockType(Vector2(2, 3), White);
  puzzleBW5.SetBlockType(Vector2(3, 3), White);
  start = HighResClock::now();
  puzzleBW5.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  std::cout << "puzzleBW5 solved in " << ms.count() << " ms" << std::endl;
  if (puzzleBW5.GetPaths().size() != 44) {
    std::cout << "solution mismatch" << std::endl;
  }

  return 0;
}
