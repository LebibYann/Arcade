/*
** EPITECH PROJECT, 2023
** snake
** File description:
** loadConfig
*/

#include "nibbler.hpp"

void initSnake(t_nibbler_data *game_data)
{
    std::vector <int> pos;
    pos.push_back(0);
    pos.push_back(0);

    game_data->snake.headPos = {10, 17};
    game_data->snake.direction = RIGHT;
    game_data->snake.size = 3;
    for (int i = 0; i < game_data->snake.size; ++i) {
        pos[0] = game_data->snake.headPos[0] - i;
        pos[1] = game_data->snake.headPos[1];
        game_data->snake.body.push_back(pos);
    }
}
