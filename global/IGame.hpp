/*
** EPITECH PROJECT, 2023
** IGame
** File description:
** The header contains the class IGame.
*/

#pragma once

#include <Instruction.hpp>

#include <cstddef>
#include <vector>
#include <string>

namespace Arcade
{
    typedef struct s_tile_config {
        int id; // Same id as the one InstDrawTile
        int color; // Normally an enum with fixed color
        std::string path; // The of the texture if needed
    } t_tile_config;

    class IGame
    {
    public:
        /**
         * @brief Call the main equivalent function to compute a frame of the game.
         *
         * @param buttons A bool table which represent the buttons pressed in the current frame.
         * @return List of instructions to execute.
         */
        virtual std::vector<IInstruction> computeFrame(bool *buttons) = 0;
        /**
         ** @brief Gives information about the game tiles
         ** their id, color, and potentialy texture.
         **
         ** @return std::vector<t_tile_config>
         */
        virtual std::vector<t_tile_config> getTilesConfig(void) const = 0;
        /**
         ** @brief Gives information about the number of tiles
         ** in width and height required by the game.
         **
         ** @return std::vector<int>
         */
        virtual std::vector<int> getWindowSize(void) const = 0;
        /**
         ** @brief Get the game's score
         **
         ** @return int
         */
        virtual std::size_t getScore(void) const = 0;
    };
};
