/*
** EPITECH PROJECT, 2023
** Libcaca
** File description:
** The header contains all the dependances of the Libcaca library
*/

#pragma once

#include "IGraphics.hpp"

#include <memory>
#include <map>
#include <caca.h>

#define TILES_X 64
#define TILES_Y 36
#define LIBCACA_MAXX 160
#define LIBCACA_MAXY 90

class ArcadeLibcaca: public Arcade::IGraphics
{
public:
    ArcadeLibcaca();
    ~ArcadeLibcaca();
    void *loadImage(__attribute__((unused)) const std::string &path) {return (NULL);};
    void loadFont(__attribute__((unused)) const std::string &path) {};
    void fill(uint32_t color);
    void drawTile(int x, int y, uint32_t color);
    void drawImage(__attribute__((unused))int x, __attribute__((unused)) int y, __attribute__((unused)) void *img) {};
    void drawText(const std::string &text, int x, int y, int color);
    void display(void);
    void getMousePos(std::vector<int> &coords);
    void getMouseButton(std::vector<bool> &buttons);
    void getButtons(std::vector<bool> &buttons);
    char getKeyboard(void);
private:
    int _width;
    int _height;
    caca_canvas_t *_canva;
    caca_display_t *_display;
    std::map<int, int> _keys;
    std::map<int, std::pair<int, int>> _color;
};
