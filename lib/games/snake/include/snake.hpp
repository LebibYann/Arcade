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
#include "IGame.hpp"

typedef enum e_ArcadeColor {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
} t_ArcadeColor;

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

typedef struct s_snake_data {
    std::vector <std::vector<int>> map;
    t_snake snake;
    int score;
} t_snake_data;

std::vector <std::vector<int>> loadMap();
t_snake_data *loadConfig();
std::vector <int> findHead(std::vector <std::vector<int>> map);
std::vector<std::shared_ptr<IInstruction>> computeGame(t_snake_data *game, std::vector<bool> inputs);
std::vector<std::shared_ptr<IInstruction>> computeFrame(t_game_data *game_data, std::vector<bool> buttons);

class ArcadeSnake: public Arcade::IGame {
public:
    ArcadeSnake();
    ~ArcadeSnake();

    std::vector<std::shared_ptr<IInstruction>> computeFrame(std::vector<bool> buttons);
    std::vector<Arcade::t_tile_config> getTilesConfig(void) const;
    std::vector<int> getWindowSize(void) const;
    std::size_t getScore(void) const;
};
