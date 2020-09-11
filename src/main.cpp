// Minesweeper powered by SFML, version 2

// including my headers first
#include "../include/game.h"
#include "../include/window.h"

// other headers
#include <iostream>

// defines
#define MAXCOLS 50
#define MAXROWS 25
// -> mines in the range [1, cols*rows -1]

// functions prototypes
int choose_diff(void);
void custom_settings(int *r, int *c, int *m);

// main function
int main(void)
{
    // first choose the difficulty
    int diff = choose_diff();
    // based on the difficulty level chosen set variables
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
        // custom
        rows = -1;
        cols = -1;
        mines = -1;
        break;
    }
    // if the custom diff is chosen, then call a function to set values
    if(rows == -1 || cols == -1 || mines == -1)
    {
        custom_settings(&rows, &cols, &mines);
    }
    // then init the classes
    Game new_game(rows, cols, mines);
    Window new_wnd(rows, cols);
    // launch the game loop
    new_wnd.wnd_loop(new_game);
    // game ended, destroy class instances
    return 0;
}

// choose the game's difficulty
/**
 * easy:        9 x 9 and 10 mines ->       0.123
 * normal:      16 x 16 and 40 mines ->     0.156
 * hard:        16 x 30 and 99 mines ->     0.206
 * custom:      choose your own
 */
int choose_diff(void)
{
    int diff;
    do
    {
        std::cout<<"Welcome to Minesweeper. Choose the difficulty"
                 <<"\n\t1) easy : 9 x 9 grid, 10 mines"
                 <<"\n\t2) normal: 16 x 16 grid, 40 mines"
                 <<"\n\t3) hard: 16 x 30 grid, 99 mines"
                 <<"\n\t4) custom: personalized settings\n";
        std::cin >> diff;
    }
    while(diff < 1 || diff > 4);
    return diff;
}
// choose custom number of rows/cols/mines within some boundaries
void custom_settings(int *r, int *c, int *m)
{
    // choose num rows
    std::cout << "Custom settings:\n\trows [1, " << MAXROWS << "]\n";
    do
    {
        std::cin >> *r;
    }
    while(*r < 1 || *r > MAXROWS);
    // choose num cols
    std::cout << "\tcols [1, " << MAXCOLS << "]\n";
    do
    {
        std::cin >> *c;
    }
    while(*c < 1 || *c > MAXCOLS);
    // choose num mines
    std::cout << "\nmines [1, " << (*r) * (*c) - 1 << "]\n";
    do
    {
        std::cin >> *m;
    }
    while(*m < 1 || *m > (*r) * (*c) - 1);
    // TODO: print ratio? Maybe confirmation loop?
}
