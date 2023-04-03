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
    std::shared_ptr<Arcade::IGraphics> graphics;
    Arcade::DLLoader libLoader;

    if (argc < 2) {
        std::cerr << "USAGE:\n";
        std::cerr << "\t./arcade [Graphic library]\n\n";
        std::cerr << "PARAMETERS:\n";
        std::cerr << "\t[Graphic library]\t The path of the ";
        std::cerr << ".so graphical library you want to use." << std::endl;
        return (84);
    }
    (void)argv;
//    std::vector<bool> buttons;
//     buttons.resize(Arcade::TOTAL_INPUT);
//     try
//     {
//         libLoader.Load(argv[1]);
//         graphics = libLoader.getInstance<Arcade::IGraphics>("entry_point");
//     }
//     catch(Arcade::DLLoader::BadLibrary& e)
//     {
//         std::cerr << e.what() << '\n';
//         return (84);
//     }
//     std::string str("prout");
//     for (size_t i = 1; i != 100000; ++i) {
//         graphics->fill(Arcade::BLACK);
//         graphics->drawTile(0, 0, Arcade::GREEN);
//         graphics->drawTile(0, 1, Arcade::BLUE);
//         graphics->drawTile(1, 0, Arcade::BLUE);
//         graphics->drawTile(1, 1, Arcade::BLUE);
//         graphics->drawText(str.c_str(), 0, 5, Arcade::WHITE);
//         graphics->display();
//         char c = graphics->getKeyboard();
//         if (c == 127 && str.size() != 0)
//             str.pop_back();
//         else if (c != 0 && c != 127)
//             str += c;
//         graphics->getButtons(buttons);
//         if (buttons[Arcade::EXIT])
//             break;
//     }
    return (0);
}
