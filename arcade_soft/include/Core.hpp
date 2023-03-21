/*
** EPITECH PROJECT, 2023
** Core
** File description:
** The header contains the class Core.
*/

#pragma once

#include "IGame.hpp"
#include "IGraphics.hpp"
#include "DLLoader.hpp"

namespace Arcade
{

    typedef enum e_arcade_input
    {
        UP_ARROW,
        DOWN_ARROW,
        LEFT_ARROW,
        RIGHT_ARROW,
        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        PREV_GAME,
        NEXT_GAME,
        PREV_LIB,
        NEXT_LIB,
        RESTART,
        HOME_MENU,
        EXIT,
        TOTAL_INPUT
    } t_arcade_input;

    typedef struct s_tile_data
    {
        int id;
        bool img_loaded;
        void *img;
        int color;
    } t_tile_data;

    class Core
    {
    public:
        Core();
        ~Core();

        void loadGame(std::string game);
        std::size_t runGame();
        void loadGraphics(std::string graphic);
        /**
         * @brief Limit the number of refresh per second.
         * If the code run faster than the time needed for one tick to happen,
         * the function will wait until this time is reached.
         * If the code takes longer than the time needed for one tick,
         * then it will continue without waiting.
         * The function can be used for example to set the game max framerate.
         *
         * @param tickPerSecond Number of time the game must refresh per second
         */
        double setTickRate(double tickPerSecond);

    private:
        std::unique_ptr<IGame> _game;
        std::unique_ptr<IGraphics> _graphic;
    };
}