/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "ArcadeSdl2.hpp"

extern "C" Arcade::IGraphics *entry_point()
{
    return (new ArcadeSdl2());
}

extern "C" int get_type(void)
{
    return (1);
}
