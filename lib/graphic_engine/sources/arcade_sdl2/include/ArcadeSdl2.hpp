/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeSdl2
*/

#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <iomanip>
#include <iostream>

#include "IGraphics.hpp"

class ArcadeSdl2: public Arcade::IGraphics {
public:
    ArcadeSdl2();
    ~ArcadeSdl2();

    void openWindow(int width, int height);
    void closeWindow();
    void *loadImage(const std::string &path);
    void loadFont(const std::string &path);
    void drawTile(int x, int y, uint32_t color);
    void drawImage(int x, int y, void *img);
    void drawText(std::string &text, int x, int y, int color);
    void display(void);

    std::vector<int> getMousePos(void);
    std::vector<bool> getMouseButton(void);
    std::vector<bool> getButtons(void);

private:
    int tileSize = 10;
    SDL_Window *_window = nullptr;
};
