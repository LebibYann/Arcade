/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "ArcadeNcurses.hpp"

extern "C" std::shared_ptr<ArcadeNcurses> entry_point()
{
    return (std::make_shared<ArcadeNcurses>());
}

extern "C" int get_type(void)
{
    return (1);
}
