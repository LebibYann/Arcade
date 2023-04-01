/*
** EPITECH PROJECT, 2023
** snake
** File description:
** main
*/

#include "../include/snake.hpp"

int main()
{
    int i = 0;
    std::vector <bool> inputs;
    inputs.push_back(false);
    inputs.push_back(false);
    inputs.push_back(true);
    inputs.push_back(false);

    t_snake_data *game_data = loadConfig();
    while (1) {
        if (i % 100000 == 0) {
            computeGame(game_data, inputs);
            for (size_t i = 0; i < game_data->map.size(); ++i) {
                for (size_t j = 0; j < game_data->map[i].size(); ++j) {
                    std::cout << game_data->map[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << "---------------------------------------------------------\n";
        }
        i++;
    }
    return (0);
}
