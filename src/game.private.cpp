// private Game class methods

/*
 * game.private.cpp
 * This file is part of minesweeper
 *
 * Copyright (C) 2021 - etrian-dev
 *
 * minesweeper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * minesweeper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with minesweeper. If not, see <http://www.gnu.org/licenses/>.
 */

// game class header
#include "../include/game.h"

#include <random> // for the mines'randgen
#include <ctime>
#include <cstdlib>
#include <algorithm> // for std::find

// given the number of mines of this instance, place them
// randomly on the field, except on the first uncovered cell
void Game::place_mines(const int x_clude, const int y_clude)
{
    std::random_device rd;
    // random numbers in the range [0, 2^32-1] seeded with hardware randomness (hopefully)
    std::mt19937 rnd_gen(rd());
    
    int x, y;
    int n_mines = m_mines;
    while(n_mines > 0)
    {
        // modulo to obtain a valid index
        x = rnd_gen() % m_cols;
        y = rnd_gen() % m_rows;
        if(!(x == x_clude && y == y_clude) && logic[y][x] != State::MINE)
        {
            logic[y][x] = State::MINE;
            n_mines--;

            // debug info
#ifdef DEBUG
            std::cout   << "Mine placed at " << &logic[y][x]
                        << " [" << y << "][" << x << "] ("
                        << n_mines << " left)\n";
#endif
        }
        else
        {
            // debug info
#ifdef DEBUG
            std::cout   << "Mine cannot be placed at " << &logic[y][x]
                        << " [" << y << "][" << x << "] ("
                        << n_mines << " left)\n";
#endif
        }
    }

    // debug info
#ifdef DEBUG
    int i, j;
    std::cout << "LOGIC\n";
    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols-1; j++)
        {
            if(logic[i][j] != State::MINE && !(i == y_clude && j == x_clude))
            {
                std::cout << "C ";
            }
            else if(i == y_clude && j == x_clude)
            {
                std::cout << "U ";
            }
            else
            {
                std::cout << "M ";
            }
        }
        if(logic[i][j] != State::MINE && !(i == y_clude && j == x_clude))
        {
            std::cout << "C\n";
        }
        else if(i == y_clude && j == x_clude)
        {
            std::cout << "U\n";
        }
        else
        {
            std::cout << "M\n";
        }
    }
#endif

    // all mines placed
}

// calculate the value of each cell based on the mines' positions
void Game::calc_values(void)
{
    // for each cell, count the number of surrounding cells with a mine
    // complexity is rows * cols * 8 * theta(1) = theta(rows * cols) => optimal
    int i, j, m, n;
    for(i = 0;  i < m_rows; i++)
    {
        for(j = 0; j < m_cols; j++)
        {
            // if cell [i][j] does not contain a mine, check surrounding cells
            if(logic[i][j] != State::MINE)
            {
                for(m = i-1; m < i+2; m++)
                {
                    for(n = j-1; n < j+2; n++)
                    {
                        // verify that [m][n] is a valid cell and not [i][j]
                        // and that it does not contain a mine (short circuit and)
                        if(
                            m >= 0 && m < m_rows
                            && n >= 0 && n < m_cols
                            && !(m == i && n == j)
                            && logic[m][n] == State::MINE
                        )
                        {
                            values[i][j]++;
                        }
                    }
                }
            }
            else
            {
                // assing '*' = 42: a value that cannot appear otherwise
                values[i][j] = '*';
            }

            //debug info
#ifdef DEBUG
            std::cout << "Final value of [" << i << "][" << j << "] = " << values[i][j] << "\n";
#endif
        }
    }
    // all values calculated

    // debug info
#ifdef DEBUG
    std::cout << "VALUES\n";
    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols-1; j++)
        {
            if(logic[i][j] != State::MINE)
            {
                std::cout << values[i][j] << " ";
            }
            else
            {
                std::cout << "M ";
            }
        }
        if(logic[i][j] != State::MINE)
        {
            std::cout << values[i][j] << "\n";
        }
        else
        {
            std::cout << "M\n";
        }
    }
#endif
}

// recursively uncover cells
void Game::uncover_zeros(const int x, const int y)
{
    // this function is executed only whitin move() when uncovering a cell
    // thus no particular caution is needed in recurring
    int i, j;
    for(i = y - 1; i < y + 2; i++)
    {
        for(j = x - 1; j < x + 2; j++)
        {
            // if [j][i] is a valid cell and it's covered
            if( i >= 0 && i < m_rows
                    && j >= 0 && j < m_cols
                    && logic[i][j] == State::COVERED
              )
            {
                // debug info
#ifdef DEBUG
                std::cout   << "Cell [" << y << "][" << x << "] = "<< values[y][x]
                            << " uncovered\n";
#endif

                // uncover it and unflag if necessary
                logic[i][j] = State::UNCOVERED;
                flagged[i][j] = Flag::UNFLAGGED;
                // if the value is 0, then recurse on nearby cells [j][i]
                if(values[i][j] == 0)
                {
                    uncover_zeros(j, i);
                }
            }
        }
    }
    // debug info
#ifdef DEBUG
    std::cout << "All zeros have been uncovered\n";
#endif

    // all available zeros have been uncovered
}
