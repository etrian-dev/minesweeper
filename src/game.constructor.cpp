// defines the constructor and destructor for the Game class

/*
 * game.constructor.cpp
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

// Game class constructor
#include "../include/game.h"
// useful shared values between window logic and game logic
#include "../include/states.h"

// the code sets the state variables and the playing boards, then the running flag is set to true
Game::Game(const int rows, const int cols, const int mines)
{

    this->m_rows = rows;
    this->m_cols = cols;
    this->m_mines = mines;
    
    this->logic = new int* [rows];
    this->values = new int* [rows];
    this->flagged = new bool* [rows];
    int i, j;
    for(i = 0; i < rows; i++)
    {
        this->logic[i] = new int [cols];
        this->values[i] = new int [cols];
        this->flagged[i] = new bool [cols];
    }

    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols; j++)
        {
            this->logic[i][j] = State::COVERED;
            this->values[i][j] = 0;
            this->flagged[i][j] = Flag::UNFLAGGED;
        }
    }

    // set game as running
    this->keep_running = true;

    // debug info
#ifdef DEBUG
    std::cout   << "Game initialized: " << rows << "x" << cols
                << " with " << mines << " mines";
#endif
}

// Game class destructor, used to delete the matrices representing the playing field
Game::~Game()
{
    int i;
    // delete rows
    for(i = 0; i < m_rows; i++)
    {
        delete[] logic[i];
        delete[] values[i];
        delete[] flagged[i];
    }
    // then the array of pointers can be deleted
    delete logic;
    delete values;
    delete flagged;
}
