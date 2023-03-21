/*
** EPITECH PROJECT, 2023
** IGame
** File description:
** The header contains the class IGame.
*/

#pragma once

#include <cstddef>

namespace Arcade
{
    typedef struct s_game_data
    {
        int mapWidth;
        int mapHeight;
        char *map;
        int score;
        void *data;
    } t_game_data;

    class IGame
    {
    public:
        /**
         * @brief Call the main equivalent function to start the game
         *
         * @param graphics
         * @return std::size_t
         */
        std::size_t computeFrame(t_game_data &gdata, bool *inputs);
    };
}