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
#include <memory>
#include "Instruction.hpp"

typedef enum e_snake_tiles {
    GROUND = 0,
    WALL = 1,
    SNAKE_HEAD = 2,
    SNAKE_BODY = 3,
    FOOD = 4
} t_snake_tiles;

typedef enum e_snake_direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
} t_snake_direction;

typedef struct s_game_data {
    void *data;
} t_game_data;

typedef struct s_snake {
    int direction;
    std::vector <int> headPos;
    std::vector <std::vector<int>> body;
    int size;
} t_snake;

typedef struct s_nibbler_data {
    std::vector <std::vector<int>> map;
    t_snake snake;
    int timer;
    int score;
    bool gameOver;
    int lastEaten;
} t_nibbler_data;

std::vector <std::vector<int>> loadMap();
t_nibbler_data *loadConfig();
std::vector <int> findHead(std::vector <std::vector<int>> map);
std::vector<std::shared_ptr<IInstruction>> computeGame(t_nibbler_data *game, std::vector<bool> inputs);
std::vector<std::shared_ptr<IInstruction>> computeFrame(t_game_data *game_data, std::vector<bool> buttons);

void moveHandler(t_nibbler_data *game, std::vector<bool> inputs);
void move_snake(t_nibbler_data *game, int collision);
int collisionHandler(t_nibbler_data *game);