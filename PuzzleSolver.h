#pragma once
#include "stdafx.h"

#include "Path.h"
#include "Puzzle.h"

class PuzzleSolver
{
public:
  PuzzleSolver() {}
  PuzzleSolver(Puzzle &puzzle, int maxNumOutput = 1)
  {
    m_PuzzlePtr = &puzzle;
    m_MaxNumSolutions = maxNumOutput;
  }

  void Solve();

  PathVector &GetPaths() { return m_Paths; }

private:
  // Max number of outputs
  // If set to -1, the solver will return all the solutions
  int m_MaxNumSolutions;

  PathVector m_Paths;
  Puzzle *m_PuzzlePtr;
};

class MirrorPuzzleSolver
{
public:
  MirrorPuzzleSolver() {}
  MirrorPuzzleSolver(Puzzle &puzzle)
  {
    m_PuzzlePtr = &puzzle;
  }

  void Solve();

  // PathVector &GetPaths() { return m_Paths; }

private:
  Path m_Path1;
  Path m_Path2;
  Puzzle *m_PuzzlePtr;
};