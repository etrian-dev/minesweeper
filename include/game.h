// game class header file
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "states.h"

// other stdlib headers
#include <vector>
#include <iostream>

// window class
class Game {
    private:
        // playing fields are just matrices of integers
        int **logic;
        int **values;
        bool **flagged; // flagged cells
        // number of rows, columns and mines
        int m_rows, m_cols, m_mines;
        // flag to indicate whether the game is lost or not
        bool keep_running;

        // various methods

        // procedure to place mines, excludes cell [y][x]
        void place_mines(const int x_clude, const int y_clude);
        // procedure to calc values
        void calc_values(void);
        // recursively uncovers all adjacent zeros up to values != 0
        void uncover_zeros(const int x, const int y);
    public:
        // tries to uncover cell [y][x]
        void move(const int x, const int y);
        // tries to flag/unflag cell [y][x]
        void flag(const int x, const int y);
        
        // triggers mine placing etc... after a move has been performed
        void init_game(const int x_clude, const int y_clude);
        
        // getters and setters
        // they return a shallow copy of the value / set something
        int** get_logic(void);
        int** get_values(void);
        const int get_rows(void);
        const int get_cols(void);
        const int get_mines(void);
        const bool get_continue(void);
        
        // return true if cell [y][x] is flagged, false otherwise
        bool is_flagged(const int x, const int y);
        
        // tests victory
        bool test_victory(void);

        // constructors and destructors
        Game(const int rows, const int cols, const int mines);
        ~Game();
};

#endif // GAME_H_INCLUDED
