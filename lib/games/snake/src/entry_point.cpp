/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "snake.hpp"

extern "C" std::shared_ptr<ArcadeSnake> entry_point()
{
    return (std::make_shared<ArcadeSnake>());
}

extern "C" int get_type(void)
{
    return (0);
}
