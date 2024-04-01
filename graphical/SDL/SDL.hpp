/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** SDL
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "ADisplay.hpp"

struct Sprite {
    SDL_Texture *texture;
    SDL_Rect dstrect;
    colors::Color col;
    int h;
    int w;
};

class SDL :  public ADisplay {
    public:
        SDL();
        SDL(std::string);
        ~SDL();
        void clear() override;
        void display() override;
        void drawText(const std::string &text, const std::vector<int> &pos, colors::Color color) override;
        void drawSprite(int type, const std::vector<float> &pos, colors::Color color) override;
        void setWindowSize(int width, int height) override;
        const std::string &getSpritePath(int type) const override;
        void drawButton(const std::string &text, const std::vector<int> &pos, const std::vector<int> &size, colors::Color color) override;
        void fetchEvents() override;
        events::Event getEvents() override;
        std::vector<int> getMousePos() override;
        bool isMousePressed() override;
        void handleMusic(const std::string &path, bool loop, bool play) override;
    private:
        Mix_Music *music;
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::map<char, std::unique_ptr<Sprite>> sprites;
        std::map<char, std::string> maps = {
            {'W',"./ressource/back.png"},
            {'#',"./ressource/solar-fox/none.png"},
            {'.',"./ressource/solar-fox/fireball.png"},
            {'*',"./ressource/solar-fox/shoot.png"},
            {'c',"./ressource/solar-fox/essence.png"},
            {' ',"./ressource/solar-fox/none.png"},
            {'P', "./ressource/snake/apple.png"},
            {'b', "./ressource/purple.png"},
            {'S', "./ressource/snake/snake_head_up.png"},
            {'V', "./ressource/snake/snake_head_down.png"},
            {'B', "./ressource/snake/snake_head_right.png"},
            {'N', "./ressource/snake/snake_head_left.png"},
            {'G', "./ressource/snake/background.png"},
            {'Z', "./ressource/snake/snake_body.png"},
            {'X', "./ressource/snake/snake_body_trnd.png"},
            {'O', "./ressource/snake/game_over.jpg"},
            {'Y', "./ressource/snake/firstback.png"},
            {'R', "./ressource/solar-fox/ship_hero/hero-r.png"},
            {'L', "./ressource/solar-fox/ship_hero/hero-l.png"},
            {'U', "./ressource/solar-fox/ship_hero/hero-u.png"},
            {'D', "./ressource/solar-fox/ship_hero/hero-d.png"},
            {'r', "./ressource/solar-fox/ship_villain/villain-r.png"},
            {'l', "./ressource/solar-fox/ship_villain/villain-l.png"},
            {'u', "./ressource/solar-fox/ship_villain/villain-u.png"},
            {'d', "./ressource/solar-fox/ship_villain/villain-d.png"},
            {'?', "./ressource/greenbg.png"},
            {'!', "./ressource/snake/wall.png"},
            {0, "./ressource/solar-fox/none.png"},
            {1, "./ressource/block.png"},
            {2, "./ressource/circle.png"}
        };

        std::map<colors::Color, std::vector<Uint8>> color = {
            {colors::RED, {255, 0, 0, 255}},
            {colors::BLACK, {0, 0, 0, 255}},
            {colors::CYAN, {0, 255, 255, 255}},
            {colors::YELLOW, {255, 255, 0, 255}},
            {colors::GREEN, {0, 255, 0, 255}},
            {colors::BLUE, {0, 0, 255, 255}},
            {colors::WHITE, {255, 255, 255, 255}},
        };

        std::map<int, events::Events> eventtype = {
            {SDL_QUIT, events::Events::QUIT},
            {SDL_BUTTON_LEFT, events::Events::MOUSE_LEFT},
            {SDL_BUTTON_RIGHT, events::Events::MOUSE_RIGHT},
            {'1', events::Events::MOUSE_CLICK},
            {-100, events::Events::MOUSE_MOVE},
            {SDLK_x, events::Events::QUIT},
            {SDLK_z, events::Events::UP},
            {SDLK_s, events::Events::DOWN},
            {SDLK_q, events::Events::LEFT},
            {SDLK_d, events::Events::RIGHT},
            {SDLK_p, events::Events::BACK},
            {SDLK_i, events::Events::I_CHANGE},
            {SDLK_g, events::Events::G_CHANGE},
            {SDLK_SPACE, events::Events::A_BUTTON},
            {SDLK_n, events::Events::B_BUTTON},
        };
};