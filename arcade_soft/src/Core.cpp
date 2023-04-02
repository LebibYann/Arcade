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

void Arcade::Core::loadGame(const std::string &gameLibName)
{
    this->_gameLib.Load(gameLibName);
    this->_game = this->_gameLib.getInstance<Arcade::IGame>("entry_point");
    this->_tileCnf = this->_game->getTilesConfig();
    this->initTileData();
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

void Arcade::Core::initTileData(void)
{
    t_tile_data tmpData;

    this->_tileData.clear();
    for (size_t i = 0; i < this->_tileCnf.size(); ++i) {
        tmpData.id = this->_tileCnf[i].id;
        tmpData.color = this->_tileCnf[i].color;
        tmpData.img = nullptr;
        // if (this->_tileCnf[i].path.c_str() != nullptr)
        //     tmpData.img = this->_graphic->loadImage(this->_tileCnf[i].path);
        this->_tileData.push_back(tmpData);
    }
}

void Arcade::Core::run(void)
{
    std::vector<bool> buttons = this->_graphic->getButtons();
    std::vector<std::shared_ptr<IInstruction>> inst;

    while (!buttons[Arcade::EXIT]) {
        buttons = this->_graphic->getButtons();
        if (this->_game == nullptr) {

        } else {
            inst = this->_game->computeFrame(buttons);
            this->interpretInstruction(inst);
        }
        this->interpretInstruction(inst);
        this->_graphic->display();
    }
}

void Arcade::Core::interpretInstruction(const std::vector<std::shared_ptr<IInstruction>> &instr)
{
    for (size_t i = 0; i < instr.size(); ++i) {
        switch (instr[i]->getId()) {
            case INST_FILL:
                this->fill(instr[i]);
                break;
            case INST_DRAW_TILE:
                this->drawTile(instr[i]);
                break;
            case INST_DRAW_TEXT:
                this->drawText(instr[i]);
                break;
        }
    }
}

void Arcade::Core::fill(const std::shared_ptr<IInstruction> &instr)
{
    InstFill *cast_instr = dynamic_cast<InstFill*>(instr.get());

    this->_graphic->fill(cast_instr->get_color());
}

void Arcade::Core::drawTile(const std::shared_ptr<IInstruction> &instr)
{
    InstDrawTile *cast_instr = dynamic_cast<InstDrawTile*>(instr.get());

    this->_graphic->drawTile(cast_instr->get_x(), cast_instr->get_y(), 255);
    // this->_graphic->draw(cast_instr->get_color());
}

void Arcade::Core::drawText(const std::shared_ptr<IInstruction> &instr)
{
    InstDrawText *cast_instr = dynamic_cast<InstDrawText*>(instr.get());

    this->_graphic->drawText(cast_instr->get_text(), cast_instr->get_x(), cast_instr->get_y(), cast_instr->get_color());
    // this->_graphic->draw(cast_instr->get_color());
}
