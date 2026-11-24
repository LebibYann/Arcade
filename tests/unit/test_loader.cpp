/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Tests of the dynamic library loader
*/

#include "../Test.hpp"
#include "DLLoader.hpp"

#include <dlfcn.h>
#include <filesystem>

#define SNAKE "./lib/arcade_snake.so"
#define NCURSES "./lib/arcade_ncurses.so"

TEST(loader_recognizes_library_types)
{
    Arcade::DLLoader loader;

    CHECK_EQ(loader.checkLibIntegrity(SNAKE), 1);
    CHECK_EQ(loader.checkLibIntegrity("./lib/arcade_nibbler.so"), 1);
    CHECK_EQ(loader.checkLibIntegrity(NCURSES), 2);
}

TEST(loader_rejects_missing_and_foreign_libraries)
{
    Arcade::DLLoader loader;

    CHECK_EQ(loader.checkLibIntegrity("./lib/does_not_exist.so"), 0);
    // A real shared library without the arcade entry points
    CHECK_EQ(loader.checkLibIntegrity("libm.so.6"), 0);
}

TEST(loader_throws_on_missing_library)
{
    Arcade::DLLoader loader;
    bool thrown = false;

    try {
        loader.Load("./lib/does_not_exist.so");
    } catch (const Arcade::DLLoader::BadLibrary &error) {
        thrown = std::string(error.what()).find("does_not_exist") != std::string::npos;
    }
    CHECK(thrown);
}

TEST(loader_throws_on_missing_symbol)
{
    Arcade::DLLoader loader(SNAKE);
    bool thrown = false;

    try {
        loader.getInstance<Arcade::IGame>("no_such_symbol");
    } catch (const Arcade::DLLoader::BadLibrary &) {
        thrown = true;
    }
    CHECK(thrown);
}

TEST(loader_creates_instances)
{
    Arcade::DLLoader loader(SNAKE);
    std::shared_ptr<Arcade::IGame> game = loader.getInstance<Arcade::IGame>("entry_point");

    CHECK(game != nullptr);
    CHECK_EQ(game->getScore(), (std::size_t)0);
    game.reset();
}

// Libraries must really leave memory when unloaded, so that a rebuilt
// library is picked up and no state survives a reload
TEST(loader_really_unloads_libraries)
{
    std::string path = std::filesystem::absolute(SNAKE).string();
    Arcade::DLLoader loader(path);
    std::shared_ptr<Arcade::IGame> game = loader.getInstance<Arcade::IGame>("entry_point");
    void *handle;

    handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOLOAD);
    CHECK(handle != nullptr);
    dlclose(handle);
    game.reset();
    loader.unLoad();
    handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_NOLOAD);
    if (handle != nullptr)
        dlclose(handle);
    CHECK(handle == nullptr);
}
