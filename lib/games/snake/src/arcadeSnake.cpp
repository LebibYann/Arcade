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
    _game_data.map.push_back({1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 2, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 3, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 3, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
    _game_data.map.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 1});
    _game_data.map.push_back({1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    _window_size.push_back(10);
    _window_size.push_back(10);
    _tiles_config.push_back({0, BLACK, " "});
    _tiles_config.push_back({1, WHITE, " "});
    _tiles_config.push_back({2, GREEN, " "});
    _tiles_config.push_back({3, GREEN, " "});
    _tiles_config.push_back({4, YELLOW, " "});
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

    instructions = computeGame(&_game_data, buttons);
    return (instructions);
}
