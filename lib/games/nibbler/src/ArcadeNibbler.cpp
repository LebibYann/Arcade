/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeNibbler
*/

#include "nibbler.hpp"

ArcadeNibbler::ArcadeNibbler()
{
    _window_size.push_back(10);
    _window_size.push_back(10);
    _tiles_config.push_back({0, BLACK, " "});
    _tiles_config.push_back({1, WHITE, " "});
    _tiles_config.push_back({2, GREEN, " "});
    _tiles_config.push_back({3, GREEN, " "});
    _tiles_config.push_back({4, YELLOW, " "});
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
    t_nibbler_data *game = static_cast<t_nibbler_data*> (_game_data->data);
    return (game->score);
}

std::vector<std::shared_ptr<IInstruction>> ArcadeNibbler::computeFrame(std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;
    t_nibbler_data *game = static_cast<t_nibbler_data*> (_game_data->data);

    instructions = computeGame(game, buttons);
    return (instructions);
}
