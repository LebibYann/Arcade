/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Tests of the core: library discovery and scores
*/

#include "../Test.hpp"
#include "Core.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

/**
 ** @brief Temporary arcade root whose lib/ points to the built libraries,
 ** so that score files are written there and not in the project.
 */
class TempRoot {
public:
    explicit TempRoot(bool withLibs = true)
    {
        std::string pattern = (fs::temp_directory_path() / "arcade_tests_XXXXXX").string();

        if (mkdtemp(pattern.data()) == nullptr)
            throw test::Failure{"cannot create a temporary directory"};
        _path = pattern;
        if (withLibs)
            fs::create_directory_symlink(fs::absolute("lib"), _path / "lib");
    }
    ~TempRoot() { fs::remove_all(_path); }
    std::string str(void) const { return (_path.string()); }

private:
    fs::path _path;
};

TEST(core_lists_libraries_by_type_and_sorted)
{
    TempRoot root;
    Arcade::Core core(root.str());
    std::vector<std::string> games = {"arcade_nibbler.so", "arcade_snake.so"};
    const std::vector<std::string> &graphics = core.getGraphicList();

    CHECK(core.getGameList() == games);
    CHECK(!graphics.empty());
    CHECK(std::is_sorted(graphics.begin(), graphics.end()));
    CHECK(std::find(graphics.begin(), graphics.end(), "arcade_ncurses.so") != graphics.end());
}

TEST(core_finds_libraries_next_to_the_executable)
{
    Arcade::Core core;

    CHECK(fs::path(core.getLibDir()).is_absolute());
    CHECK(fs::equivalent(core.getLibDir(), fs::absolute("lib")));
}

TEST(core_survives_a_missing_lib_directory)
{
    TempRoot root(false);
    Arcade::Core core(root.str());

    CHECK(core.getGameList().empty());
    CHECK(core.getGraphicList().empty());
}

TEST(scores_are_sorted_and_kept_to_ten)
{
    TempRoot root;
    Arcade::Core core(root.str());
    std::vector<Arcade::t_score_data> scores;

    core.addGameScore(scores, 50, "B");
    core.addGameScore(scores, 100, "A");
    core.addGameScore(scores, 10, "C");
    CHECK_EQ(scores[0].name, std::string("A"));
    CHECK_EQ(scores[1].name, std::string("B"));
    CHECK_EQ(scores[2].name, std::string("C"));
    for (int i = 0; i < 20; ++i)
        core.addGameScore(scores, 20 + i, "X");
    CHECK_EQ(scores.size(), (std::size_t)10);
    CHECK_EQ(scores[0].score, (std::size_t)100);
}

TEST(scores_are_saved_and_loaded_back)
{
    TempRoot root;
    Arcade::Core core(root.str());
    std::vector<Arcade::t_score_data> scores;

    core.addGameScore(scores, 42, "YANN");
    core.addGameScore(scores, 7, "LENNY");
    core.saveGameScore(scores, "arcade_snake.so");
    scores = core.loadGameScore("arcade_snake.so");
    CHECK_EQ(scores.size(), (std::size_t)2);
    CHECK_EQ(scores[0].score, (std::size_t)42);
    CHECK_EQ(scores[0].name, std::string("YANN"));
    CHECK_EQ(scores[1].name, std::string("LENNY"));
}

TEST(corrupted_score_files_are_ignored)
{
    TempRoot root;
    Arcade::Core core(root.str());

    fs::create_directories(core.getScoreDir());
    std::ofstream(core.getScoreDir() + "huge.score") << "999999999999\n5\nBOB\n";
    std::ofstream(core.getScoreDir() + "garbage.score") << "not a score file\n";
    CHECK_EQ(core.loadGameScore("huge").size(), (std::size_t)1);
    CHECK(core.loadGameScore("garbage").empty());
    CHECK(core.loadGameScore("missing").empty());
}

TEST(core_loads_games_by_index)
{
    TempRoot root;
    Arcade::Core core(root.str());

    core.loadGame(core.getGameList().size());
    core.loadGame(0);
    core.loadGame(1);
    core.unloadGame();
    // Unloading a game saves its score board
    CHECK(fs::exists(core.getScoreDir() + "arcade_snake.so.score"));
    CHECK(fs::exists(core.getScoreDir() + "arcade_nibbler.so.score"));
}
