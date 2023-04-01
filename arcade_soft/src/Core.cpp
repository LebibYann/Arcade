/*
** EPITECH PROJECT, 2023
** Core
** File description:
** The file contains all the methods of the class Core
*/

#include "Core.hpp"

Arcade::Core::Core()
{
    this->getAvailableLib();
}

Arcade::Core::~Core()
{
}

void Arcade::Core::loadGraphics(const std::string &graphicLibName)
{
    this->_graphicLib.Load(graphicLibName);
    this->_graphic = this->_graphicLib.getInstance<Arcade::IGraphics>("entry_point");
}

void Arcade::Core::getSOFiles(std::vector<std::string> &list, const std::string &path)
{
    list.clear();
    std::filesystem::path fpath = path;
    std::string tmp;
    std::string libName;

    for (const auto& entry : std::filesystem::directory_iterator(fpath)) {
        tmp = entry.path();
        if (strcmp(".so", &tmp.c_str()[tmp.length() - 3]) == 0) {
            libName = strrchr(tmp.c_str(), '/');
            if (libName.c_str() == nullptr)
                list.push_back(tmp);
            else {
                list.push_back(&libName.c_str()[1]);
            }
        }
    }
}

void Arcade::Core::getAvailableLib(void)
{
    this->getSOFiles(this->_graphicList, this->_graphicPath);
    this->getSOFiles(this->_gameList, this->_gamePath);
}

void Arcade::Core::run(void)
{
}
