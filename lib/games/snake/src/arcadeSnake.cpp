/*
** EPITECH PROJECT, 2023
** snake
** File description:
** getAction
*/

#include "snake.hpp"

ArcadeSnake::ArcadeSnake()
{
    initSnake(&_game_data);
    this->_game_data.score = 0;
    _game_data.map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    _window_size.push_back(10);
    _window_size.push_back(10);
    _tiles_config.push_back({0, BLACK, " "});
    _tiles_config.push_back({1, WHITE, " "});
    _tiles_config.push_back({2, YELLOW, " "});
    _tiles_config.push_back({3, GREEN, " "});
    _tiles_config.push_back({4, RED, " "});
}

void ArcadeSnake::reset()
{
    initSnake(&_game_data);
    this->_game_data.score = 0;
    _game_data.map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    counter = 0;
}

std::vector <int> ArcadeSnake::getWindowSize(void) const
{
    return (_window_size);
}

std::vector<Arcade::t_tile_config> ArcadeSnake::getTilesConfig(void) const
{
    return (_tiles_config);
}

std::size_t ArcadeSnake::getScore(void) const
{
    return (this->_game_data.score);
}

std::vector<std::shared_ptr<IInstruction>> ArcadeSnake::computeFrame(std::vector<bool> buttons)
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

void ArcadeSnake::accumulateInput(const std::vector<bool> &buttons)
{
    this->_buttons.resize(buttons.size());
    for (size_t i = 0; i < this->_buttons.size(); ++i)
        this->_buttons[i] = (buttons[i] || this->_buttons[i]);
}
