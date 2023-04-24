/*
** EPITECH PROJECT, 2023
** Core
** File description:
** The file contains all the methods of the class Core
*/

#include "Core.hpp"

Arcade::Core::Core() : _selected(0), _entry(false), _playerName("")
{
    this->getAvailableLib();
    this->_score.resize(0);
}

Arcade::Core::~Core()
{
    this->unloadGame();
    _graphic.reset();
    _graphicLib.unLoad();
}

void Arcade::Core::unloadGame(void)
{
    if (this->_game == nullptr)
        return;
    if (this->_game->getScore() != 0)
        this->addGameScore(this->_score, this->_game->getScore(), this->_playerName);
    this->saveGameScore(this->_score, this->_gameList[this->_selected]);
    this->_game.reset();
    this->_game = nullptr;
    this->_gameLib.unLoad();
}

void Arcade::Core::loadGame(const std::string &gameLibName)
{
    if (this->_game != nullptr)
        this->unloadGame();
    // std::cout << "Loading game lib: " << gameLibName << std::endl;
    this->_gameLib.Load(gameLibName);
    // std::cout << "Game lib [" << gameLibName << "] load OK" << std::endl;
    this->_score = this->loadGameScore(this->_gameList[this->_selected]);
    this->_game = this->_gameLib.getInstance<Arcade::IGame>("entry_point");
    this->_tileCnf = this->_game->getTilesConfig();
    // std::cout << "Game init [" << gameLibName << "] OK" << std::endl;
    this->initTileData();
    _gameSize = _game->getWindowSize();
    _gamePadding.resize(2);
    _gamePadding[0] = (TILES_X / 2 - _gameSize[0] / 2);
    _gamePadding[1] = (TILES_Y / 2 - _gameSize[1] / 2);
}

void Arcade::Core::loadGraphics(const std::string &graphicLibName)
{
    this->_graphic.reset();
    this->_graphicLib.unLoad();
    // std::cout << "Loading display lib: " << graphicLibName << std::endl;
    this->_graphicLib.Load(graphicLibName);
    // std::cout << "Display lib [" << graphicLibName << "] load OK" << std::endl;
    this->_graphic = this->_graphicLib.getInstance<Arcade::IGraphics>("entry_point");
    // std::cout << "Display init [" << graphicLibName << "] OK" << std::endl;
}

void Arcade::Core::getSOFiles(std::vector<std::string> &list, const std::string &path)
{
    list.clear();
    std::filesystem::path fpath = path;
    std::string tmp;
    std::string libName;

    for (const auto& entry : std::filesystem::directory_iterator(fpath)) {
        tmp = entry.path();
        if (strcmp(".so", &tmp.c_str()[tmp.length() - 3]) == 0) {
            libName = strrchr(tmp.c_str(), '/');
            if (libName.c_str() == nullptr)
                list.push_back(tmp);
            else {
                list.push_back(&libName.c_str()[1]);
            }
        }
    }
}

void Arcade::Core::getAvailableLib(void)
{
    Arcade::DLLoader libChecker;
    std::vector<std::string> libs;

    this->getSOFiles(libs, "./lib/");
    for (size_t i = 0; i < libs.size(); ++i) {
        switch (libChecker.checkLibIntegrity("./lib/" + libs[i])) {
            case 1:
                this->_gameList.push_back(libs[i]);
                break;
            case 2:
                this->_graphicList.push_back(libs[i]);
                break;

        }
    }
}

void Arcade::Core::initTileData(void)
{
    t_tile_data tmpData;

    this->_tileData.clear();
    for (size_t i = 0; i < this->_tileCnf.size(); ++i) {
        tmpData.id = this->_tileCnf[i].id;
        tmpData.color = this->_tileCnf[i].color;
        tmpData.img = nullptr;
        // if (this->_tileCnf[i].path.c_str() != nullptr)
        //     tmpData.img = this->_graphic->loadImage(this->_tileCnf[i].path);
        this->_tileData.push_back(tmpData);
    }
}

Arcade::t_tile_data Arcade::Core::getTileData(int id)
{
    Arcade::t_tile_data errorTile = {-1, false, nullptr, -1};

    for (size_t i = 0; i < this->_tileData.size(); ++i) {
        if (this->_tileData[i].id == id)
            return (this->_tileData[i]);
    }
    return (errorTile);
}

void Arcade::Core::runGame(std::vector<bool> buttons)
{
    std::vector<std::shared_ptr<IInstruction>> inst;

    if (this->_buttonsClicked[Arcade::RESTART])
        this->loadGame(_gamePath + this->_gameList[this->_selected]);
    if (this->_buttonsClicked[Arcade::NEXT_GAME]) {
        this->unloadGame();
        if (this->_selected < _gameList.size() - 1)
            this->_selected++;
        else
            this->_selected = 0;
        loadGame(_gamePath + _gameList[this->_selected]);
    }
    if (this->_buttonsClicked[Arcade::PREV_GAME]) {
        this->unloadGame();
        if (this->_selected != 0)
            this->_selected--;
        else
            this->_selected = _gameList.size() - 1;
        loadGame(_gamePath + _gameList[this->_selected]);
    }
    _graphic->fill(BLACK);
    inst = this->_game->computeFrame(buttons);
    this->interpretInstruction(inst);
    _graphic->drawText(_playerName + "'s score: " + std::to_string(_game->getScore()) , _gamePadding[0], _gamePadding[1] - 1, WHITE);
}

void Arcade::Core::displayScore(int x, int y)
{
    std::string tmp = "SCORE: ";

    if (this->_prevSelected != this->_selected)
        this->_scoreLoaded = false;

    if (this->_selected < this->_gameList.size()) {
        tmp.append(this->_gameList[this->_selected]);
        if (!this->_scoreLoaded) {
            this->_score = loadGameScore(this->_gameList[this->_selected]);
            this->_scoreLoaded = true;
        }
        this->_graphic->drawText(tmp, x, y, RED);
        for (size_t i = 0; i < this->_score.size(); i++) {
            tmp = std::to_string(this->_score[i].score) + " " + this->_score[i].name;
            this->_graphic->drawText(tmp, x + 1, i + y + 1, WHITE);
        }
    }
}

void Arcade::Core::displayGames(int x, int y)
{
    int offset = 0;
    int colorPick;

    this->_graphic->drawText("GAMES:", x, y, RED);
    for (size_t i = 0; i < _gameList.size(); i++) {
        offset = (i == this->_selected && i < _gameList.size());
        colorPick = (i == this->_selected && i < _gameList.size()) ? WHITE : BLACK;
        this->_graphic->drawText(_gameList[i], x + offset, i + y + 1, colorPick);
    }
}

void Arcade::Core::pickName()
{
    char c;

    c = _graphic->getKeyboard();
    if (c == 0);
    else if (c == '\n' || c == ' ')
        _entry = false;
    else if (c != 127 && _playerName.size() < 8)
        _playerName += toupper(c);
    else if (_playerName.compare("") != 0 && c == 127)
        _playerName.pop_back();
}

void Arcade::Core::runMenu(std::vector<bool> buttons)
{
    int offset = 0;
    int colorPick = WHITE;
    (void)colorPick;
    size_t selectGraph = this->_selected - _gameList.size();
    (void)buttons;

    this->_graphic->fill(ArcadeColor::GREEN);

    this->displayScore(20, 0);
    this->displayGames(0, 0);

    _graphic->drawText("DISPLAY:", 0, _gameList.size() + 2, RED);
    for (size_t i = 0; i < _graphicList.size(); i++) {
        offset = 0;
        if (this->_selected >= _gameList.size() && selectGraph == i) {
            offset = 1;
            colorPick = WHITE;
        }
        else if (this->_pickedGraphics != 0 && i == this->_pickedGraphics - 1)
            colorPick = BLUE;
        else
            colorPick = BLACK;
        _graphic->drawText(_graphicList[i], offset, i + _gameList.size() + 3, colorPick);
    }
    if (this->_selected == this->_gameList.size() + this->_graphicList.size())
        colorPick = WHITE;
    else
        colorPick = BLACK;
    _graphic->drawText("Name: " + _playerName, 0, 15, colorPick);
    if (_entry){
        return (pickName());
    }
    this->_prevSelected = this->_selected;
    if (this->_buttonsClicked[Arcade::DOWN_ARROW] &&
        this->_selected < this->_gameList.size() + this->_graphicList.size())
        this->_selected++;
    if (this->_buttonsClicked[Arcade::UP_ARROW] && this->_selected != 0)
        this->_selected--;
    if (this->_buttonsClicked[Arcade::RIGHT_ARROW]){
        if (this->_selected == this->_gameList.size() + this->_graphicList.size())
            _entry = true;
        else if (this->_selected >= this->_gameList.size()) {
            this->_pickedGraphics = selectGraph + 1;
            loadGraphics(_graphicPath + _graphicList[this->_selected - _gameList.size()]);
        } else if (_playerName.compare("") != 0){
            loadGame(_gamePath + _gameList[this->_selected]);
        }
    }
}

void Arcade::Core::run(void)
{
    std::vector<bool> buttons(TOTAL_INPUT);

    this->_graphic->getButtons(buttons);
    this->_prevButtons.resize(buttons.size());
    this->_buttonsClicked.resize(buttons.size());
    do {
        std::fill(buttons.begin(), buttons.end(), false);
        this->_graphic->getButtons(buttons);
        if (buttons[Arcade::HOME_MENU]) {
            this->unloadGame();
        }
        if (_game != nullptr)
            runGame(buttons);
        else
            runMenu(buttons);
        if (buttons[Arcade::PREV_LIB] && _pickedGraphics < _graphicList.size()) {
            loadGraphics(_graphicPath + _graphicList[_pickedGraphics]);
            _pickedGraphics++;
        }
        if (buttons[Arcade::NEXT_LIB] && _pickedGraphics > 1) {
            loadGraphics(_graphicPath + _graphicList[_pickedGraphics - 2]);
            _pickedGraphics--;
        }
        this->_graphic->display();
        this->getClickedButton(buttons, this->_prevButtons);
        this->_prevButtons = buttons;
    } while (!buttons[Arcade::EXIT]);
}

void Arcade::Core::interpretInstruction(const std::vector<std::shared_ptr<IInstruction>> &instr)
{
    for (size_t i = 0; i < instr.size(); ++i) {
        switch (instr[i]->getId()) {
            case INST_FILL:
                this->fill(instr[i]);
                break;
            case INST_DRAW_TILE:
                this->drawTile(instr[i]);
                break;
            case INST_DRAW_TEXT:
                this->drawText(instr[i]);
                break;
        }
    }
}

void Arcade::Core::fill(const std::shared_ptr<IInstruction> &instr)
{
    InstFill *cast_instr = dynamic_cast<InstFill*>(instr.get());

    this->_graphic->fill(cast_instr->get_color());
}

void Arcade::Core::drawTile(const std::shared_ptr<IInstruction> &instr)
{
    InstDrawTile *cast_instr = dynamic_cast<InstDrawTile*>(instr.get());
    Arcade::t_tile_data tileData = this->getTileData(cast_instr->get_texture());

    this->_graphic->drawTile(cast_instr->get_x() + _gamePadding[0], cast_instr->get_y() + _gamePadding[1], tileData.color);
}

void Arcade::Core::drawText(const std::shared_ptr<IInstruction> &instr)
{
    InstDrawText *cast_instr = dynamic_cast<InstDrawText*>(instr.get());

    this->_graphic->drawText(cast_instr->get_text(), cast_instr->get_x() + _gamePadding[0], cast_instr->get_y() + _gamePadding[1], cast_instr->get_color());
}

void Arcade::Core::getClickedButton(std::vector<bool> curr, std::vector<bool> prev)
{
    this->_buttonsClicked.resize(curr.size());
    for (size_t i = 0; i < curr.size(); ++i)
        this->_buttonsClicked[i] = (curr[i] && !prev[i]);
}

std::vector<Arcade::t_score_data> Arcade::Core::loadGameScore(const std::string &gameName)
{
    size_t nbr_score;
    t_score_data scoreData;
    std::fstream scoreFile;
    std::vector<t_score_data> scores;

    scoreFile.open(this->_scoreDir + gameName + ".score", std::ios::in);
    if (!scoreFile) {
        // std::cout << "No score data found for the game called: " << gameName << std::endl;
        return (scores);
    }
    scoreFile >> nbr_score;
    for (size_t i = 0; i < nbr_score; ++i) {
        scoreFile >> scoreData.score;
        scoreFile >> scoreData.name;
        scores.push_back(scoreData);
    }
    scoreFile.close();
    return(scores);
}

void Arcade::Core::addGameScore(std::vector<Arcade::t_score_data> &scoreList, size_t score, const std::string &playerName)
{
    bool scorePushed = false;
    t_score_data scoreData = {score, playerName};
    std::vector<Arcade::t_score_data>::iterator it;

    it = scoreList.begin();
    for (; it != scoreList.end(); ++it) {
        if (score > it->score) {
            scoreList.insert(it, scoreData);
            scorePushed = true;
            break;
        }
    }
    if (!scorePushed)
        scoreList.push_back(scoreData);
    if (scoreList.size() > 10)
        scoreList.resize(10);
}

bool Arcade::Core::checkScoreFileStatus(std::fstream &scoreFile, const std::string &gameName)
{
    std::string fullPath = this->_scoreDir + gameName;

    if (access(this->_scoreDir.c_str(), F_OK) != 0)
        std::filesystem::create_directories(this->_scoreDir);
    scoreFile.open(this->_scoreDir + gameName + ".score", std::ios::out);
    return ((!scoreFile) ? false : true);
}

void Arcade::Core::saveGameScore(const std::vector<Arcade::t_score_data> &scoreList, const std::string &gameName)
{
    std::fstream scoreFile;

    if (!this->checkScoreFileStatus(scoreFile, gameName)) {
        // std::cerr << "Saving score of the game called: " <<
        //     gameName << " has failed" << std::endl;
        return;
    }
    scoreFile << scoreList.size() << "\n";
    for (size_t i = 0; i < scoreList.size(); ++i) {
        scoreFile << scoreList[i].score << "\n";
        scoreFile << scoreList[i].name.c_str() << "\n";
    }
    scoreFile.close();
}
