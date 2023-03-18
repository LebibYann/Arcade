/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** The header contains all the methods of the Arcade program
*/

#pragma once

#include <memory>
#include <string>

typedef struct s_button {
    double xAxis;
    double yAxis;
    bool b1;
    bool b2;
    bool b3;
    bool b4;
} t_button;

class IShape {
    public:
        void draw(void);
        IShape *getShape(void);
        void setColor(int r, int g, int b);
        void setPosition(double x, double y);
        void setRotation(double rad);
        void setScale(double scale);
        void setSize(double w, double h);
};

class IGame {
    public:
        /**
         * @brief Call the main equivalent function to start the game
         * 
         * @param graphics 
         * @return std::size_t 
         */
        std::size_t run(IGraphics graphics);      
};

class IGraphics {
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
         * @brief Fill the windows with a single color.
         * 
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         */
        void fill(uint32_t color);
        /**
         * @brief Convert the given color in parameters into a single unsigned int.
         * 
         * @param red Between 0 and 255 where 0 is colorless and 255 colorful.
         * @param green Between 0 and 255 where 0 is colorless and 255 colorful.
         * @param blue Between 0 and 255 where 0 is colorless and 255 colorful.
         * @param opacity Between 0 and 255 where 0 is transparent and 255 opaque.
         */
        uint32_t setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t opacity);
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
         * @brief Draw a line where the start point is made with the x1-y1 parameters
         * and the end point at the x2-y2 position.
         * 
         * @param x1 Start x
         * @param y1 Start y
         * @param x2 End x
         * @param y2 End y
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color. 
         */
        void drawTileLine(int x1, int y1, int x2, int y2, int color);
        /**
         * @brief Draw a rectangle where x and y parameters 
         * define the top left corner of the rectangle.
         * 
         * @param x Top left corner x
         * @param y Top left corner y
         * @param width 
         * @param height 
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color.
         * @param fill Let you choose if you want ot fill or not the rectangle.
         */
        void drawTileRect(int x, int y, int width, int height, int color, bool fill = true);
        /**
         * @brief Draw a circle where x and y parameters 
         * define the center of the circle.
         * 
         * @param x 
         * @param y 
         * @param rad The radius of the circle.
         * @param color An unsigned int where each byte is in the following order -> rgba
         * You can use the setColor method to get a well formed unsigned int color. 
         */
        void drawTileCircle(int x, int y, int rad, int color);
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
         * @brief Get the Mouse Button object in int pointer of 2 occurences.a
         * Where the first occurence contains x position and
         * the second the y position.
         * 
         * @return true 
         * @return false 
         */
        int *getMousePos(int *coords);
        /**
         * @brief Get the Buttons object in bool pointer of 3 occurences.
         * The first occurence contain the left click state, 
         * the second one contain the middle click state,
         * the third one contain the right click state
         * 
         * @return true 
         * @return false 
         */
        bool *getMouseButton(bool *mouseButtons);
        /**
         * @brief Fill the t_button struct with the information about
         * what buttons have been triggered.
         * 
         * @return t_button* 
         */
        t_button *getButtons(t_button *buttons);
        /**
         * @brief Limit the number of refresh per second. 
         * If the code run faster than the time needed for one tick to happen,
         * the function will wait until this time is reached.
         * If the code takes longer than the time needed for one tick,
         * then it will continue without waiting. 
         * The function can be used for example to set the game max framerate.
         * 
         * @param tickPerSecond Number of time the game must refresh per second
         */
        double setTickRate(double tickPerSecond);



        // Potential useful method
        /**
         * @brief Let you draw any shape as long as the class you give inherits from IShape.
         * 
         * @param shape The shape you want to draw.
         */
        void drawShape(IShape &shape);
        /**
         * @brief Loads an image.
         * 
         * @param path The path of the image to load
         * @return Always return a texture even if the loading fails, however,
         * if it fails it will the texture with the minecraft unknown block texture.
         */
        Texture loadImage(const std::string &path);
        /**
         * @brief Draw the image into the buffer.
         * 
         * @param img The image you want to draw
         */
        void drawImage(Texture &img);
};

class Core
{
public:
    Core();
    ~Core();

    void loadGame(std::string game);
    std::size_t runGame();
    void loadGraphics(std::string graphic);
private:
    std::unique_ptr<IGame> _game;
    std::unique_ptr<IGraphics> _graphic;
};