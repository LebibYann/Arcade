/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Tests of loading and switching graphics libraries.
** They need a terminal (make tests_run gives them one with script) and
** run without a screen: SDL2 uses its dummy driver and libcaca its
** ncurses driver.
*/

#include "../Test.hpp"
#include "DLLoader.hpp"

#include <dlfcn.h>
#include <filesystem>
#include <fstream>
#include <random>

#define NCURSES "./lib/arcade_ncurses.so"
#define SDL2 "./lib/arcade_sdl2.so"
#define LIBCACA "./lib/arcade_libcaca.so"

static void requireLibs(const std::vector<std::string> &libs)
{
    for (const std::string &lib : libs)
        if (!std::filesystem::exists(lib))
            SKIP(lib + " is not built");
}

/**
 ** @brief Load each library in turn the way the core switches them, and
 ** draw a few frames with each.
 */
static void switchThrough(const std::vector<std::string> &libs)
{
    Arcade::DLLoader loader;
    std::shared_ptr<Arcade::IGraphics> graphics;
    std::vector<bool> buttons(Arcade::TOTAL_INPUT);

    requireLibs(libs);
    for (const std::string &lib : libs) {
        graphics.reset();
        loader.unLoad();
        loader.Load(lib);
        graphics = loader.getInstance<Arcade::IGraphics>("entry_point");
        CHECK(graphics != nullptr);
        for (int frame = 0; frame < 3; ++frame) {
            graphics->getButtons(buttons);
            CHECK_EQ(buttons.size(), (std::size_t)Arcade::TOTAL_INPUT);
            graphics->fill(Arcade::GREEN);
            graphics->drawTile(1, 1, Arcade::RED);
            // Colors outside ArcadeColor must be ignored
            graphics->drawTile(2, 1, 1234);
            graphics->drawText("arcade", 2, 2, Arcade::WHITE);
            graphics->display();
        }
    }
    graphics.reset();
    loader.unLoad();
}

TEST(each_graphics_library_draws)
{
    for (const char *lib : {NCURSES, SDL2, LIBCACA})
        if (std::filesystem::exists(lib))
            switchThrough({lib});
}

TEST(each_graphics_library_reloads)
{
    for (const char *lib : {NCURSES, SDL2, LIBCACA})
        if (std::filesystem::exists(lib))
            switchThrough({lib, lib, lib});
}

// Regression: libcaca uses ncurses too, and loading arcade_ncurses after it
// reused a stale ncurses screen and crashed
TEST(ncurses_loads_after_libcaca)
{
    switchThrough({LIBCACA, NCURSES, LIBCACA, NCURSES});
}

TEST(random_switches_between_all_libraries)
{
    std::vector<std::string> all = {NCURSES, SDL2, LIBCACA};
    std::vector<std::string> sequence;
    std::mt19937 random(2023);

    for (int i = 0; i < 30; ++i)
        sequence.push_back(all[random() % all.size()]);
    switchThrough(sequence);
}

int main(int argc, char **argv)
{
    // The real SDL2 drivers keep libtinfo (the ncurses terminal library)
    // loaded for the whole run. Do the same here, since it is the
    // condition for the ncurses after libcaca crash.
    dlopen("libtinfo.so.6", RTLD_NOW | RTLD_GLOBAL);
    // The libraries draw in the terminal: write the results to a file
    if (argc > 1) {
        std::ofstream results(argv[1]);
        return (test::runAll(results));
    }
    return (test::runAll(std::cerr));
}
