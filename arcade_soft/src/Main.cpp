/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Main
*/


#include "Core.hpp"
#include "IGraphics.hpp"
#include "IGame.hpp"
#include "DLLoader.hpp"
#include <memory>

int main(void)
{
    Arcade::DLLoader loader("./caca.so");
    std::unique_ptr<Arcade::IGame> game;
    loader.getInstance<Arcade::IGame>("caca");
    return (0);
}
