/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "snake.hpp"

extern "C" Arcade::IGame *entry_point()
{
    return (new ArcadeSnake());
}

extern "C" int get_type(void)
{
    return (0);
}
