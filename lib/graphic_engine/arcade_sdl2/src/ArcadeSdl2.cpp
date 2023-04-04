/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** ArcadeSdl2
*/

#include "ArcadeSdl2.hpp"

static std::string getTermFont(void)
{
    char buffer[128];
    std::string termFontPath = "";
    std::string termFont = std::getenv("TERM");
    std::string command = "fc-match --format=%{file} ";

    command.append(termFont);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
        return (termFontPath);
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            termFontPath += buffer;
    }
    pclose(pipe);
    return (termFontPath);
}

ArcadeSdl2::ArcadeSdl2()
{
    std::string termFontPath = getTermFont();


    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    this->_font = nullptr;
    if (termFontPath.c_str() != nullptr)
        this->loadFont(termFontPath);

    this->_arcadeButtons.resize(Arcade::TOTAL_INPUT);
    std::fill(this->_arcadeButtons.begin(), this->_arcadeButtons.end(), false);

    this->_keyId.resize(Arcade::TOTAL_INPUT);
    std::fill(this->_keyId.begin(), this->_keyId.end(), 0);
    this->_keyId[Arcade::UP_ARROW] = SDLK_z;
    this->_keyId[Arcade::DOWN_ARROW] = SDLK_s;
    this->_keyId[Arcade::LEFT_ARROW] = SDLK_q;
    this->_keyId[Arcade::RIGHT_ARROW] = SDLK_d;
    this->_keyId[Arcade::BUTTON1] = SDLK_i;
    this->_keyId[Arcade::BUTTON2] = SDLK_j;
    this->_keyId[Arcade::BUTTON3] = SDLK_k;
    this->_keyId[Arcade::BUTTON4] = SDLK_l;
    this->_keyId[Arcade::PREV_GAME] = SDLK_LEFT;
    this->_keyId[Arcade::NEXT_GAME] = SDLK_RIGHT;
    this->_keyId[Arcade::PREV_LIB] = SDLK_DOWN;
    this->_keyId[Arcade::NEXT_LIB] = SDLK_UP;
    this->_keyId[Arcade::RESTART] = SDLK_r;
    this->_keyId[Arcade::HOME_MENU] = SDLK_RETURN;
    this->_keyId[Arcade::EXIT] = SDLK_ESCAPE;

    this->_colors.resize(SDL_TOTALCOLOR);
    this->_colors[Arcade::BLACK].full = SDL_SETCOLOR(0, 0, 0, 255);
    this->_colors[Arcade::RED].full = SDL_SETCOLOR(255, 0, 0, 255);
    this->_colors[Arcade::GREEN].full = SDL_SETCOLOR(0, 255, 0, 255);
    this->_colors[Arcade::YELLOW].full = SDL_SETCOLOR(255, 255, 0, 255);
    this->_colors[Arcade::BLUE].full = SDL_SETCOLOR(0, 0, 255, 255);
    this->_colors[Arcade::MAGENTA].full = SDL_SETCOLOR(255, 0, 255, 255);
    this->_colors[Arcade::CYAN].full = SDL_SETCOLOR(0, 255, 255, 255);
    this->_colors[Arcade::WHITE].full = SDL_SETCOLOR(255, 255, 255, 255);

    this->openWindow(64, 36);
}

ArcadeSdl2::~ArcadeSdl2()
{
    this->closeWindow();
    this->unloadFont();
    TTF_Quit();
    SDL_Quit();
}

void ArcadeSdl2::openWindow(int width, int height)
{
    if (this->_window == nullptr)
        this->_window = SDL_CreateWindow("Arcade SDL2",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        width * this->_tileSize, height * this->_tileSize, 0);
    // if (this->_surface == nullptr)
    //     this->_surface = SDL_GetWindowSurface(this->_window);
    if (this->_render == nullptr)
        this->_render = SDL_CreateRenderer(this->_window, -1, 0);
}

void ArcadeSdl2::closeWindow(void)
{
    if (this->_render != nullptr) {
        SDL_DestroyRenderer(this->_render);
        this->_render = nullptr;
    }
    // if (this->_surface != nullptr) {
    //     SDL_FreeSurface(this->_surface);
    //     this->_surface = nullptr;
    // }
    if (this->_window != nullptr) {
        SDL_DestroyWindow(this->_window);
        this->_window = nullptr;
    }

}

void *ArcadeSdl2::loadImage(const std::string &path)
{
    (void)path;
    return (nullptr);
}

void ArcadeSdl2::loadFont(const std::string &path)
{
    this->unloadFont();
    this->_font = TTF_OpenFont(path.c_str(), this->_tileSize);
}

void ArcadeSdl2::unloadFont(void)
{
    if (this->_font != nullptr) {
        TTF_CloseFont(this->_font);
        this->_font = nullptr;
    }
}

void ArcadeSdl2::drawRect(int x, int y, int width, int height, uint32_t color)
{
    t_sdl_color colorU;

    colorU.full = color;
    SDL_SetRenderDrawColor(this->_render,
        colorU.rgba[0], colorU.rgba[1], colorU.rgba[2], colorU.rgba[3]);
    this->_rect.x = x;
    this->_rect.y = y;
    this->_rect.w = width;
    this->_rect.h = height;
    SDL_RenderFillRect(this->_render, &(this->_rect));
}

void ArcadeSdl2::drawUnknownTexture(int x, int y, int width, int height, uint32_t color)
{
    int w = width / 2;
    int h = height / 2;

    this->drawRect(x, y, w, h, color);
    this->drawRect(x + w, y + h, w, h, color);
    this->drawRect(x + w, y, w, h, SDL_SETCOLOR(0, 0, 0, 255));
    this->drawRect(x, y + h, w, h, SDL_SETCOLOR(0, 0, 0, 255));
}

void ArcadeSdl2::fill(uint32_t color)
{
    uint8_t *c;
    int w;
    int h;

    if (color >= SDL_TOTALCOLOR) {
        SDL_GetWindowSize(this->_window, &w, &h);
        this->drawUnknownTexture(0, 0, w, h, SDL_SETCOLOR(255, 0, 0, 255));
        return;
    }
    c = this->_colors[color].rgba;
    SDL_SetRenderDrawColor(this->_render, c[0], c[1], c[2], c[3]);
    SDL_RenderClear(this->_render);
}

void ArcadeSdl2::drawTile(int x, int y, uint32_t color)
{
    x *= this->_tileSize;
    y *= this->_tileSize;
    if (color >= SDL_TOTALCOLOR) {
        this->drawUnknownTexture(x , y, this->_tileSize, this->_tileSize,
            SDL_SETCOLOR(255, 0, 255, 255));
        return;
    }
    this->drawRect(x , y, this->_tileSize, this->_tileSize,
        this->_colors[color].full);
}

void ArcadeSdl2::drawImage(int x, int y, void *img)
{
    (void)x;
    (void)y;
    (void)img;
}

void ArcadeSdl2::drawText(const std::string &text, int x, int y, int color)
{
    t_sdl_color colorU;
    int xSize = 0;
    colorU.full = SDL_SETCOLOR(255, 255, 255, 255);
    if (color < SDL_TOTALCOLOR)
        colorU.full = this->_colors[color].full;
    SDL_Color sdlColor = {colorU.rgba[0], colorU.rgba[1], colorU.rgba[2], colorU.rgba[3]};
    SDL_Surface *surface = TTF_RenderText_Solid(this->_font, text.c_str(), sdlColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_render, surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &xSize, nullptr);
    this->_rect = {x * this->_tileSize, y * this->_tileSize, xSize, this->_tileSize};
    SDL_RenderCopy(this->_render, texture, nullptr, &this->_rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void ArcadeSdl2::display(void)
{
    SDL_RenderPresent(this->_render);
}

void ArcadeSdl2::getMousePos(std::vector<int> &coords)
{
    coords.clear();
    coords.resize(2);

    SDL_GetMouseState(&coords[0], &coords[1]);
}

void ArcadeSdl2::getMouseButton(std::vector<bool> &coord)
{
    int tmp;
    uint32_t buttons;

    coord.clear();
    coord.resize(3);
    buttons = SDL_GetMouseState(&tmp, &tmp);
    coord[0] = buttons & SDL_BUTTON(1);
    coord[1] = buttons & SDL_BUTTON(2);
    coord[2] = buttons & SDL_BUTTON(3);
}

void ArcadeSdl2::getButtons(std::vector<bool> &input)
{
    this->handleEvent();
    input = this->_arcadeButtons;
}

void ArcadeSdl2::updateMatchingKey(SDL_Event event, bool toState)
{
    for (int i = 0; i < Arcade::TOTAL_INPUT; ++i) {
        if (event.key.keysym.sym == this->_keyId[i])
            this->_arcadeButtons[i] = toState;
    }
}

void ArcadeSdl2::handleEvent(void)
{
    while (SDL_PollEvent(&this->_event)) {
        switch (this->_event.type) {
            case SDL_KEYDOWN:
                this->updateMatchingKey(this->_event, true);
                break;
            case SDL_KEYUP:
                this->updateMatchingKey(this->_event, false);
                break;
        }
    }
}
