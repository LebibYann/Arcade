/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeNibbler
*/

#include "nibbler.hpp"

ArcadeNibbler::ArcadeNibbler()
{
    initSnake(&_game_data);
    _game_data.score = 0;
    _game_data.timer = 999;
    _game_data.gameOver = false;
    _game_data.lastEaten = 0;
    _game_data.level = 1;
    loadMaps(&_game_data);
    _game_data.map = _game_data.maps[0];
    _window_size.push_back(19);
    _window_size.push_back(19);
    _tiles_config.push_back({0, BLACK, " "});
    _tiles_config.push_back({1, WHITE, " "});
    _tiles_config.push_back({2, YELLOW, " "});
    _tiles_config.push_back({3, GREEN, " "});
    _tiles_config.push_back({4, RED, " "});
}

ArcadeNibbler::~ArcadeNibbler()
{
}

std::vector <int> ArcadeNibbler::getWindowSize(void) const
{
    return (_window_size);
}

std::vector<Arcade::t_tile_config> ArcadeNibbler::getTilesConfig(void) const
{
    return (_tiles_config);
}

std::size_t ArcadeNibbler::getScore(void) const
{
    return (_game_data.score);
}

std::vector<std::shared_ptr<IInstruction>> ArcadeNibbler::computeFrame(std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;

    this->accumulateInput(buttons);
    if (this->counter == 0) {
        this->instr = computeGame(&_game_data, this->_buttons);
        std::fill(this->_buttons.begin(), this->_buttons.end(), false);
    }
    usleep(1.0 / 30.0 * 1e6);
    ++counter;
    counter = counter % 5;
    return (this->instr);
}

void ArcadeNibbler::accumulateInput(const std::vector<bool> &buttons)
{
    this->_buttons.resize(buttons.size());
    for (size_t i = 0; i < this->_buttons.size(); ++i)
        this->_buttons[i] = (buttons[i] || this->_buttons[i]);
}
