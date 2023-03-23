/*
** EPITECH PROJECT, 2023
** IGraphics
** File description:
** The header contains the class IGraphics.
*/

#pragma once

#include <string>

namespace Arcade
{
    class IGraphics
    {
    public:
        /**
         * @brief
         *
         * @param width X position of the tile to draw
         * @param height Y position of the tile to draw
         * @param scale
         */
        void openWindow(int width, int height);
        void closeWindow();
        /**
         * @brief Loads an image.
         *
         * @param path The path of the image to load
         * @return Always return a texture even if the loading fails, however,
         * if it fails it will be an unknown block texture black and purple.
         */
        void *loadImage(const std::string &path);
        /**
         * @brief Loads a font.
         *
         * @param path The path of the image to load
         * @return
         */
        void loadFont(const std::string &path);
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
        void drawTile(int x, int y, uint32_t color);
        /**
         * @brief Draws an image at the specified position
         * 
         * @param x X position of the tile to draw
         * @param y Y position of the tile to draw
         * @param img The image to draw 
         */
        void drawImage(int x, int y, void *img);
        /**
         * @brief Draw text
         *
         * @param text The text to draw
         * @param x
         * @param y
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         */
        void drawText(std::string &text, int x, int y, int color);
        /**
         * @brief Refresh the window with every element that have been drawn with any draw function.
         *
         */
        void display();
        /**
         * @brief Get the Mouse Button in an int table object in 
         * 
         * @param coords Int table of 2 occurences.
         * Which contains in the first occurence the position x and 
         * the second the position y.
         */
        void getMousePos(int *coords);
        /**
         * @brief Get the mouse Buttons in a bool table.
         * 
         * @param buttons Bool table of 3 occurences which
         * return the buttons pressed during the call.
         */
        void getMouseButton(bool *buttons);
        /**
         * @brief Get the Buttons in a bool table.
         * 
         * @param buttons Bool table of TOTAL_INPUT occurences which
         * return the buttons pressed during the call.
         */
        void getButtons(bool *buttons);
    };
}
