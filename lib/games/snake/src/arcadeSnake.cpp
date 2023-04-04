/*
** EPITECH PROJECT, 2023
** snake
** File description:
** getAction
*/

#include "snake.hpp"

ArcadeSnake::ArcadeSnake()
{
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
    t_snake_data *game = static_cast<t_snake_data*> (_game_data->data);
    return (game->score);
}

std::vector<std::shared_ptr<IInstruction>> ArcadeSnake::computeFrame(std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;
    t_snake_data *game = static_cast<t_snake_data*> (_game_data->data);

    instructions = computeGame(game, buttons);
    return (instructions);
}