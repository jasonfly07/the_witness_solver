#pragma once

#include "Path.h"
#include "Puzzle.h"

class PuzzleSolver {
public:
  PuzzleSolver() {}
  PuzzleSolver(Puzzle& puzzle) {
    m_PuzzlePtr = &puzzle;
  }

  void Solve();

private:
  PathVector m_Paths;
  Puzzle* m_PuzzlePtr;
};