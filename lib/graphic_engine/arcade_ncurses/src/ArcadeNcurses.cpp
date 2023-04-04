/*
** EPITECH PROJECT, 2023
** Ncurse
** File description:
** The file contains all the methods of the class ncurse.
*/

#include "ArcadeNcurses.hpp"
#include <signal.h>

ArcadeNcurses::ArcadeNcurses()
{
    signal(SIGINT, SIG_IGN);
    initscr();
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
    _win = newwin(NCURSE_MAXY, NCURSE_MAXX, (NCURSE_MAXY - TILES_Y) / 2, (NCURSE_MAXX - TILES_X * 2) / 2);
    cbreak();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
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
    keys.insert({10, Arcade::HOME_MENU});
    keys.insert({27, Arcade::EXIT});
    refresh();
}

ArcadeNcurses::~ArcadeNcurses()
{
    endwin();
}

void ArcadeNcurses::drawText(const std::string &text, int x, int y, int color)
{
    mvwprintw(_win, y, x * 2, "%s", text.c_str());
    wattron(_win, COLOR_PAIR(color));
    mvwprintw(_win, y, x * 2, "%s", text.c_str());
    wattroff(_win, COLOR_PAIR(color));
}

void ArcadeNcurses::drawTile(int x, int y, uint32_t color)
{
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

    buttons.resize(Arcade::TOTAL_INPUT);
    for (size_t i = 0; i < buttons.size(); i++)
        buttons[i] = false;
    if ((pressed = keys.find(getch())) != keys.end())
        buttons[pressed->second] = true;
}

char ArcadeNcurses::getKeyboard(void)
{
    int c = getch();

    if (isprint(c) || c == 127)
        return (c);
    return (0);
}
