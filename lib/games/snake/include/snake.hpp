/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** snake
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Instruction.hpp"

typedef struct s_game_data {
    void *data;
} t_game_data;

typedef struct s_snake {
    int direction;
    std::vector <int> headPos;
    int size;
} t_snake;

typedef struct s_snake_data {
    std::vector <std::vector<int>> map;
    t_snake snake;
    int score;
} t_snake_data;

std::vector <std::vector<int>> loadMap();
t_snake_data loadConfig();