// public functions of the game class: getters and setters

/*
 * game.public.cpp
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

// game header
#include "../include/game.h"

// place mines and calc values excluding the [y][x] cell provided (the first move)
void Game::init_game(const int x_clude, const int y_clude)
{
    // place mines first
    place_mines(x_clude, y_clude);
    calc_values();
    // make the move. Automatically uncovers zeros too
    move(x_clude, y_clude);
}

// make a move: uncover cell [y][x]
void Game::move(const int x, const int y)
{
    switch(logic[y][x])
    {
    case State::MINE:
#ifdef DEBUG
        std::cout << "Cell [" << y << "][" << x << "] is a mine: game lost\n";
#endif
        keep_running = false;
        break;
    case State::COVERED:
#ifdef DEBUG
        std::cout << "Cell [" << y << "][" << x << "] has been uncovered\n";
#endif
        logic[y][x] = State::UNCOVERED;
        flagged[y][x] = Flag::UNFLAGGED;
        // if the cell's value is 0 the recursive uncover function is called
        if(values[y][x] == 0)
        {
            uncover_zeros(x, y);
        }
        break;
        
    default: // nothing happens if a cell is already uncovered
#ifdef DEBUG
        std::cout << "Cell [" << y << "][" << x << "] already uncovered\n";
#endif
    }

// if the debug flag is asserted, then all the fiels are printed at each move
#ifdef DEBUG
    int i, j;
    std::cout << "LOGIC\n";
    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols-1; j++)
        {
            if(logic[i][j] == State::MINE)
            {
                std::cout << "M ";
            }
            else if(logic[i][j] == State::COVERED)
            {
                std::cout << "C ";
            }
            else
            {
                std::cout << "U ";
            }
        }
        if(logic[i][j] == State::MINE)
        {
            std::cout << "M\n";
        }
        else if(logic[i][j] == State::COVERED)
        {
            std::cout << "C\n";
        }
        else
        {
            std::cout << "U\n";
        }
    }
#endif
}

// if cell [y][x] is not flagged, flag it, otherwise unflag it
void Game::flag(const int x, const int y)
{
    if(flagged[y][x] == Flag::FLAGGED)
    {
        flagged[y][x] = Flag::UNFLAGGED;
    }
    else
    {
        flagged[y][x] = Flag::FLAGGED;
    }

// if the debug flag is asserted, then all the flagged matrix is printed
#ifdef DEBUG
    int i, j;
    std::cout << "FLAGS\n";
    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols-1; j++)
        {
            if(flagged[i][j] == Flag::FLAGGED)
            {
                std::cout << "F ";
            }
            else
            {
                std::cout << "N ";
            }
        }
        if(flagged[i][j] == Flag::FLAGGED)
        {
            std::cout << "F\n";
        }
        else
        {
            std::cout << "N\n";
        }
    }
#endif
}

// return true if cell [y][x] is flagged, false otherwise
bool Game::is_flagged(const int x, const int y)
{
    if(flagged[y][x] == Flag::UNFLAGGED)
    {
        return false;
    }
    return true;
}

// just getters
int** Game::get_logic(void)
{
    return logic;
}
int** Game::get_values(void)
{
    return values;
}
const int Game::get_rows(void)
{
    return m_rows;
}
const int Game::get_cols(void)
{
    return m_cols;
}
const int Game::get_mines(void)
{
    return m_mines;
}
const bool Game::get_continue(void)
{
    return keep_running;
}

// tests victory
bool Game::test_victory(void)
{
    bool no_win = false;
    int i, j;
    for(i = 0; !no_win && i < m_rows; i++)
    {
        for(j = 0; !no_win && j < m_cols; j++)
        {
            if(logic[i][j] == State::COVERED)
            {
                no_win = true;
            }
        }
    }
    if(!no_win)
    {
        std::cout << "Victory!\n";
        return true;
    }
    return false;
}
