/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** snake
*/

#pragma once

#include <random>

#include "GridSnake.hpp"

/**
 ** @brief Classic snake: eat the apples to grow, without hitting a wall
 ** or your own body. One point per apple.
 */
class ArcadeSnake : public GridSnake::Game {
public:
    ArcadeSnake();

protected:
    void step(const std::vector<bool> &inputs) override;

private:
    /**
     ** @brief Put an apple on a free cell if there is none on the map.
     **
     ** @return false if there is no free cell left: the snake fills the map.
     */
    bool placeFood(void);

    std::mt19937 _rng;
};
