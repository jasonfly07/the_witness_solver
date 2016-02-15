#pragma once
#include "stdafx.h"

#include "Path.h"
#include "Puzzle.h"

class PuzzleSolver {
public:
  PuzzleSolver() {}
  PuzzleSolver(Puzzle& puzzle) {
    m_HasBlackWhite = false;
    m_PuzzlePtr = &puzzle;
  }

  void Solve();

  PathVector& GetPaths() { return m_Paths; }

private:

  bool m_HasBlackWhite;

  PathVector m_Paths;
  Puzzle* m_PuzzlePtr;
};