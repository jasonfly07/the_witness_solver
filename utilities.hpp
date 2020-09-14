#pragma once
#include "Puzzle.h"
#include "Path.h"

// Visualize puzzle & solution
void draw(const Puzzle &puzzle, const Path &path)
{
    /*****************
     * Init canvas
     *****************/
    // Construct a 2D grid of char
    // TODO: switch to one-line init for vector
    static constexpr size_t CANVAS_NUM_ROWS_PER_BLOCK = 6;
    static constexpr size_t CANVAS_NUM_COLS_PER_BLOCK = 10;
    const size_t canvas_num_rows = CANVAS_NUM_ROWS_PER_BLOCK * puzzle.BlockRows() + 1;
    const size_t canvas_num_cols = CANVAS_NUM_COLS_PER_BLOCK * puzzle.BlockCols() + 1;
    std::vector<std::vector<char>> canvas;
    for (size_t r = 0; r < canvas_num_rows; ++r)
    {
        std::vector<char> row;
        for (size_t c = 0; c < canvas_num_cols; ++c)
        {
            row.push_back(' ');
        }
        canvas.push_back(row);
    }

    // Draw the basic skeleton
    for (size_t r = 0; r < puzzle.BlockRows(); ++r)
    {
        for (size_t c = 0; c < puzzle.BlockCols(); ++c)
        {
            for (size_t i = 1; i < CANVAS_NUM_ROWS_PER_BLOCK; ++i)
            {
                canvas[r * CANVAS_NUM_ROWS_PER_BLOCK + i][c * CANVAS_NUM_COLS_PER_BLOCK] = '|';
                canvas[r * CANVAS_NUM_ROWS_PER_BLOCK + i][(c + 1) * CANVAS_NUM_COLS_PER_BLOCK] = '|';
            }
            for (size_t i = 1; i < CANVAS_NUM_COLS_PER_BLOCK; ++i)
            {
                canvas[r * CANVAS_NUM_ROWS_PER_BLOCK][c * CANVAS_NUM_COLS_PER_BLOCK + i] = '-';
                canvas[(r + 1) * CANVAS_NUM_ROWS_PER_BLOCK][c * CANVAS_NUM_COLS_PER_BLOCK + i] = '-';
            }
        }
    }

    /*****************
     * Draw path
     *****************/
    for (size_t i = 0; i < path.GetPath().size() - 1; ++i)
    {
        // For each pair of points on the path, construct a side
        const auto &curr_pt = path.GetPath()[i];
        const auto &next_pt = path.GetPath()[i + 1];
        const Side side(curr_pt, next_pt);

        // Draw the side
        const Vector2 &side_p1 = side.node1->coord;
        const Vector2 &side_p2 = side.node2->coord;
        if (side.IsHorizontal())
        {
            for (size_t i = 0; i <= CANVAS_NUM_COLS_PER_BLOCK; ++i)
            {
                canvas[side_p1.r * CANVAS_NUM_ROWS_PER_BLOCK][side_p1.c * CANVAS_NUM_COLS_PER_BLOCK + i] = 'o';
            }
        }
        else
        {
            for (size_t i = 0; i <= CANVAS_NUM_ROWS_PER_BLOCK; ++i)
            {
                canvas[side_p1.r * CANVAS_NUM_ROWS_PER_BLOCK + i][side_p1.c * CANVAS_NUM_COLS_PER_BLOCK] = 'o';
            }
        }
    }

    /*****************
     * Draw puzzle elements
     *****************/
    // Draw obstacle sides
    // (by taking out line segments)
    for (const auto &side : puzzle.GetObstacleSides())
    {
        const Vector2 &side_p1 = side.node1->coord;
        const Vector2 &side_p2 = side.node2->coord;
        if (side.IsHorizontal())
        {
            for (size_t i = 3; i < CANVAS_NUM_COLS_PER_BLOCK - 2; ++i)
            {
                canvas[side_p1.r * CANVAS_NUM_ROWS_PER_BLOCK][side_p1.c * CANVAS_NUM_COLS_PER_BLOCK + i] = ' ';
            }
        }
        else
        {
            for (size_t i = 2; i < CANVAS_NUM_ROWS_PER_BLOCK - 1; ++i)
            {
                canvas[side_p1.r * CANVAS_NUM_ROWS_PER_BLOCK + i][side_p1.c * CANVAS_NUM_COLS_PER_BLOCK] = ' ';
            }
        }
    }

    // Draw essential nodes
    for (const auto &essential_node : puzzle.GetEssentialNodes())
    {
        const Vector2 &coord = essential_node->coord;
        canvas[coord.r * CANVAS_NUM_ROWS_PER_BLOCK][coord.c * CANVAS_NUM_COLS_PER_BLOCK] = '*';
    }

    // Draw essential sides
    for (const auto &essential_side : puzzle.GetEssentialSides())
    {
        const Vector2 &coord1 = essential_side.node1->coord;
        const Vector2 &coord2 = essential_side.node2->coord;
        if (essential_side.IsHorizontal())
        {
            canvas[coord1.r * CANVAS_NUM_ROWS_PER_BLOCK][coord1.c * CANVAS_NUM_COLS_PER_BLOCK + CANVAS_NUM_COLS_PER_BLOCK / 2] = '*';
        }
        else
        {
            canvas[coord1.r * CANVAS_NUM_ROWS_PER_BLOCK + CANVAS_NUM_ROWS_PER_BLOCK / 2][coord1.c * CANVAS_NUM_COLS_PER_BLOCK] = '*';
        }
    }

    // Draw heads & tails
    for (const auto &head : puzzle.GetHeads())
    {
        const Vector2 &hCoord = head->coord;
        canvas[hCoord.r * CANVAS_NUM_ROWS_PER_BLOCK][hCoord.c * CANVAS_NUM_COLS_PER_BLOCK] = 'H';
    }
    for (const auto &head : puzzle.GetTails())
    {
        const Vector2 &hCoord = head->coord;
        canvas[hCoord.r * CANVAS_NUM_ROWS_PER_BLOCK][hCoord.c * CANVAS_NUM_COLS_PER_BLOCK] = 'T';
    }

    // Draw blocks
    // TODO: draw tetris
    for (int r = 0; r < puzzle.BlockRows(); r++)
    {
        for (int c = 0; c < puzzle.BlockCols(); c++)
        {
            const Block &currBlock = puzzle.GetBlock(r, c);
            const size_t canvas_r = r * CANVAS_NUM_ROWS_PER_BLOCK + CANVAS_NUM_ROWS_PER_BLOCK / 2;
            const size_t canvas_c = c * CANVAS_NUM_COLS_PER_BLOCK + CANVAS_NUM_COLS_PER_BLOCK / 2;
            switch (currBlock.type)
            {
            case BlockType::Empty:
                // no-op
                break;
            case BlockType::Black:
                canvas[canvas_r][canvas_c] = 'B';
                break;
            case BlockType::White:
                canvas[canvas_r][canvas_c] = 'W';
                break;
            default:
                break;
            }
        }
    }

    /*****************
     * Display
     *****************/
    for (const auto &row : canvas)
    {
        for (const char c : row)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}