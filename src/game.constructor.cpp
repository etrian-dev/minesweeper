// Game class constructor
#include "../include/game.h"

Game::Game(const int rows, const int cols, const int mines)
{
    // set class rows, cols and mines
    m_rows = rows;
    m_cols = cols;
    m_mines = mines;
    // then initialize playing fields (all zeroes)
    logic = new int* [rows];
    values = new int* [rows];
    flagged = new bool* [rows];
    int i, j;
    for(i = 0; i < rows; i++)
    {
        // this version of new inits to 0 all the cells
        logic[i] = new int [cols]();
        values[i] = new int [cols]();
        flagged[i] = new bool [cols]();
    }
    // init values
    for(i = 0; i < m_rows; i++)
    {
        for(j = 0; j < m_cols; j++)
        {
            logic[i][j] = State::COVERED;
            values[i][j] = 0;
            flagged[i][j] = Flag::UNFLAGGED;
        }
    }

    // set game as running
    keep_running = true;

    // debug info
#ifdef DEBUG
    std::cout   << "Game initialized: " << rows << "x" << cols
                << " with " << mines << " mines"
                << "\nlogic field at " << &logic
                << "\nvalues field at " << &values << std::endl;
#endif

    // mines are not placed until the user uncovers the first cell
}

Game::~Game()
{
    // free boards
    int i;
    for(i = 0; i < m_rows; i++)
    {
        delete[] logic[i];
        delete[] values[i];
        delete[] flagged[i];
    }
    delete logic;
    delete values;
    delete flagged;
}
