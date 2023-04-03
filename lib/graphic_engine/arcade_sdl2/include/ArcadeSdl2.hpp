/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeSdl2
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <vector>
#include <memory>
#include <iomanip>
#include <iostream>

#include "IGraphics.hpp"

#define SDL_SETCOLOR(r, g, b, a) (r | (g << 8) | (b << 16) | (a << 24))

typedef union u_sdl_color {
    uint32_t full;
    uint8_t rgba[4];
} t_sdl_color;

class ArcadeSdl2: public Arcade::IGraphics {
public:
    ArcadeSdl2();
    ~ArcadeSdl2();

    void *loadImage(const std::string &path);
    void loadFont(const std::string &path);
    void fill(uint32_t color);
    void drawTile(int x, int y, uint32_t color);
    void drawImage(int x, int y, void *img);
    void drawText(const std::string &text, int x, int y, int color);
    void display(void);

    std::vector<int> getMousePos(void);
    std::vector<bool> getMouseButton(void);
    std::vector<bool> getButtons(void);
    char getKeyboard(void) {return 'c';}

private:
    void openWindow(int width, int height);
    void closeWindow();
    // void unloadImage();
    void unloadFont(void);
    void handleEvent(void);
    void updateMatchingKey(SDL_Event event, bool toState);
    int _tileSize = 30;
    std::vector<t_sdl_color> _colors;
    std::vector<int> _keyId;
    std::vector<bool> _arcadeButtons;
    SDL_Window *_window = nullptr;
    SDL_Surface *_surface = nullptr;
    SDL_Renderer *_render = nullptr;
    SDL_Event _event;
    TTF_Font *_font;
    SDL_Rect _rect;
};
