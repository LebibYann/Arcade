/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** entry_point
*/

#include "ArcadeSdl2.hpp"

extern "C" std::shared_ptr<ArcadeSdl2> entry_point()
{
    return (std::make_shared<ArcadeSdl2>());
}

extern "C" int get_type(void)
{
    return (1);
}
