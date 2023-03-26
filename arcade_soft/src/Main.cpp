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
#include <iostream>

int main(int argc, char **argv)
{
    ;

    if (argc < 2) {
        std::cerr << "USAGE:\n";
        std::cerr << "\t./arcade [Graphic library]\n\n";
        std::cerr << "PARAMETERS:\n";
        std::cerr << "\t[Graphic library]\t The path of the ";
        std::cerr << ".so graphical library you want to use." << std::endl;
        return (84);
    }
    // Arcade::DLLoader libLoader(argv[1]);
    // std::unique_ptr<Arcade::IGraphics> graphics = libLoader.getInstance<Arcade::IGraphics>("entry_point");
    // graphics->openWindow(20, 20);
    // graphics->closeWindow();
    return (0);
}
