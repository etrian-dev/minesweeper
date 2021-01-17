// window class constructor and destructor

/*
 * window.constructors.cpp
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

 
// window header
#include "../include/window.h"
// std lib headers
#include <iostream>
// c++17 header that supplies a way to get the cwd
#include <filesystem>

Window::Window(const int rows, const int cols)
{
#ifdef DEBUG
    std::cout   << "Current working directory: "
                << std::filesystem::current_path() << "\n";
#endif

    main_wnd.create(
        // create a window of width, height pixels, based cell size
        sf::VideoMode(cols * SIDE, rows * SIDE),
        "Minesweeper", // the window's title
        sf::Style::Titlebar | sf::Style::Close // titlebar and close button
    );

    // debug info
#ifdef DEBUG
    std::cout   << "New instance of Window (" << rows << "x" << cols
                << "created at " << &main_wnd << "\n";
#endif

    // load font used by the program (Arial Bold)
    if(false == arial_bold.loadFromFile("fonts/Arial_Bold.ttf"))
    {
        if(false == arial_bold.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial_Bold.ttf"))
        {
            std::cout << "Font Arial Bold not present in the system\n";

            // destroy window...
        }
    }

    // debug info
#ifdef DEBUG
    std::cout << "Font Arial Bold loaded at "<< &arial_bold << "\n";
#endif

    // then initialize the text object with the loaded font
    txt_obj.setFont(arial_bold);
    txt_obj.setCharacterSize(FONT_SZ);
    txt_obj.setFillColor(sf::Color::Black);

    // debug info
#ifdef DEBUG
    std::cout << "Text object initialized at" << &txt_obj << "\n";
#endif

    // initialize cells
    int i, j;
    cells = new sf::RectangleShape* [rows];
    if(!cells)
    {
        std::cout << "Cannot initialize cell object\n";

        // freeing...
    }
    for(i = 0; i < rows; i++)
    {
        cells[i] = new sf::RectangleShape [cols];
        if(!cells[i])
        {
            std::cout << "Cannot initialize cell object\n";

            // freeing...
        }
    }
    // set parameters for all cells in the matrix
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            // first set the cell's position
            cells[i][j].setPosition(j * SIDE, i * SIDE);
            // and other graphical properties
            cells[i][j].setSize(sf::Vector2f(SIDE, SIDE));
            cells[i][j].setOutlineThickness(BORDER);
            cells[i][j].setOutlineColor(border_color);
        }
    }

    // debug info
#ifdef DEBUG
    std::cout << "Cell object initialized at" << &cells << "\n";
#endif

    // load flag texture from file
    if(!flag_img.loadFromFile("textures/redflag.png"))
    {
        std::cout << "Texture redflag.png cannot be loaded\n";

        // window destroy....
    }

    // debug info
#ifdef DEBUG
    std::cout << "Texture object initialized at" << &flag_img << "\n";
#endif

    // window initialized
}
