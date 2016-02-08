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
  assert(puzzleSimpleMaze1.GetPaths().size() == 14);
  std::cout << "puzzleSimpleMaze1 solved in " << ms.count() << " ms" << std::endl;
  // TODO: check if there're duplicated paths

  // Maze with essential nodes
  Puzzle puzzleMazeEssential1(4, 4);
  puzzleMazeEssential1.AddHead(Vector2(1, 1));
  puzzleMazeEssential1.AddHead(Vector2(2, 2));
  puzzleMazeEssential1.AddTail(Vector2(1, 0));
  puzzleMazeEssential1.AddNodeObstacle(Vector2(0, 0), Vector2(0, 1));
  puzzleMazeEssential1.AddNodeObstacle(Vector2(0, 0), Vector2(1, 0));
  puzzleMazeEssential1.AddNodeObstacle(Vector2(1, 2), Vector2(1, 3));
  puzzleMazeEssential1.AddNodeObstacle(Vector2(2, 2), Vector2(3, 2));
  puzzleMazeEssential1.AddEssentialNode(Vector2(2, 0));
  puzzleMazeEssential1.AddEssentialNode(Vector2(2, 1));
  puzzleMazeEssential1.AddEssentialNode(Vector2(0, 1));
  puzzleMazeEssential1.AddEssentialNode(Vector2(1, 2));
  puzzleMazeEssential1.AddEssentialNode(Vector2(1, 3));
  puzzleMazeEssential1.AddEssentialNode(Vector2(3, 3));
  start = HighResClock::now();
  puzzleMazeEssential1.Solve();
  end = HighResClock::now();
  ms = std::chrono::duration_cast<MilliSecond>(end - start);
  assert(puzzleMazeEssential1.GetPaths().size() == 1);
  std::cout << "puzzleMazeEssential1 solved in " << ms.count() << " ms" << std::endl;


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
  assert(puzzleBW1.GetPaths().size() == 1);
  std::cout << "puzzleBW1 solved in " << ms.count() << " ms" << std::endl;

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
  assert(puzzleBW2.GetPaths().size() == 1);
  std::cout << "puzzleBW2 solved in " << ms.count() << " ms" << std::endl;

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
  std::cout << puzzleBW3.GetPaths().size() << std::endl;
  std::cout << "puzzleBW3 solved in " << ms.count() << " ms" << std::endl;

  return 0;
}
