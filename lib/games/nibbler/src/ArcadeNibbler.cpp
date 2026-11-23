/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeNibbler
*/

#include "nibbler.hpp"

// The core runs at 30 frames per second: the snake moves 6 times per second
#define NIBBLER_FRAMES_PER_STEP 5

ArcadeNibbler::ArcadeNibbler()
    : GridSnake::Game(NIBBLER_FRAMES_PER_STEP), _maps(loadMaps())
{
    startLevel();
}

void ArcadeNibbler::startLevel(void)
{
    _map = _maps[_level];
    _timer = NIBBLER_START_TIMER;
    spawn({10, 17}, Arcade::RIGHT_ARROW, 3);
}

std::vector<int> ArcadeNibbler::getWindowSize(void) const
{
    // One more row under the maze for the level and the timer
    return {width(), height() + 1};
}

void ArcadeNibbler::step(const std::vector<bool> &inputs)
{
    int next;

    if (_gameOver)
        return (removeTail());
    steer(inputs);
    next = tileAt(nextCell());
    if (next == GridSnake::BODY)
        return (die());
    if (next != GridSnake::WALL) {
        if (next == GridSnake::FOOD)
            _score += 10;
        advance(next == GridSnake::FOOD);
    }
    _timer -= 1;
    if (!hasTile(GridSnake::FOOD)) {
        _score += _timer;
        _level = (_level + 1) % _maps.size();
        return (startLevel());
    }
    if (_timer <= 0)
        die();
}

std::vector<std::shared_ptr<IInstruction>> ArcadeNibbler::draw(void) const
{
    std::vector<std::shared_ptr<IInstruction>> instructions = GridSnake::Game::draw();

    instructions.push_back(std::make_shared<InstDrawText>(0, height(), Arcade::WHITE,
        "Level " + std::to_string(_level + 1) + "   Time " + std::to_string(_timer)));
    return (instructions);
}
