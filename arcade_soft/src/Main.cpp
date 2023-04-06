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
    Arcade::Core core;

    if (argc < 2) {
        std::cerr << "USAGE:\n";
        std::cerr << "\t./arcade [Graphic library]\n\n";
        std::cerr << "PARAMETERS:\n";
        std::cerr << "\t[Graphic library]\t The path of the ";
        std::cerr << ".so graphical library you want to use." << std::endl;
        return (84);
    }
    std::vector<Arcade::t_score_data> score;

    core.addGameScore(score, 10, "BOB");
    core.addGameScore(score, 5, "LEL");
    core.addGameScore(score, 30, "YAN");
    core.addGameScore(score, 20, "JPP");
    core.saveGameScore(score, "snake.so");
    try {
        core.loadGraphics(argv[1]);
        core.run();
    }
    catch(Arcade::DLLoader::BadLibrary& e) {
        std::cerr << e.what() << '\n';
        return (84);
    }
    return (0);
}
