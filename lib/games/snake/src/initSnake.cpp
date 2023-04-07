/*
** EPITECH PROJECT, 2023
** snake
** File description:
** loadConfig
*/

#include "snake.hpp"

std::vector <int> findHead(std::vector <std::vector<int>> map)
{
    std::vector <int> headPos = {4, 4};

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == SNAKE_HEAD) {
                headPos[0] = j;
                headPos[1] = i;
                return (headPos);
            }
        }
    }
    return (headPos);
}

void initSnake(t_snake_data *game_data)
{
    std::vector <int> pos;
    pos.push_back(0);
    pos.push_back(0);

    game_data->snake.headPos = findHead(game_data->map);
    game_data->snake.direction = 0;
    game_data->snake.size = 3;
    for (int i = 0; i < game_data->snake.size; ++i) {
        pos[0] = game_data->snake.headPos[0];
        pos[1] = game_data->snake.headPos[1] + i;
        game_data->snake.body.push_back(pos);
    }
}
