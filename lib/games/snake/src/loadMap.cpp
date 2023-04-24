/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** loadMap
*/

#include "../include/snake.hpp"

std::vector <std::vector<int>> loadMap()
{
    std::ifstream map;
    std::string line;
    std::vector <std::vector<int>> vect;

    map.open("snake_map");
    if (!map)
        return (vect);
    while (getline(map, line)) {
        std::vector <int> tmp;
        for (int i = 0; line[i] != 0; i++)
            tmp.push_back(line[i] - '0');
        vect.push_back(tmp);
    }
    return (vect);
}
