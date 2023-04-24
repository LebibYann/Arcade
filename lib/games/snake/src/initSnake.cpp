/*
** EPITECH PROJECT, 2023
** snake
** File description:
** loadConfig
*/

#include "snake.hpp"

void initSnake(t_snake_data *game_data)
{
    std::vector <int> pos;
    pos.push_back(0);
    pos.push_back(0);

    game_data->gameOver = false;
    game_data->snake.headPos = {4, 4};
    game_data->snake.direction = 0;
    game_data->snake.size = 3;
    game_data->snake.body.clear();
    for (int i = 0; i < game_data->snake.size; ++i) {
        pos[0] = game_data->snake.headPos[0];
        pos[1] = game_data->snake.headPos[1] + i;
        game_data->snake.body.push_back(pos);
    }
}
