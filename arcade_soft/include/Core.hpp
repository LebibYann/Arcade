/*
** EPITECH PROJECT, 2023
** Core
** File description:
** The header contains the class Core.
*/

#pragma once

#include <filesystem>
#include <iostream>
#include <cstring>
#include <memory.h>

#include "IGame.hpp"
#include "IGraphics.hpp"
#include "DLLoader.hpp"

#define TILES_X 64
#define TILES_Y 36

namespace Arcade
{
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

        void runGame(std::vector<bool> inputs);
        void runMenu(std::vector<bool> inputs);
        void loadGame(const std::string &gameLibNamegame);
        void loadGraphics(const std::string &graphicLibName);
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
        //double setTickRate(double tickPerSecond);
        void getSOFiles(std::vector<std::string> &list, const std::string &path);
        void getAvailableLib(void);
        void run(void);
        void interpretInstruction(const std::vector<std::shared_ptr<IInstruction>> &instr);
        void fill(const std::shared_ptr<IInstruction> &instr);
        void drawTile(const std::shared_ptr<IInstruction> &instr);
        void drawText(const std::shared_ptr<IInstruction> &instr);
        void initTileData(void);
        t_tile_data getTileData(int id);

    private:
        std::vector<t_tile_config> _tileCnf;
        std::vector<t_tile_data> _tileData;

        std::string _graphicPath = "./lib/graphic_engine/";
        std::string _gamePath = "./lib/games/";
        std::vector<std::string> _gameList;
        std::vector<std::string> _graphicList;
        std::size_t _selected;
        std::shared_ptr<IGame> _game = nullptr;
        std::shared_ptr<IGraphics> _graphic = nullptr;
        Arcade::DLLoader _gameLib;
        Arcade::DLLoader _graphicLib;
    };
}
