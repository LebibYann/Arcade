/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "ArcadeLibcaca.hpp"

extern "C" std::shared_ptr<ArcadeLibcaca> entry_point()
{
    return (std::make_shared<ArcadeLibcaca>());
}

extern "C" int get_type(void)
{
    return (1);
}
