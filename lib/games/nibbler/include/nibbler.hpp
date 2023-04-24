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
#include <unistd.h>
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
    RESTART = 12
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
    std::vector <std::vector<std::vector<int>>> maps;
    t_snake snake;
    int timer;
    int score;
    bool gameOver;
    int level;
    int lastEaten;
} t_nibbler_data;

std::vector <std::vector<int>> loadMap();
t_nibbler_data *loadConfig();
std::vector <int> findHead(std::vector <std::vector<int>> map);
std::vector<std::shared_ptr<IInstruction>> computeGame(t_nibbler_data *game, std::vector<bool> inputs);

void moveHandler(t_nibbler_data *game, std::vector<bool> inputs);
void move_snake(t_nibbler_data *game, int collision);
int collisionHandler(t_nibbler_data *game);
void initSnake(t_nibbler_data *game_data);
void loadMaps(t_nibbler_data *game_data);

class ArcadeNibbler: public Arcade::IGame {
public:
    ArcadeNibbler();
    ~ArcadeNibbler();

    std::vector<std::shared_ptr<IInstruction>> computeFrame(std::vector<bool> buttons);
    std::vector<Arcade::t_tile_config> getTilesConfig(void) const;
    std::vector<int> getWindowSize(void) const;
    std::size_t getScore(void) const;

    private:
        void accumulateInput(const std::vector<bool> &buttons);
        t_nibbler_data _game_data;
        std::vector<Arcade::t_tile_config> _tiles_config;
        std::vector<int> _window_size;
        std::size_t _score;
        int counter = 0;
        std::vector<std::shared_ptr<IInstruction>> instr;
        std::vector<bool> _buttons;
};
