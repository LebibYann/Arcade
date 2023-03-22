/*
** EPITECH PROJECT, 2023
** IGame
** File description:
** The header contains the class IGame.
*/

#pragma once

#include <cstddef>
#include <vector>
#include <string>

namespace Arcade
{
    typedef struct s_game_data
    {
        void *data;
    } t_game_data;
    typedef struct s_tile_config {
        int id; // Same id as the one InstDrawTile
        int color; // Normally an enum with fixed color
        std::string path; // The of the texture if needed
    } t_tile_config;

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
        /**
         ** @brief Gives information about the game tiles
         ** their id, color, and potentialy texture.
         **
         ** @return std::vector<t_tile_config>
         */
        std::vector<t_tile_config> getTilesConfig(void) const;
        /**
         ** @brief Get the game's score
         **
         ** @return int
         */
        int getScore(void) const;
    };
}
