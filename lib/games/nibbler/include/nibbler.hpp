/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** nibbler
*/

#pragma once

#include "GridSnake.hpp"

#define NIBBLER_START_TIMER 999

std::vector<GridSnake::Map> loadMaps(void);

/**
 ** @brief Eat every apple of the maze before the timer runs out.
 ** Ten points per apple, and the time left is added to the score when
 ** the level is cleared. The snake stops against walls and dies when
 ** it bites itself.
 */
class ArcadeNibbler : public GridSnake::Game {
public:
    ArcadeNibbler();

    std::vector<int> getWindowSize(void) const override;

protected:
    void step(const std::vector<bool> &inputs) override;
    std::vector<std::shared_ptr<IInstruction>> draw(void) const override;

private:
    void startLevel(void);

    std::vector<GridSnake::Map> _maps;
    std::size_t _level = 0;
    int _timer = NIBBLER_START_TIMER;
};
