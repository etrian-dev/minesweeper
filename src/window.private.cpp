// Window class private methods

/*
 * window.private.cpp
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

// window class header
#include "../include/window.h"
// others
#include <string>

void Window::wnd_draw(Game& curr_game)
{
    // gets copies of the game state
    int rows = curr_game.get_rows();
    int cols = curr_game.get_cols();
    int** logic = curr_game.get_logic();
    int** values = curr_game.get_values();

    // clear the whole window to covered bg
    main_wnd.clear(bg_covered);

    // object to store text bounds, used in centering text in cell
    sf::FloatRect bounds;

    int i, j;
    // for loops to draw all the cells in the field
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(curr_game.is_flagged(j, i))
            {
                // set this rect object's texture to the flag
                cells[i][j].setTexture(&flag_img, false);
            }
            // else remove texture
            else
            {
                cells[i][j].setTexture(nullptr, false);
            }

            // if the cell is not uncovered, fill it with covered color
            if(logic[i][j] != State::UNCOVERED)
            {
                cells[i][j].setFillColor(bg_covered);
                main_wnd.draw(cells[i][j]); // draw the cell
            }
            // otherwise set the uncovered background
            else
            {
                // set the uncovered bg color and remove the texture if there was any
                cells[i][j].setFillColor(bg_uncovered);
                cells[i][j].setTexture(nullptr, false);
                // draws the cell first
                main_wnd.draw(cells[i][j]);

                // then draw its value on top, with the text object
                txt_obj.setString(std::to_string(values[i][j]));
                // text drawing "black box" that centers it to the cell
                bounds = txt_obj.getLocalBounds();
                // the origin of the text obj is changed to the center of the bounding box
                txt_obj.setOrigin   (bounds.left + bounds.width/2.0f,
                                    bounds.top + bounds.height/2.0f);
                // then the text position is set
                txt_obj.setPosition (j * SIDE + SIDE/2.0f,
                                    i * SIDE + SIDE/2.0f);

                main_wnd.draw(txt_obj); // draw text (value)
            }
        }
    }

    // and finally update the window
    main_wnd.display();
}
