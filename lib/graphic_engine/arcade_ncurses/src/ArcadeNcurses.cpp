/*
** EPITECH PROJECT, 2023
** Ncurse
** File description:
** The file contains all the methods of the class ncurse.
*/

#include "ArcadeNcurses.hpp"

#include <stdexcept>

ArcadeNcurses::ArcadeNcurses()
{
    _oldSigint = signal(SIGINT, SIG_IGN);
    // newterm instead of initscr: initscr only sets the terminal up once per
    // process, and the ncurses state (kept in libtinfo) outlives this library
    // when the core unloads it and loads it again later.
    _screen = newterm(nullptr, stdout, stdin);
    if (_screen == nullptr) {
        signal(SIGINT, _oldSigint);
        throw std::runtime_error("arcade_ncurses: unable to set up the terminal");
    }
    set_term(_screen);
    noecho();
    start_color();
    init_pair(Arcade::BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(Arcade::RED, COLOR_WHITE, COLOR_RED);
    init_pair(Arcade::GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(Arcade::YELLOW, COLOR_WHITE, COLOR_YELLOW);
    init_pair(Arcade::BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(Arcade::MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(Arcade::CYAN, COLOR_WHITE, COLOR_CYAN);
    init_pair(Arcade::WHITE, COLOR_BLACK, COLOR_WHITE);
    // Center the game area in the terminal, cut to the terminal size if it is
    // smaller (newwin fails when the window does not fit)
    _win = newwin(std::min(TILES_Y, LINES), std::min(TILES_X * 2, COLS),
        std::max(0, (LINES - TILES_Y) / 2), std::max(0, (COLS - TILES_X * 2) / 2));
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    // Let ncurses decode arrow keys, and only wait 25 ms to tell a lone
    // Escape from the start of an arrow key sequence
    keypad(stdscr, TRUE);
    set_escdelay(25);
    // Some terminals send the normal mode arrow sequences anyway
    define_key("\033[A", KEY_UP);
    define_key("\033[B", KEY_DOWN);
    define_key("\033[C", KEY_RIGHT);
    define_key("\033[D", KEY_LEFT);
    keys.insert({'z', Arcade::UP_ARROW});
    keys.insert({'s', Arcade::DOWN_ARROW});
    keys.insert({'q', Arcade::LEFT_ARROW});
    keys.insert({'d', Arcade::RIGHT_ARROW});
    keys.insert({'i', Arcade::BUTTON1});
    keys.insert({'l', Arcade::BUTTON2});
    keys.insert({'k', Arcade::BUTTON3});
    keys.insert({'j', Arcade::BUTTON4});
    keys.insert({'r', Arcade::RESTART});
    keys.insert({KEY_LEFT, Arcade::PREV_GAME});
    keys.insert({KEY_RIGHT, Arcade::NEXT_GAME});
    keys.insert({KEY_UP, Arcade::NEXT_LIB});
    keys.insert({KEY_DOWN, Arcade::PREV_LIB});
    keys.insert({27, Arcade::EXIT});
    keys.insert({10, Arcade::HOME_MENU});
    refresh();
}

ArcadeNcurses::~ArcadeNcurses()
{
    if (_win != nullptr)
        delwin(_win);
    endwin();
    delscreen(_screen);
    signal(SIGINT, _oldSigint);
}

// IGraphics: a color outside ArcadeColor must be ignored, not crash
static bool isArcadeColor(long color)
{
    return (color >= Arcade::BLACK && color <= Arcade::WHITE);
}

void ArcadeNcurses::drawText(const std::string &text, int x, int y, int color)
{
    if (!isArcadeColor(color))
        color = Arcade::WHITE;
    wattron(_win, COLOR_PAIR(color));
    mvwprintw(_win, y, x * 2, "%s", text.c_str());
    wattroff(_win, COLOR_PAIR(color));
}

void ArcadeNcurses::drawTile(int x, int y, uint32_t color)
{
    if (!isArcadeColor(color))
        return;
    wattron(_win, COLOR_PAIR(color));
    mvwprintw(_win, y, x * 2, "  ");
    wattroff(_win, COLOR_PAIR(color));
}

void ArcadeNcurses::display(void)
{
    wrefresh(_win);
}

void ArcadeNcurses::fill(uint32_t color)
{
    if (!isArcadeColor(color))
        return;
    wattron(_win, COLOR_PAIR(color));
    for (size_t i = 0; i < TILES_Y; i++)
        for (size_t j = 0; j < TILES_X * 2; j += 2)
            mvwprintw(_win, i, j, "  ");
    wattroff(_win, COLOR_PAIR(color));
}

void ArcadeNcurses::getMousePos(std::vector<int> &coords)
{
    coords.resize(2);
}

void ArcadeNcurses::getMouseButton(std::vector<bool> &buttons)
{
    buttons.resize(3);
}

void ArcadeNcurses::getButtons(std::vector<bool> &buttons)
{
    std::map<int, int>::iterator pressed;
    int ch;

    buttons.resize(Arcade::TOTAL_INPUT);
    std::fill(buttons.begin(), buttons.end(), false);
    _typed.clear();
    while ((ch = getch()) != ERR) {
        if ((pressed = keys.find(ch)) != keys.end())
            buttons[pressed->second] = true;
        if (ch == KEY_BACKSPACE || ch == 8)
            ch = 127;
        if ((ch < 128 && isalpha(ch)) || ch == 127 || ch == '\n' || ch == ' ')
            _typed.push_back(ch);
    }
}

char ArcadeNcurses::getKeyboard(void)
{
    char c;

    if (_typed.empty())
        return (0);
    c = _typed.front();
    _typed.pop_front();
    return (c);
}
