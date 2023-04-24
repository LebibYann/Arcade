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
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

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

    typedef struct s_score_data {
        size_t score;
        std::string name;
    } t_score_data;

    class Core
    {
    public:
        Core();
        ~Core();

        void runGame(std::vector<bool> inputs);
        void runMenu(std::vector<bool> inputs);
        void loadGame(const std::string &gameLibNamegame);
        void unloadGame(void);
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
        std::vector<t_score_data> loadGameScore(const std::string &gameName);
        void saveGameScore(const std::vector<Arcade::t_score_data> &scoreList, const std::string &gameName);
        void addGameScore(std::vector<Arcade::t_score_data> &scoreList, size_t score, const std::string &gameName);
        t_tile_data getTileData(int id);

    private:
        void getClickedButton(std::vector<bool> curr, std::vector<bool> prev);
        bool checkScoreFileStatus(std::fstream &scoreFile, const std::string &gameName);
        void displayScore(int x, int y);
        void displayGames(int x, int y);
        void pickName();
        std::vector<t_tile_config> _tileCnf;
        std::vector<t_tile_data> _tileData;

        std::size_t _pickedGraphics = 0;
        std::size_t _selected = 0;
        std::size_t _prevSelected = 0;
        std::string _graphicPath = "./lib/";
        std::string _gamePath = "./lib/";
        std::vector<std::string> _gameList;
        std::vector<std::string> _graphicList;
        std::shared_ptr<IGame> _game = nullptr;
        std::shared_ptr<IGraphics> _graphic = nullptr;
        Arcade::DLLoader _gameLib;
        Arcade::DLLoader _graphicLib;

        bool _entry;
        std::string _playerName;
        std::vector<int> _gameSize;
        std::vector<int> _gamePadding;

        std::vector<bool> _prevButtons;
        std::vector<bool> _buttonsClicked;


        // Score
        std::string _scoreFileName;
        std::string _scoreDir = "score/";
        std::vector<Arcade::t_score_data> _score;
        bool _scoreLoaded = false;
    };
}
