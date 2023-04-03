/*
** EPITECH PROJECT, 2023
** snake
** File description:
** getAction
*/

#include "../include/snake.hpp"

std::vector<std::shared_ptr<IInstruction>> computeFrame(t_game_data *game_data, std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;
    t_snake_data *game = static_cast<t_snake_data*> (game_data->data);

    instructions = computeGame(game, buttons);
    return (instructions);
}
