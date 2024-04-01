/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** SDL
*/

#include "SDL.hpp"

SDL::SDL(std::string name)
{
    this->havebeeno = 1;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    this->title = 32;
    this->title_height_btn = 17.5;
    this->title_width_btn = 16;
    this->libname = "SDL2";
    this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(window, -1, 0);
    return;
}

SDL::SDL()
{
    this->havebeeno = 0;
}

SDL::~SDL()
{
    if (this->havebeeno == 0)
        return;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();
    return;
}

void SDL::clear()
{
    SDL_RenderClear(this->renderer);
}

void SDL::display()
{
    SDL_RenderPresent(this->renderer);
}

void SDL::drawSprite(int type, const std::vector<float> &pos, colors::Color color)
{
    (void)(color);
    if (this->sprites.count(type) <= 0) {
        std::unique_ptr<Sprite>(sp) = std::make_unique<Sprite>();
        SDL_Surface* surface = IMG_Load(this->maps[type].c_str());
        sp->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        sp->w = surface->w;
        sp->h = surface->h;
        this->sprites[type] = std::move(sp);
        SDL_FreeSurface(surface);
    }
    SDL_Rect dstrect = {static_cast<int>(pos[0]), static_cast<int>(pos[1]), this->sprites[type]->w, this->sprites[type]->h};
    SDL_RenderCopy(this->renderer, this->sprites[type]->texture, NULL, &dstrect);
}

void SDL::drawText(const std::string &text, const std::vector<int> &pos, colors::Color color)
{
    int p = 40;
    if (pos.size() >= 3)
        p = pos[2];
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("./ressource/ttf/RobotoCondensed-Light.ttf", p);
    if (font == nullptr) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
        return;
    }
    std::vector<Uint8> c = {0, 0, 0, 255};
    if (this->color.count(color) > 0)
        c = this->color[color];
    SDL_Color cl = {c[0], c[1], c[2], c[3]};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), cl);
    if (surface == nullptr) {
        std::cerr << "Error creating surface for text: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Error creating texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect rect = {pos[0], pos[1], surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
}

void SDL::drawButton(const std::string &text, const std::vector<int> &poss, const std::vector<int> &sizes, colors::Color color)
{
    std::vector<int> all = this->mapToWindow({poss[0], poss[1], sizes[0], sizes[1]});
    std::vector<float> pos = {static_cast<float>(all[0]), static_cast<float>(all[1]), static_cast<float>(all[2]), static_cast<float>(all[3])};
    int word = text.size();
    this->drawSprite('b', pos, color);
    if (strlen(text.c_str()) > 0 && text[0] != '/') {
        drawText(text, {(all[0] + all[3] / 2) - word * 15, all[1] + 37, poss[2]}, color);
    }
}

void SDL::handleMusic(const std::string &path, bool loop, bool play)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    this->music = nullptr;
    if (play) {
        if (music == nullptr) {
            music = Mix_LoadMUS(path.c_str());
            if (music == nullptr) {
                std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
                return;
            }
        }
        if (loop == true)
            Mix_PlayMusic(music, -1);
        else
            Mix_PlayMusic(music, 1);
    } else {
        if (music != nullptr) {
            Mix_HaltMusic();
            Mix_FreeMusic(music);
            music = nullptr;
        }
    }
}

const std::string &SDL::getSpritePath(int type) const
{
    return this->maps.at(type);
}

bool SDL::isMousePressed()
{
    if (this->event.type == SDL_MOUSEBUTTONDOWN) {
        return true;
    }
    return false;
}

void SDL::fetchEvents()
{
    SDL_PollEvent(&this->event);
    int ch = event.type;
    switch (ch) {
        case SDL_KEYDOWN:
            this->aenv = this->eventtype.count(this->event.key.keysym.sym) > 0 ?
                this->eventtype[this->event.key.keysym.sym] : events::Events::NONE;
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->aenv = this->eventtype.count(this->event.button.button) > 0 ?
                this->eventtype[this->event.button.button] : events::Events::NONE;
            break;
        case SDL_QUIT:
            this->aenv = events::Events::QUIT;
            break;
        default:
            this->aenv = events::Events::NONE;
            break;
    }
}

std::vector<int> SDL::getMousePos()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return {x, y};
}

events::Event SDL::getEvents()
{
    return this->aenv;
}

void SDL::setWindowSize(int width, int height)
{
    width *= this->getTileSize();
    height *= this->getTileSize();
    width = width > 1920 ? 1920 : width;
    height = height > 1080 ? 1080 : height;
    SDL_SetWindowSize(this->window, width, height);
}

extern "C"
{
    ADisplay* createDisplayModule(char *name)
    {
        if (name != NULL)
            return new SDL("Arcade SDL");
        else
            return new SDL();
    }
}

extern "C"
{
    void destroyDisplayModule(ADisplay* module1)
    {
        delete module1;
    }
}