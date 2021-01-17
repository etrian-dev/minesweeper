// window class header file

/*
 * window.h
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

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

// include game headers
#include "game.h"
#include "states.h"
// include SFML headers for windowing
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// window class
class Window
{
private:
    // define cell size of 25 pixels
    static constexpr float SIDE = 25.0f;
    // define cell border thickness and color
    static constexpr float BORDER = -.5f;
    sf::Color border_color = sf::Color::Blue;
    // define cell's background color when State::COVERED
    sf::Color bg_covered = sf::Color(66, 135, 245);
    // ...or State::UNCOVERED
    sf::Color bg_uncovered = sf::Color(202, 221, 227);
    // define font size as 18 points
    static constexpr int FONT_SZ = 18;

    // the window where the objects are rendered
    sf::RenderWindow main_wnd;

    // declare a RectangleShape matrix that represents the field
    sf::RectangleShape** cells;

    // Font
    sf::Font arial_bold;
    // Text object that uses font
    sf::Text txt_obj;

    // texture to be drawn on the cell when it's flagged
    sf::Texture flag_img;

    // draws to the window the current game's state
    void wnd_draw(Game& curr_game);
    // draws the victory screen
    void draw_victory(const int width, const int height);
public:
    // the window loop, where events are handled
    void wnd_loop(Game& curr_game);
    // constructors & destructors
    Window(const int rows, const int cols);
};

#endif // WINDOW_H_INCLUDED
