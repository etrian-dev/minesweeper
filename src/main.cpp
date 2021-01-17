// Minesweeper clone, GUI powered by SFML

/*
 * main.cpp
 * This file is part of minesweeeper
 *
 * Copyright (C) 2021 - etrian-dev
 *
 * minesweeeper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * minesweeeper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with minesweeeper. If not, see <http://www.gnu.org/licenses/>.
 */


// including my headers first
#include "../include/game.h"
#include "../include/window.h"

// other headers
#include <iostream>

// defines
#define MAXCOLS 50
#define MAXROWS 25
// => mines in the range [1, cols*rows -1]

// function to choose the difficulty and setting custom parameters
int choose_diff(void);
void custom_settings(int *r, int *c, int *m);

// main function
int main(void)
{
    // first choose the difficulty
    int diff = choose_diff();
    // and game parameters are set accordingly
    int rows, cols, mines;
    switch(diff)
    {
    case 1:
        // easy
        rows = 9;
        cols = 9;
        mines = 10;
        break;
    case 2:
        // normal
        rows = 16;
        cols = 16;
        mines = 40;
        break;
    case 3:
        // hard
        rows = 16;
        cols = 30;
        mines = 99;
        break;
    default:
        // custom: the call to the function sets their values
        custom_settings(&rows, &cols, &mines);
        break;
    }

    // then initialize the Game and Window classes
    Game new_game(rows, cols, mines);
    Window new_wnd(rows, cols);
    // launch the main window loop with the game as a parameter
    new_wnd.wnd_loop(new_game);

    // game ended, destroy class instances
    return 0;
}

// choose the game's difficulty
/*
 * easy:        9 x 9 and 10 mines -> P(mine) = 0.123
 * normal:      16 x 16 and 40 mines -> P(mine) = 0.156
 * hard:        16 x 30 and 99 mines -> P(mine) = 0.206
 * custom:      choose your own
 */
int choose_diff(void)
{
    int diff;
    do
    {
        std::cout <<"Welcome to Minesweeper. Choose the difficulty\n"
                  <<"1) easy : 9 x 9 grid, 10 mines\n"
                  <<"2) normal: 16 x 16 grid, 40 mines\n"
                  <<"3) hard: 16 x 30 grid, 99 mines\n"
                  <<"4) custom: personalized settings\n";
        std::cin >> diff;
    }
    while(diff < 1 || diff > 4); // if diff is not in [1, 4] then loop
    return diff;
}
// custom parameters for rows/cols/mines within the boundaries defined at the top of the file
void custom_settings(int *r, int *c, int *m)
{
    // choose num rows
    std::cout << "Custom settings:\nrows [1, " << MAXROWS << "]\n";
    do
    {
        std::cin >> *r;
    }
    while(*r < 1 || *r > MAXROWS);
    // choose num cols
    std::cout << "cols [1, " << MAXCOLS << "]\n";
    do
    {
        std::cin >> *c;
    }
    while(*c < 1 || *c > MAXCOLS);
    // choose num mines
    std::cout << "mines [1, " << (*r) * (*c) - 1 << "]\n";
    do
    {
        std::cin >> *m;
    }
    while(*m < 1 || *m > (*r) * (*c) - 1);
    /// TODO: print ratio? Maybe y/n prompt?
}
