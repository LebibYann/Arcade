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
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "USAGE:\n";
        std::cerr << "\t./arcade [Graphic library]\n\n";
        std::cerr << "PARAMETERS:\n";
        std::cerr << "\t[Graphic library]\t The path of the .so graphics library to start with,\n";
        std::cerr << "\t\t\t\t or its name in the lib directory (e.g. arcade_sdl2.so)." << std::endl;
        return (84);
    }
    try {
        Arcade::Core core;
        std::string graphicLib = argv[1];

        // Also accept a library name from the lib directory of the arcade
        if (!std::filesystem::exists(graphicLib) &&
            std::filesystem::exists(core.getLibDir() + graphicLib))
            graphicLib = core.getLibDir() + graphicLib;
        core.loadGraphics(graphicLib);
        core.run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return (84);
    }
    return (0);
}
