/*
** EPITECH PROJECT, 2023
** snake
** File description:
** ArcadeSnake
*/

#include "snake.hpp"

// The core runs at 30 frames per second: the snake moves 6 times per second
#define SNAKE_FRAMES_PER_STEP 5

ArcadeSnake::ArcadeSnake()
    : GridSnake::Game(SNAKE_FRAMES_PER_STEP), _rng(std::random_device{}())
{
    _map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    spawn({4, 4}, Arcade::UP_ARROW, 3);
    placeFood();
}

void ArcadeSnake::step(const std::vector<bool> &inputs)
{
    int next;

    if (_gameOver)
        return (removeTail());
    steer(inputs);
    next = tileAt(nextCell());
    if (next == GridSnake::WALL || next == GridSnake::BODY)
        return (die());
    if (next == GridSnake::FOOD)
        _score += 1;
    advance(next == GridSnake::FOOD);
    if (!placeFood())
        die();
}

bool ArcadeSnake::placeFood(void)
{
    std::vector<GridSnake::Cell> freeCells;

    if (hasTile(GridSnake::FOOD))
        return (true);
    for (int y = 0; y < height(); ++y)
        for (int x = 0; x < (int)_map[y].size(); ++x)
            if (_map[y][x] == GridSnake::GROUND)
                freeCells.push_back({x, y});
    if (freeCells.empty())
        return (false);
    GridSnake::Cell food = freeCells[std::uniform_int_distribution<std::size_t>(
        0, freeCells.size() - 1)(_rng)];
    _map[food.y][food.x] = GridSnake::FOOD;
    return (true);
}
