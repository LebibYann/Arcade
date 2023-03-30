/*
** EPITECH PROJECT, 2023
** snake
** File description:
** loadConfig
*/

#include "../include/snake.hpp"

std::vector <int> findHead(std::vector <std::vector<int>> map)
{
    std::vector <int> headPos;
    headPos.push_back(0);
    headPos.push_back(0);

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 2) {
                headPos[0] = j;
                headPos[1] = i;
                return (headPos);
            }
        }
    }
    return (headPos);
}

t_snake_data loadConfig()
{
    t_snake_data game_data;

    game_data.map = loadMap();
    game_data.snake.direction = 0;
    game_data.snake.size = 3;
    game_data.score = 0;
    return (game_data);
}