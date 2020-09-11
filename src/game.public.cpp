// public functions of the game class: getters and setters
#include "../include/game.h"

// triggers mine placing etc... after a move has been performed
void Game::init_game(const int x_clude, const int y_clude)
{
    // place mines first
    place_mines(x_clude, y_clude);
    // then calculate values
    calc_values();
    // make the move; automatically uncovers zeros too
    move(x_clude, y_clude);
}

// make a move: uncover cell
void Game::move(const int x, const int y)
{
    // assumes that cell [y][x] is a valid cell
    // and decides how the game state changes
    switch(logic[y][x])
    {
    case State::MINE:
        // the user tried to uncover a mine
        keep_running = false;
#ifdef DEBUG
        std::cout   << "Cell [" << y << "][" << x
                    << "] is a mine: game lost\n";
#endif
        break;
    case State::COVERED:
        // the cell is uncovered
        logic[y][x] = State::UNCOVERED;
        // the cell is removed (if necessary) from the flagged vector
        flagged[y][x] = Flag::UNFLAGGED;
        // then if its value is 0 the recursive uncover function is called
        if(values[y][x] == 0)
        {
            uncover_zeros(x, y);
        }
#ifdef DEBUG
        std::cout   << "Cell [" << y << "][" << x
                    << "] has been uncovered\n";
#endif
        break;
        // nothing is done if a cell is already uncovered
#ifdef DEBUG
    case State::UNCOVERED:
        std::cout   << "Cell [" << y << "][" << x
                    << "] already uncovered\n";
#endif
    }

    // debug info
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

    // debug info
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
// return true if cell [y][x] is flagged, false otherwise
bool Game::is_flagged(const int x, const int y)
{
    if(flagged[y][x] == Flag::UNFLAGGED)
    {
        return false;
    }
    return true;
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
