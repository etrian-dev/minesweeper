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

 
// window header file
#include "../include/window.h"

// std lib headers
#include <iostream>

// costructor of the game window
Window::Window(const int rows, const int cols)
{
	// creates the window with a given width, height and its title
	this->main_wnd.create(
		sf::VideoMode(cols * SIDE, rows * SIDE), 
		"Minesweeper", 
		sf::Style::Titlebar | sf::Style::Close); // window with titlebar and close button
// prints debug info on the window just created
#ifdef DEBUG
    std::cout << "new Window [" << rows << "x" << cols << "] with cell size " << SIDE << "\n";
#endif

	std::string p_res = Window::get_respath();

    // load font used by the program (Arial Bold)
    if(!arial_bold.loadFromFile(p_res + "Arial_Bold.ttf"))
    {
        if(!arial_bold.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial_Bold.ttf"))
        {
            std::cout << "Cannot find the path Arial Bold in the system: check if it's installed\n";
        }
    }
    // load flag texture from file
    if(!flag_img.loadFromFile(p_res + "redflag.png"))
    {
        std::cout << "Texture redflag.png cannot be loaded\n";
    }

    // then initialize the text object with the loaded font
    txt_obj.setFont(arial_bold);
    txt_obj.setCharacterSize(FONT_SZ);
    txt_obj.setFillColor(sf::Color::Black);

    // initialize cells
    int i, j;
    cells = new sf::RectangleShape* [rows];
    if(!cells)
    {
        std::cout << "Cannot initialize cell object\n";

    }
    for(i = 0; i < rows; i++)
    {
        cells[i] = new sf::RectangleShape [cols];
        if(!cells[i])
        {
            std::cout << "Cannot initialize cell object\n";
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
}
