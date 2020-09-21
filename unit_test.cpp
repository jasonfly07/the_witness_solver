#include "stdafx.h"

#include "Puzzle.h"
#include "PuzzleSolver.h"
#include "Tetris.h"
#include "utilities.hpp"

typedef std::chrono::high_resolution_clock HighResClock;
typedef std::chrono::milliseconds MilliSecond;

// Utility for run solver and profiling
static void evaluate_puzzle(Puzzle &p, const Vector2List &gt_path)
{
    // Solve the puzzle & profile its running time
    std::chrono::time_point<HighResClock> start, end;
    start = HighResClock::now();
    PuzzleSolver ps(p, 1);
    ps.Solve();
    end = HighResClock::now();
    auto ms = std::chrono::duration_cast<MilliSecond>(end - start);
    std::cout << p.GetName() << " solved in " << ms.count() << " ms" << std::endl;

    // Compare solution with ground truth
    const auto &solution_path = ps.GetPaths()[0].GetPath();
    if (solution_path.size() != gt_path.size())
    {
        std::cout << "Solution/gt mismatch: solution_path size = " << solution_path.size()
                  << ", gt_path size = " << gt_path.size();
        assert(false);
    }
    for (size_t i = 0; i < solution_path.size() - 1; ++i)
    {
        const Vector2 &sol_pt = solution_path[i]->coord;
        const Vector2 &gt_pt = gt_path[i];
        if (sol_pt != gt_pt)
        {
            std::cout << "Solution/gt mismatch: sol_pt " << i << " = " << sol_pt
                      << ", gt_pt = " << gt_pt;
            assert(false);
        }
    }

    // Draw the first solution
    constexpr bool DRAW_SOLUTION = false;
    if (DRAW_SOLUTION)
    {
        std::cout << std::endl;
        draw(p, ps.GetPaths()[0]);
        std::cout << std::endl;
    }
}

// Simple maze
void puzzle_simple()
{
    Puzzle p(5, 4);
    p.SetName("puzzle_simple");
    p.AddHead({4, 0});
    p.AddTail({0, 3});
    p.AddObstacleSide({3, 0}, {4, 0});
    p.AddObstacleSide({3, 1}, {4, 1});
    p.AddObstacleSide({1, 1}, {2, 1});
    p.AddObstacleSide({1, 2}, {2, 2});
    p.AddObstacleSide({1, 3}, {2, 3});
    p.AddObstacleSide({0, 2}, {1, 2});
    p.AddObstacleSide({0, 2}, {0, 3});
    p.AddObstacleSide({0, 0}, {0, 1});
    p.Regenerate();

    const Vector2List gt_path = {
        {4, 0},
        {4, 1},
        {4, 2},
        {4, 3},
        {3, 3},
        {2, 3},
        {2, 2},
        {3, 2},
        {3, 1},
        {2, 1},
        {2, 0},
        {1, 0},
        {1, 1},
        {1, 2},
        {1, 3},
        {0, 3}};

    evaluate_puzzle(p, gt_path);
}

void puzzle_essential_1()
{
    Puzzle p(4, 4);
    p.SetName("puzzle_essential_1");
    p.AddHead({1, 1});
    p.AddHead({2, 2});
    p.AddTail({1, 0});
    p.AddEssentialNode({0, 1});
    p.AddEssentialNode({2, 0});
    p.AddEssentialNode({2, 1});
    p.AddEssentialNode({1, 2});
    p.AddEssentialNode({1, 3});
    p.AddEssentialNode({3, 3});
    p.AddObstacleSide({0, 0}, {0, 1});
    p.AddObstacleSide({0, 0}, {1, 0});
    p.AddObstacleSide({2, 2}, {3, 2});
    p.AddObstacleSide({1, 2}, {1, 3});
    p.Regenerate();

    const Vector2List gt_path = {
        {2, 2},
        {1, 2},
        {1, 1},
        {0, 1},
        {0, 2},
        {0, 3},
        {1, 3},
        {2, 3},
        {3, 3},
        {3, 2},
        {3, 1},
        {2, 1},
        {2, 0},
        {1, 0}};

    evaluate_puzzle(p, gt_path);
}

void puzzle_bw_1()
{
    Puzzle p(3, 3);
    p.SetName("puzzle_bw_1");
    p.AddHead({2, 0});
    p.AddTail({0, 2});
    p.AddSpecialBlock({0, 0}, Black);
    p.AddSpecialBlock({0, 1}, Black);
    p.AddSpecialBlock({1, 0}, Black);
    p.AddSpecialBlock({1, 1}, White);
    p.Regenerate();

    const Vector2List gt_path = {
        {2, 0},
        {2, 1},
        {1, 1},
        {1, 2},
        {0, 2}};

    evaluate_puzzle(p, gt_path);
}

int main()
{
    puzzle_simple();
    puzzle_essential_1();
    puzzle_bw_1();
    return 0;
}
