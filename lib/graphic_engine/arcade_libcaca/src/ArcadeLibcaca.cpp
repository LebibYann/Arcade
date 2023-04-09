/*
** EPITECH PROJECT, 2023
** Libcaca
** File description:
** The file contains all the methods of the class ncurse.
*/

#include "ArcadeLibcaca.hpp"

ArcadeLibcaca::ArcadeLibcaca()
{
    _canva = caca_create_canvas(LIBCACA_MAXX, LIBCACA_MAXY);
    _display = caca_create_display(_canva);
    _keys.insert({'z', Arcade::UP_ARROW});
    _keys.insert({'s', Arcade::DOWN_ARROW});
    _keys.insert({'q', Arcade::LEFT_ARROW});
    _keys.insert({'d', Arcade::RIGHT_ARROW});
    _keys.insert({'i', Arcade::BUTTON1});
    _keys.insert({'l', Arcade::BUTTON2});
    _keys.insert({'k', Arcade::BUTTON3});
    _keys.insert({'j', Arcade::BUTTON4});
    _keys.insert({'r', Arcade::RESTART});
    _keys.insert({CACA_KEY_LEFT, Arcade::PREV_GAME});
    _keys.insert({CACA_KEY_RIGHT, Arcade::NEXT_GAME});
    _keys.insert({CACA_KEY_UP, Arcade::NEXT_LIB});
    _keys.insert({CACA_KEY_DOWN, Arcade::PREV_LIB});
    _keys.insert({CACA_KEY_RETURN, Arcade::HOME_MENU});
    _keys.insert({CACA_KEY_ESCAPE, Arcade::EXIT});
    _color.insert({Arcade::BLACK, {CACA_WHITE, CACA_BLACK}});
    _color.insert({Arcade::RED, {CACA_WHITE, CACA_RED}});
    _color.insert({Arcade::GREEN, {CACA_WHITE, CACA_GREEN}});
    _color.insert({Arcade::YELLOW, {CACA_WHITE, CACA_YELLOW}});
    _color.insert({Arcade::BLUE, {CACA_WHITE, CACA_BLUE}});
    _color.insert({Arcade::MAGENTA, {CACA_WHITE, CACA_MAGENTA}});
    _color.insert({Arcade::CYAN, {CACA_WHITE, CACA_CYAN}});
    _color.insert({Arcade::WHITE, {CACA_BLACK, CACA_WHITE}});
}

ArcadeLibcaca::~ArcadeLibcaca()
{
    caca_free_display(_display);
    caca_free_canvas(_canva);
}

void ArcadeLibcaca::drawText(const std::string &text, int x, int y, int color)
{
    std::map<int, std::pair<int, int>>::iterator found;

    if ((found = _color.find(color)) == _color.end())
        return;
    caca_set_color_ansi(_canva, found->second.first, found->second.second);
    caca_put_str(_canva, x * 2, y, text.c_str());
}

void ArcadeLibcaca::drawTile(int x, int y, uint32_t color)
{
    std::map<int, std::pair<int, int>>::iterator found;

    if ((found = _color.find(color)) == _color.end())
        return;
    caca_set_color_ansi(_canva, found->second.first, found->second.second);
    caca_put_str(_canva, x * 2, y, "  ");
    caca_put_str(_canva, x * 2, y * 1, "  ");
}

void ArcadeLibcaca::display(void)
{
    caca_refresh_display(_display);
}

void ArcadeLibcaca::fill(uint32_t color)
{
    std::map<int, std::pair<int, int>>::iterator found;

    if ((found = _color.find(color)) == _color.end())
        return;
    caca_set_color_ansi(_canva, found->second.first, found->second.second);
    for (size_t i = 0; i < TILES_Y * 2; i += 2)
        for (size_t j = 0; j < TILES_X * 4; j += 4)
        {
            caca_put_str(_canva, j, i, "    ");
            caca_put_str(_canva, j, i + 1, "    ");
        }
}

void ArcadeLibcaca::getMousePos(std::vector<int> &coords)
{
    coords.resize(2);
}

void ArcadeLibcaca::getMouseButton(std::vector<bool> &buttons)
{
    buttons.resize(3);
}

void ArcadeLibcaca::getButtons(std::vector<bool> &buttons)
{
    std::map<int, int>::iterator pressed;
    caca_event_t event;

    buttons.resize(Arcade::TOTAL_INPUT);
    for (size_t i = 0; i < buttons.size(); i++)
        buttons[i] = false;
    if (caca_get_event(_display, CACA_EVENT_KEY_PRESS, &event, 0) > 0)
    {
        int ch = caca_get_event_key_ch(&event);
        if ((pressed = _keys.find(ch)) != _keys.end())
            buttons[pressed->second] = true;
    }
}

char ArcadeLibcaca::getKeyboard(void)
{
    std::map<int, int>::iterator pressed;
    caca_event_t event;
    int ch;

    if (caca_get_event(_display, CACA_EVENT_KEY_PRESS, &event, 0) > 0)
    {
        ch = caca_get_event_key_ch(&event);
        if (ch == CACA_KEY_BACKSPACE)
            return (127);
        else if (isalpha(ch))
            return (ch);
        else if (ch == CACA_KEY_RETURN || ch == ' ')
            return ('\n');
    }
    return ('\0');
}
