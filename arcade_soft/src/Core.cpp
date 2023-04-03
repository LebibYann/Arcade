/*
** EPITECH PROJECT, 2023
** Core
** File description:
** The file contains all the methods of the class Core
*/

#include "Core.hpp"

Arcade::Core::Core() : _selected(0)
{
    this->getAvailableLib();
}

Arcade::Core::~Core()
{
    _game.reset();
    _graphic.reset();
    _gameLib.unLoad();
    _graphicLib.unLoad();
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
    this->_graphicLib.unLoad();
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

Arcade::t_tile_data Arcade::Core::getTileData(int id)
{
    Arcade::t_tile_data errorTile = {-1, false, nullptr, -1};

    for (size_t i = 0; i < this->_tileData.size(); ++i) {
        if (this->_tileData[i].id == id)
            return (this->_tileData[i]);
    }
    return (errorTile);
}

void Arcade::Core::runGame(std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> inst;

    inst = this->_game->computeFrame(buttons);
    this->interpretInstruction(inst);
}

void Arcade::Core::runMenu(std::vector<bool> buttons)
{
    _graphic->fill(ArcadeColor::MAGENTA);
    _graphic->drawText("GAMES:", 0, 0, RED);
    for (size_t i = 1; i < _gameList.size(); i++)
        _graphic->drawText(_gameList[i], 0, i, BLACK);
    _graphic->drawText("Graphics:", 0, _gameList.size() + 2, RED);
    for (size_t i = 0; i < _graphicList.size(); i++)
        if (i == _selected)
            _graphic->drawText(_graphicList[i], 0, i + _gameList.size() + 3, WHITE);
        else
            _graphic->drawText(_graphicList[i], 0, i + _gameList.size() + 3, BLACK);
    if (buttons[Arcade::DOWN_ARROW] && _selected < _gameList.size() + _graphicList.size() - 1)
        _selected++;
    if (buttons[Arcade::UP_ARROW] && _selected != 0)
        _selected--;
    if (buttons[Arcade::RIGHT_ARROW]){
        if (_selected >= _gameList.size())
            loadGraphics(_graphicPath + _graphicList[_selected]);
        else
            loadGame(_graphicPath + _graphicList[_selected]);
    }
}

void Arcade::Core::run(void)
{
    std::vector<bool> buttons;

    do{
        this->_graphic->getButtons(buttons);
        if (buttons[Arcade::HOME_MENU]) {
            _game = nullptr;
            _gameLib.unLoad();
        }
        if (_game != nullptr)
            runGame(buttons);
        else
            runMenu(buttons);
        this->_graphic->display();
    } while (!buttons[Arcade::EXIT]);
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
    Arcade::t_tile_data tileData = this->getTileData(cast_instr->get_texture());

    this->_graphic->drawTile(cast_instr->get_x(), cast_instr->get_y(), tileData.color);
}

void Arcade::Core::drawText(const std::shared_ptr<IInstruction> &instr)
{
    InstDrawText *cast_instr = dynamic_cast<InstDrawText*>(instr.get());

    this->_graphic->drawText(cast_instr->get_text(), cast_instr->get_x(), cast_instr->get_y(), cast_instr->get_color());
}
