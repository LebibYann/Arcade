/*
** EPITECH PROJECT, 2023
** snake
** File description:
** game
*/

#include "snake.hpp"

void moveHandler(t_snake_data *game, std::vector<bool> inputs)
{
    if (inputs[0] == true && game->snake.direction != 1)
        game->snake.direction = 0;
    else if (inputs[1] == true && game->snake.direction != 0)
        game->snake.direction = 1;
    else if (inputs[2] == true && game->snake.direction != 3)
        game->snake.direction = 2;
    else if (inputs[3] == true && game->snake.direction != 2)
        game->snake.direction = 3;
}

void collisionHandler(t_snake_data *game, std::vector<bool> inputs)
{
    if (game->snake.direction == 0) {
        d
    }
}

std::vector <IInstruction> computeGame(t_snake_data *game, std::vector<bool> inputs)
{
    std::vector <IInstruction> instructions;

    moveHandler(game, inputs);

}