/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** GridSnake
** \file GridSnake.hpp
*/

#pragma once

#include <algorithm>
#include <cstddef>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "IGame.hpp"
#include "IGraphics.hpp"
#include "Instruction.hpp"

/**
 ** @brief Shared logic of the games where a snake moves on a grid
 ** (Snake and Nibbler): steering, moving, death animation and drawing.
 ** Each game only implements step(), called at the game speed.
 */
namespace GridSnake
{
    /**
     ** @brief Content of a map cell. It is also the tile id given to the core.
     */
    enum Tile {
        GROUND = 0,
        WALL = 1,
        HEAD = 2,
        BODY = 3,
        FOOD = 4
    };

    typedef std::vector<std::vector<int>> Map;

    struct Cell {
        int x;
        int y;
    };

    class Game : public Arcade::IGame
    {
    public:
        std::vector<std::shared_ptr<IInstruction>> computeFrame(std::vector<bool> buttons) override
        {
            _pending.resize(buttons.size(), false);
            for (std::size_t i = 0; i < buttons.size(); ++i)
                _pending[i] = _pending[i] || buttons[i];
            if (_frame == 0) {
                _pending.resize(Arcade::TOTAL_INPUT, false);
                step(_pending);
                std::fill(_pending.begin(), _pending.end(), false);
                _instructions = draw();
            }
            _frame = (_frame + 1) % _framesPerStep;
            return (_instructions);
        }

        std::vector<Arcade::t_tile_config> getTilesConfig(void) const override
        {
            return {
                {GROUND, Arcade::BLACK, ""},
                {WALL, Arcade::WHITE, ""},
                {HEAD, Arcade::YELLOW, ""},
                {BODY, Arcade::GREEN, ""},
                {FOOD, Arcade::RED, ""}
            };
        }

        std::vector<int> getWindowSize(void) const override
        {
            return {width(), height()};
        }

        std::size_t getScore(void) const override
        {
            return (_score);
        }

    protected:
        /**
         ** @param framesPerStep The snake moves once every framesPerStep
         ** frames. The core runs at 30 frames per second.
         */
        explicit Game(int framesPerStep) : _framesPerStep(framesPerStep) {}

        /**
         ** @brief Advance the game by one move.
         **
         ** @param inputs The buttons pressed since the last step,
         ** indexed by Arcade::t_arcade_input.
         */
        virtual void step(const std::vector<bool> &inputs) = 0;

        virtual std::vector<std::shared_ptr<IInstruction>> draw(void) const
        {
            std::vector<std::shared_ptr<IInstruction>> instructions;

            if (_gameOver && _body.empty()) {
                instructions.push_back(std::make_shared<InstDrawText>(
                    width() / 2 - 3, height() / 2, Arcade::WHITE, "Game over !"));
                return (instructions);
            }
            for (int y = 0; y < height(); ++y)
                for (int x = 0; x < (int)_map[y].size(); ++x)
                    instructions.push_back(std::make_shared<InstDrawTile>(x, y, _map[y][x]));
            return (instructions);
        }

        int width(void) const { return (_map.empty() ? 0 : (int)_map[0].size()); }
        int height(void) const { return ((int)_map.size()); }

        /**
         ** @brief Tile at a cell, or WALL outside the map.
         */
        int tileAt(Cell cell) const
        {
            if (cell.y < 0 || cell.y >= height() ||
                cell.x < 0 || cell.x >= (int)_map[cell.y].size())
                return (WALL);
            return (_map[cell.y][cell.x]);
        }

        /**
         ** @brief Place a snake of size cells with its head at head,
         ** the body trailing behind it.
         */
        void spawn(Cell head, int direction, int size)
        {
            Cell back = offset(direction);

            _body.clear();
            _direction = direction;
            for (int i = 0; i < size; ++i) {
                Cell cell = {head.x - back.x * i, head.y - back.y * i};
                _body.push_back(cell);
                _map[cell.y][cell.x] = (i == 0) ? HEAD : BODY;
            }
        }

        /**
         ** @brief Turn the snake from the arrow keys. It cannot turn back
         ** onto itself.
         */
        void steer(const std::vector<bool> &inputs)
        {
            if (inputs[Arcade::UP_ARROW] && _direction != Arcade::DOWN_ARROW)
                _direction = Arcade::UP_ARROW;
            else if (inputs[Arcade::DOWN_ARROW] && _direction != Arcade::UP_ARROW)
                _direction = Arcade::DOWN_ARROW;
            else if (inputs[Arcade::LEFT_ARROW] && _direction != Arcade::RIGHT_ARROW)
                _direction = Arcade::LEFT_ARROW;
            else if (inputs[Arcade::RIGHT_ARROW] && _direction != Arcade::LEFT_ARROW)
                _direction = Arcade::RIGHT_ARROW;
        }

        Cell nextCell(void) const
        {
            Cell move = offset(_direction);

            return {_body.front().x + move.x, _body.front().y + move.y};
        }

        /**
         ** @brief Move the snake one cell forward. It keeps its tail when
         ** it grows.
         */
        void advance(bool grow)
        {
            Cell next = nextCell();

            _map[_body.front().y][_body.front().x] = BODY;
            _map[next.y][next.x] = HEAD;
            _body.push_front(next);
            if (!grow)
                removeTail();
        }

        /**
         ** @brief End the game. The snake then disappears one cell per
         ** step before "Game over !" is shown.
         */
        void die(void)
        {
            _gameOver = true;
            removeTail();
        }

        void removeTail(void)
        {
            if (_body.empty())
                return;
            _map[_body.back().y][_body.back().x] = GROUND;
            _body.pop_back();
        }

        bool hasTile(int tile) const
        {
            for (const auto &row : _map)
                for (int cell : row)
                    if (cell == tile)
                        return (true);
            return (false);
        }

        Map _map;
        std::deque<Cell> _body;
        int _direction = Arcade::UP_ARROW;
        std::size_t _score = 0;
        bool _gameOver = false;

    private:
        static Cell offset(int direction)
        {
            switch (direction) {
                case Arcade::UP_ARROW: return {0, -1};
                case Arcade::DOWN_ARROW: return {0, 1};
                case Arcade::LEFT_ARROW: return {-1, 0};
                default: return {1, 0};
            }
        }

        int _framesPerStep;
        int _frame = 0;
        std::vector<bool> _pending;
        std::vector<std::shared_ptr<IInstruction>> _instructions;
    };
}
