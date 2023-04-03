/*
** EPITECH PROJECT, 2023
** Ncurse
** File description:
** The header contains all the dependances of the ncurse library
*/

#pragma once

#include "IGraphics.hpp"

#include <ncurses.h>

namespace Arcade
{
    class Ncurse : public IGraphics
    {
    public:
        void openWindow();
        void closeWindow();
    private:
        int _width;
        int _height;
        WINDOW *_win;
    };
}