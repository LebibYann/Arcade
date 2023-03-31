/*
** EPITECH PROJECT, 2023
** snake
** File description:
** getAction
*/

#include "../include/snake.hpp"

std::vector <IInstruction> computeFrame(t_game_data *game_data, std::vector<bool> inputs)
{
    std::vector <IInstruction> instructions;
    t_snake_data *game = static_cast<t_snake_data*> (game_data->data);

    instructions = computeGame(game, inputs);
    return (instructions);
}