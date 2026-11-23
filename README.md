# Arcade: a gaming platform with hot-swappable libraries

Arcade is a small game console written in C++. Games and graphics back ends are both **shared libraries** (`.so`) loaded at runtime with `dlopen`, so you can switch the renderer (terminal, ncurses, SDL2) or the game while playing, without restarting the program.

<!-- TODO: add a screenshot or GIF here (e.g. Snake in ncurses, then SDL2) -->

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-1E2A55?style=for-the-badge)
![Doxygen](https://img.shields.io/badge/Doxygen-2C4AA8?style=for-the-badge)

## Features

- Games: **Snake** and **Nibbler**, with their maps in [`game_files/`](game_files)
- Graphics back ends: **ncurses**, **SDL2** and **libcaca**
- Switch game or renderer at runtime; each library only depends on the shared interfaces

## Architecture

The core never knows which game or renderer it runs. It only talks to two interfaces in [`global/`](global):

- `IGame`: game logic, which reads player instructions and produces what to draw
- `IGraphics`: rendering and input for one back end

`DLLoader` opens a `.so`, finds its extern "C" entry point and returns an instance of the interface. Adding a new game or renderer means writing one library, with no change to the core.

```
arcade_soft/          core program (Core, DLLoader, Main)
global/               shared interfaces (IGame, IGraphics, Instruction)
lib/games/            snake, nibbler
lib/graphic_engine/   arcade_ncurses, arcade_sdl2, arcade_libcaca
doc/                  Doxygen documentation (HTML and LaTeX)
```

## Build and run

Requires a Linux system with `g++`, `make`, ncurses, SDL2 and libcaca.

```bash
make
./arcade ./lib/arcade_ncurses.so
```

The argument is the graphics library to start with.

## Documentation

The API documentation is generated with Doxygen (`Doxyfile`) and committed in [`doc/`](doc): open `doc/html/index.html` in a browser.

## Team

Team project of 3 at Epitech (2023):

- [Yann Lebib](https://github.com/LebibYann)
- Valentin Maurel
- Enzo Pfeiffer

<!-- TODO (Yann): add a "My contribution" section with the parts you wrote -->

See [CONTRIBUTING.md](CONTRIBUTING.md) for the commit convention.
