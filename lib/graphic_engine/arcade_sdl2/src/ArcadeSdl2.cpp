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
    this->_keyId[Arcade::UP_ARROW] = SDLK_UP;
    this->_keyId[Arcade::DOWN_ARROW] = SDLK_DOWN;
    this->_keyId[Arcade::LEFT_ARROW] = SDLK_LEFT;
    this->_keyId[Arcade::RIGHT_ARROW] = SDLK_RIGHT;
    this->_keyId[Arcade::BUTTON1] = SDLK_a;
    this->_keyId[Arcade::BUTTON2] = SDLK_z;
    this->_keyId[Arcade::BUTTON3] = SDLK_e;
    this->_keyId[Arcade::BUTTON4] = SDLK_r;
    this->_keyId[Arcade::PREV_GAME] = SDLK_F2;
    this->_keyId[Arcade::NEXT_GAME] = SDLK_F3;
    this->_keyId[Arcade::PREV_LIB] = SDLK_F4;
    this->_keyId[Arcade::NEXT_LIB] = SDLK_F5;
    this->_keyId[Arcade::RESTART] = SDLK_F6;
    this->_keyId[Arcade::HOME_MENU] = SDLK_F1;
    this->_keyId[Arcade::EXIT] = SDLK_ESCAPE;
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

void ArcadeSdl2::fill(uint32_t color)
{
    char *c = (char*) &color;

    SDL_SetRenderDrawColor(this->_render, c[0], c[1], c[2], c[3]);
    SDL_RenderClear(this->_render);
}

void ArcadeSdl2::drawTile(int x, int y, uint32_t color)
{
    char *c = (char*) &color;

    SDL_SetRenderDrawColor(this->_render, c[0], c[1], c[2], c[3]);
    this->_rect.x = x * this->_tileSize;
    this->_rect.y = y * this->_tileSize;
    this->_rect.w = this->_tileSize;
    this->_rect.h = this->_tileSize;
    SDL_RenderFillRect(this->_render, &(this->_rect));
}

void ArcadeSdl2::drawImage(int x, int y, void *img)
{
    (void)x;
    (void)y;
    (void)img;
}

void ArcadeSdl2::drawText(const std::string &text, int x, int y, int color)
{
    int xSize = 0;
    unsigned char *c = (unsigned char*) &color;
    SDL_Color sdlColor = {c[0], c[1], c[2], c[3]};
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

std::vector<int> ArcadeSdl2::getMousePos(void)
{
    std::vector<int> mousePos(2);

    SDL_GetMouseState(&mousePos[0], &mousePos[1]);
    return (mousePos);
}

std::vector<bool> ArcadeSdl2::getMouseButton(void)
{
    int tmp;
    uint32_t buttons;
    std::vector<bool> mouseButtons(3);

    buttons = SDL_GetMouseState(&tmp, &tmp);
    mouseButtons[0] = buttons & SDL_BUTTON(1);
    mouseButtons[1] = buttons & SDL_BUTTON(2);
    mouseButtons[2] = buttons & SDL_BUTTON(3);
    return (mouseButtons);
}

std::vector<bool> ArcadeSdl2::getButtons(void)
{
    this->handleEvent();
    return (this->_arcadeButtons);
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
