/*
** EPITECH PROJECT, 2023
** IGraphics
** File description:
** The header contains the class IGraphics.
*/

#pragma once

#include <string>
#include <vector>

#define TILES_X 64
#define TILES_Y 36

namespace Arcade
{
    typedef enum e_arcade_input
    {
        UP_ARROW,
        DOWN_ARROW,
        LEFT_ARROW,
        RIGHT_ARROW,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        PREV_GAME,
        NEXT_GAME,
        PREV_LIB,
        NEXT_LIB,
        RESTART,
        HOME_MENU,
        EXIT,
        TOTAL_INPUT
    } t_arcade_input;

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

    class IGraphics
    {
    public:
        /**
         * @brief Loads an image.
         *
         * @param path The path of the image to load
         * @return Always return a texture even if the loading fails, however,
         * if it fails it will be an unknown block texture black and purple.
         */
        virtual void *loadImage(const std::string &path) = 0;
        /**
         * @brief Loads a font.
         *
         * @param path The path of the image to load
         * @return
         */
        virtual void loadFont(const std::string &path) = 0;
        /**
         * @brief Fill the windows with a single color.
         *
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         */
        virtual void fill(uint32_t color) = 0;
        /**
         * @brief Draws a tile a the specified position with the specified color.
         * A tile is based on the size of one character in ASCII rendered library.
         * Using non-integer numbers is only useful for library
         * that doesn't use ASCII character to render images.
         *
         * @param x X position of the tile to draw
         * @param y Y position of the tile to draw
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         */

        virtual void drawTile(int x, int y, uint32_t color) = 0;
        /**
         * @brief Draws an image at the specified position
         *
         * @param x X position of the tile to draw
         * @param y Y position of the tile to draw
         * @param img The image to draw
         */
        virtual void drawImage(int x, int y, void *img) = 0;
        /**
         * @brief Draw text
         *
         * @param text The text to draw
         * @param x
         * @param y
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         */
        virtual void drawText(const std::string &text, int x, int y, int color) = 0;
        /**
         * @brief Refresh the window with every element that have been drawn with any draw function.
         *
         */
        virtual void display() = 0;
        /**
         * @brief Get the Mouse Button in an int table object in
         *
         * @return coords Int table of 2 occurences.
         * Which contains in the first occurence the position x and
         * the second the position y.
         */
        virtual void getMousePos(std::vector<int> &coords) = 0;
        /**
         * @brief Get the mouse Buttons in a bool table.
         *
         * @return buttons Bool table of 3 occurences which
         * return the buttons pressed during the call.
         */
        virtual void getMouseButton(std::vector<bool> &coord) = 0;
        /**
         * @brief Get the Buttons in a bool table.
         *
         * @return buttons Bool table of TOTAL_INPUT occurences which
         * return the buttons pressed during the call.
         */
        virtual void getButtons(std::vector<bool> &input) = 0;
        virtual char  getKeyboard(void) = 0;
    };
};
