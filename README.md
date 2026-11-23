# Arcade: a gaming platform with hot-swappable libraries

Arcade is a small game console written in C++. Games and graphics back ends are both **shared libraries** (`.so`) loaded at runtime with `dlopen`, so you can switch the renderer (terminal, ncurses, SDL2) or the game while playing, without restarting the program.

<!-- TODO: add a screenshot or GIF here (e.g. Snake in ncurses, then SDL2) -->

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-1E2A55?style=for-the-badge)
![Doxygen](https://img.shields.io/badge/Doxygen-2C4AA8?style=for-the-badge)

## Features

- Games: **Snake**, and **Nibbler** with three mazes and a timer
- Graphics back ends: **ncurses**, **SDL2** and **libcaca**
- Switch game or renderer at runtime; each library only depends on the shared interfaces
- Player name and a top 10 score board per game, saved in `score/`

## Architecture

The core never knows which game or renderer it runs. It only talks to two interfaces in [`global/`](global):

- `IGame`: game logic, which reads the pressed buttons and returns a list of drawing instructions
- `IGraphics`: rendering and input for one back end

`DLLoader` opens a `.so`, calls its extern "C" `entry_point` and takes ownership of the instance it returns. Adding a new game or renderer means writing one library, with no change to the core. The core runs the loop at 30 frames per second.

```
arcade_soft/          core program (Core, DLLoader, Main)
global/               shared interfaces (IGame, IGraphics, Instruction)
lib/common/           snake logic shared by Snake and Nibbler
tests/                unit and graphics tests
lib/games/            snake, nibbler
lib/graphic_engine/   arcade_ncurses, arcade_sdl2, arcade_libcaca
doc/                  Doxygen documentation (HTML and LaTeX)
```

## Build and run

Requires a Linux system with `g++` (C++17), `make`, ncurses, SDL2, SDL2_ttf and libcaca. On Debian or Ubuntu:

```bash
sudo apt install g++ make libncurses-dev libsdl2-dev libsdl2-ttf-dev libcaca-dev
make
./arcade arcade_sdl2.so
```

The argument is the graphics library to start with: a path to a `.so`, or the name of one in `lib/`. The arcade finds `lib/`, `assets/` and `score/` next to the executable, so it can be run from any directory. For ncurses, use a terminal of at least 128 x 36 characters to see the whole game area. If a back end's dependency is missing, `make` reports an error for that library but still builds the other ones.

| Key | Action |
|---|---|
| Z Q S D | Move (and navigate the menu) |
| D in the menu | Select: launch a game, load a renderer, edit the name |
| ← → | Previous / next game |
| ↑ ↓ | Next / previous graphics library |
| R | Restart the game |
| Enter | Back to the menu |
| Escape | Quit |

The keys follow an AZERTY layout. Enter a name before launching a game.

## Tests

```bash
make tests_run
```

This builds the project, then runs two test programs with no extra dependency:

- unit tests of the library loader, the score board and both games, played through the `IGame` interface
- graphics tests that load and switch the graphics libraries, including a regression test for a crash when ncurses was loaded after libcaca. They run in a terminal created by `script`, without a screen (SDL2 dummy driver, libcaca ncurses driver)

## Documentation

The API documentation is generated with Doxygen (`Doxyfile`) and committed in [`doc/`](doc): open `doc/html/index.html` in a browser.

## Team

Team project of 3 at Epitech (March to April 2023):

- [Yann Lebib](https://github.com/LebibYann): core, library loader, menu, ncurses and libcaca back ends
- [Lenny Vigeon](https://github.com/Linnchoeuh): instruction system, instruction interpreter, scores, SDL2 back end, documentation
- Jean-Pierre Janopoulos: Snake and Nibbler games

The shared interfaces in [`global/`](global) were agreed with the groups of Valentin Maurel and Enzo Pfeiffer, so that games and graphics libraries work across both projects.

## My contribution

The full commit history is kept in this repository. My part:

- **Dynamic library loader** (`DLLoader`): loading, reloading and unloading `.so` files, and moving from `unique_ptr` to `shared_ptr` instances so that a library can be swapped at runtime
- **First version of the core** and of the `IGame` / `IGraphics` interfaces
- **Menu**: game and graphics selection, switching the graphics library from the menu, player name entry in every back end, and centering the game in the window
- **Graphics back ends**: libcaca, and the first ncurses version
- **Build**: library directory layout and the Makefiles
- **Fixes**: death and restart in Snake, spawn and death animation in Nibbler

See [CONTRIBUTING.md](CONTRIBUTING.md) for the commit convention.
