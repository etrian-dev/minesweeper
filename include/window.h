// window class header file
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

// include game headers
#include "game.h"
#include "states.h"
// include SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// window class
class Window {
    private:
        
        // declare cell size: common to all instances of Window
        static constexpr float SIDE = 25.0f;
        // define border thickness and color
        static constexpr float BORDER = -.5f;
        sf::Color border_color = sf::Color::Blue;
        // Cell's background color when State::COVERED
        sf::Color bg_covered = sf::Color(66, 135, 245);
        // or State::UNCOVERED
        sf::Color bg_uncovered = sf::Color(202, 221, 227);
        // define font size
        static constexpr int FONT_SZ = 18;
        
        // the window where the objects are rendered
        sf::RenderWindow main_wnd;
        
        // declare a RectangleShape matrix that represents the cells
        sf::RectangleShape** cells;
        
        // Font
        sf::Font arial_bold;
        
        // Text object that uses font
        sf::Text txt_obj;
        
        // texture to be drawn on the cell when it's flagged
        sf::Texture flag_img;
        
        /// Methods (private)
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
