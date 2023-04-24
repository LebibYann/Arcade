/**
** EPITECH PROJECT, 2023
** IGame
** File description:
** The header contains the class IGame.
** \file IGame.hpp
*/

#pragma once

#include "Instruction.hpp"

#include <cstddef>
#include <vector>
#include <string>
#include <memory>

namespace Arcade
{
    /**
     ** @brief Gives informations about a tile of the game.
     ** Depending on the library and if an image path is given,
     ** the program will decide if it must draw a colored square or display an image.
     **
     */
    typedef struct s_tile_config {
        int id; // Same id as the one InstDrawTile
        int color; // Correspond to color fixed in the enum ArcadeColor
        std::string path; // The path of the texture if needed.
    } t_tile_config;

    /**
     ** @brief This class refer all methods that you should code
     ** in order to add a new game to the arcade software,
     ** you must inherit of it if possible.
     ** Do not forget to implement the two extern "C" function
     ** which are entry_point and get_type.
     */
    class IGame
    {
    public:
        /**
         * @brief Call a main equivalent function to compute one frame of the game.
         *
         * @param buttons A bool table which represent the buttons pressed in the current frame.
         * These buttons are referenced in t_arcade_input.
         * @return std::vector<std::shared_ptr<IInstruction>>
         * For list of instructions to execute, look in the Instruction section.
         */
        virtual std::vector<std::shared_ptr<IInstruction>> computeFrame(std::vector<bool> buttons) = 0;
        /**
         ** @brief Gives informations about game tiles
         ** their id, color, and potentialy texture.
         **
         ** @return std::vector<t_tile_config>
         */
        virtual std::vector<t_tile_config> getTilesConfig(void) const = 0;
        /**
         ** @brief Gives informations about the number of tiles
         ** in width and height required by the game.
         **
         ** @return std::vector<int> The first occurence is the width and
         ** the second occurrence is the height
         */
        virtual std::vector<int> getWindowSize(void) const = 0;
        /**
         ** @brief Get the game's score.
         **
         ** @return int return the game score.
         */
        virtual std::size_t getScore(void) const = 0;
    };
};
