/*
** EPITECH PROJECT, 2023
** snake
** File description:
** main
*/

#include "nibbler.hpp"
#include <unistd.h>

int main()
{
    int i = 0;
    std::vector <bool> inputs;
    inputs.push_back(false);
    inputs.push_back(false);
    inputs.push_back(true);
    inputs.push_back(false);

    t_nibbler_data *game_data = loadConfig();
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
        usleep(1.0/7.0 * 1000000);
        i++;
    }
    return (0);
}
