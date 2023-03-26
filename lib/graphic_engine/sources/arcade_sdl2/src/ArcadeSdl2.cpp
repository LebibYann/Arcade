/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeSdl2
*/

#include "ArcadeSdl2.hpp"

ArcadeSdl2::ArcadeSdl2()
{
    this->_window = nullptr;
}

ArcadeSdl2::~ArcadeSdl2()
{
    this->closeWindow();
    SDL_Quit();
}

void ArcadeSdl2::openWindow(int width, int height)
{
    if (this->_window == nullptr)
        this->_window = SDL_CreateWindow("Arcade SDL2",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        width * this->tileSize, height * this->tileSize, 0);
    // if (this->_surface == nullptr)
    //     this->_surface = SDL_GetWindowSurface(this->_window);
    if (this->_render == nullptr)
        this->_render = SDL_CreateRenderer(this->_window, -1, 0);
}

void ArcadeSdl2::closeWindow(void)
{
    if (this->_render != nullptr) {
        SDL_DestroyRenderer(this->_render);
        this->_render = nullptr;
    }
    // if (this->_surface != nullptr) {
    //     SDL_FreeSurface(this->_surface);
    //     this->_surface = nullptr;
    // }
    if (this->_window != nullptr) {
        SDL_DestroyWindow(this->_window);
        this->_window = nullptr;
    }

}

void *ArcadeSdl2::loadImage(const std::string &path)
{
    (void)path;
    return (nullptr);
}

void ArcadeSdl2::loadFont(const std::string &path)
{
    (void)path;

}

void ArcadeSdl2::fill(uint32_t color)
{
    char *c = (char*) &color;

    SDL_SetRenderDrawColor(this->_render, c[0], c[1], c[2], c[3]);
    SDL_RenderClear(this->_render);
}

void ArcadeSdl2::drawTile(int x, int y, uint32_t color)
{
    (void)x;
    (void)y;
    (void)color;
}

void ArcadeSdl2::drawImage(int x, int y, void *img)
{
    (void)x;
    (void)y;
    (void)img;
}

void ArcadeSdl2::drawText(std::string &text, int x, int y, int color)
{
    (void)text;
    (void)x;
    (void)y;
    (void)color;
}

void ArcadeSdl2::display(void)
{
    SDL_RenderPresent(this->_render);
}

std::vector<int> ArcadeSdl2::getMousePos(void)
{
    std::vector<int> mousePos;

    return (mousePos);
}

std::vector<bool> ArcadeSdl2::getMouseButton(void)
{
    std::vector<bool> mouseButtons;

    return (mouseButtons);
}

std::vector<bool> ArcadeSdl2::getButtons(void)
{
    std::vector<bool> arcadeButtons;

    return (arcadeButtons);
}
