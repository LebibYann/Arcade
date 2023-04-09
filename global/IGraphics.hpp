/**
** EPITECH PROJECT, 2023
** IGraphics
** File description:
** The header contains the class IGraphics.
** \file IGraphics.hpp
*/

#pragma once

#include <string>
#include <vector>

namespace Arcade
{
    /**
     ** @brief Refers all the buttons
     **
     */
    typedef enum e_arcade_input
    {
        UP_ARROW, // Move (usually: Z)
        DOWN_ARROW, // Move down (usually: S)
        LEFT_ARROW, // Move left (usually: Q)
        RIGHT_ARROW, // Move right (usually: D)
        BUTTON1, // (usually: I)
        BUTTON2, // (usually: J)
        BUTTON3, // (usually: K)
        BUTTON4, // (usually: L)
        PREV_GAME, // Previous game (usually: LEFT_ARROW)
        NEXT_GAME, // Next game (usually: RIGHT_ARROW)
        PREV_LIB, // Previous graphical library (usually: DOWN_ARROW)
        NEXT_LIB, // Next graphical library (usually: UP_ARROW)
        RESTART, // Restart the current loaded game (usually: R)
        HOME_MENU, // Restart the current loaded game (usually: RETURN)
        EXIT, // Quit the program (usually: ESCAPE)
        TOTAL_INPUT // Not a key just a way to know the size of the std::vector<bool> of getButton method.
    } t_arcade_input;

    /**
     ** @brief These are all the supported color by the arcade.
     ** Any color that goes outside the range of this enum
     ** must be ignoried or handled (it's up to you)
     ** but must not make the program crash or throw an error.
     **
     */
    enum ArcadeColor
    {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    /**
     ** @brief This class refer all the method that you should code
     ** in order to add a new graphic library to the arcade software,
     ** you must inherit of it if possible.
     ** Do not forget to implement the two extern "C" function
     ** which are entry_point and get_type.
     */
    class IGraphics
    {
    public:
        /**
         * @brief Loads an image.
         *
         * @param path The path of the image to load
         * @return Return an object that contains an image
         * depending on the graphic library,
         * it can also return a nullptr if the loading failed or
         * the library doesn't support image loading.
         */
        virtual void *loadImage(const std::string &path) = 0;
        /**
         * @brief Loads a font.
         *
         * @param path The path of the image to load
         */
        virtual void loadFont(const std::string &path) = 0;
        /**
         * @brief Fill the windows with a single color.
         *
         * @param color A color based on the enum ArcadeColor.
         */
        virtual void fill(uint32_t color) = 0;
        /**
         * @brief Draws a tile a the specified position with the specified color.
         *
         * @param x X position of the tile to draw.
         * @param y Y position of the tile to draw.
         * @param color A color based on the enum ArcadeColor.
         */

        virtual void drawTile(int x, int y, uint32_t color) = 0;
        /**
         * @brief Draws an image at the specified position.
         *
         * @param x X position of the tile to draw.
         * @param y Y position of the tile to draw.
         * @param img The object that contains an image to draw
         */
        virtual void drawImage(int x, int y, void *img) = 0;
        /**
         * @brief Draw text  at the specified position
         *
         * @param text The text to draw
         * @param x X position of the tile to draw.
         * @param y Y position of the tile to draw.
         * @param color A color based on the enum ArcadeColor.
         */
        virtual void drawText(const std::string &text, int x, int y, int color) = 0;
        /**
         * @brief Refresh the window and display with every element
         * that have been drawn with any draw function
         * before the call of this function.
         *
         */
        virtual void display(void) = 0;
        /**
         * @brief Get the Mouse Button in an int table.
         *
         * @return An int table of 2 occurences,
         * where the first occurence is the x position and
         * the second the y position.
         */
        virtual void getMousePos(std::vector<int> &coords) = 0;
        /**
         * @brief Get the mouse Buttons in a bool table.
         *
         * @return An bool table of 3 occurences,
         * where the first occurence is the left click,
         * the second the middle click and the third is the right click.
         */
        virtual void getMouseButton(std::vector<bool> &coord) = 0;
        /**
         * @brief Get the Buttons in a bool table.
         * All the button must be mapped,
         * it's up to you to choose which button triggers what.
         * You can look a the buttons on the t_arcade_input enum.
         *
         * @return An bool table of TOTAL_INPUT occurences which
         * return the buttons pressed during the call.
         */
        virtual void getButtons(std::vector<bool> &input) = 0;
        /**
         ** @brief Get the Keyboard pressed keys and
         ** return the corresponding characters one by one.
         **
         ** @return char the corresponding character or,
         ** 0 if no keys are pressed or the key is ignored.
         */
        virtual char getKeyboard(void) = 0;
    };
};
