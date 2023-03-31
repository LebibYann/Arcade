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
        std::cerr << "\t[Graphic library]\t The path of the ";
        std::cerr << ".so graphical library you want to use." << std::endl;
        return (84);
    }
    std::vector<bool> buttons;
    std::vector<bool> mbuttons;
    std::vector<int> mpos;
    Arcade::t_color_custom color;
    Arcade::DLLoader libLoader(argv[1]);
    std::shared_ptr<Arcade::IGraphics> graphics = libLoader.getInstance<Arcade::IGraphics>("entry_point");

    graphics->openWindow(20, 20);
    buttons = graphics->getButtons();
    while (!buttons[Arcade::EXIT]) {
        buttons = graphics->getButtons();
        // for (size_t k = 0; k < buttons.size(); ++k) {
        //     std::cout << buttons[k] << ", ";
        // }
        // std::cout << std::endl;
        // mpos = graphics->getMousePos();
        // std::cout << mpos[0] << ", " << mpos[1] << std::endl;
        // mbuttons = graphics->getMouseButton();
        // std::cout << mbuttons[0] << ", " << mbuttons[1] << ", " << mbuttons[2] << std::endl;
        color.part[0] = 255;
        color.part[1] = 0;
        color.part[2] = 0;
        color.part[3] = 255;
        graphics->fill(color.full);
        color.part[0] = 0;
        color.part[1] = 255;
        color.part[2] = 0;
        color.part[3] = 255;
        graphics->drawTile(0, 0, color.full);
        color.part[0] = 0;
        color.part[1] = 0;
        color.part[2] = 255;
        color.part[3] = 255;
        graphics->drawTile(0, 1, color.full);
        graphics->drawTile(1, 0, color.full);
        graphics->drawTile(1, 1, color.full);
        color.part[0] = 255;
        color.part[1] = 255;
        color.part[2] = 255;
        color.part[3] = 255;
        graphics->drawText("Prout", 0, 0, color.full);
        graphics->display();
    }

    graphics->closeWindow();
    return (0);
}
