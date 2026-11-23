/*
** EPITECH PROJECT, 2023
** Ncurse
** File description:
** The header contains all the dependances of the ncurse library
*/

#pragma once

#include "IGraphics.hpp"

#include <ncurses.h>
#include <algorithm>
#include <deque>
#include <memory>
#include <map>

#define TILES_X 64
#define TILES_Y 36
#define NCURSE_MAXX 190
#define NCURSE_MAXY 45

class ArcadeNcurses : public Arcade::IGraphics
{
public:
    ArcadeNcurses();
    ~ArcadeNcurses();
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
    WINDOW *_win;
    std::map<int, int> keys;
    // Characters typed since the last getButtons call, for getKeyboard
    std::deque<char> _typed;
};
