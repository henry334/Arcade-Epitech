/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** SFML
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "ADisplay.hpp"

struct Sprite {
    sf::Sprite sfsprite;
    sf::Texture textu;
};

class SFML : public ADisplay 
{
    public:
        SFML();
        SFML(std::string);
        ~SFML();
        void clear() override;
        void display() override;
        void drawSprite(int type, const std::vector<float> &pos, colors::Color color) override;
        void setWindowSize(int width, int height) override;
        void drawText(const std::string &text, const std::vector<int> &pos, colors::Color color) override;
        void drawButton(const std::string &text, const std::vector<int> &pos, const std::vector<int> &size, colors::Color color) override;
        const std::string &getSpritePath(int type) const override;
        bool isMousePressed() override;
        void fetchEvents() override;
        std::vector<int> getMousePos() override;
        events::Event getEvents() override;
        void handleMusic(const std::string &path, bool loop, bool play) override;
    private:
        sf::Text texts;
        sf::Font font;
        sf::Event event;
        sf::RenderWindow window;
        std::map<char, std::unique_ptr<Sprite>> sprites;
        std::map<char, std::string> maps = {
            {'#',"./ressource/solar-fox/none.png"},
            {'.',"./ressource/solar-fox/fireball.png"},
            {'*',"./ressource/solar-fox/shoot.png"},
            {'|',"./ressource/solar-fox/none.png"},
            {'c',"./ressource/solar-fox/essence.png"},
            {' ',"./ressource/solar-fox/none.png"},
            {'P', "./ressource/snake/apple.png"},
            {'W',"./ressource/back.png"},
            {'b', "./ressource/purple.png"},
            {'P', "./ressource/snake/apple.png"},
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

        std::map<colors::Color, sf::Color> color = {
            {colors::RED, sf::Color::Red},
            {colors::BLACK, sf::Color::Black},
            {colors::CYAN, sf::Color::Cyan},
            {colors::YELLOW, sf::Color::Yellow},
            {colors::GREEN, sf::Color::Green},
            {colors::BLUE, sf::Color::Blue},
            {colors::WHITE, sf::Color::White}
        };

        std::map<int, events::Events> eventmouse = {
            {sf::Mouse::Left, events::Events::MOUSE_LEFT},
            {sf::Mouse::Right, events::Events::MOUSE_RIGHT},
            {'1', events::Events::MOUSE_CLICK},
            {-100, events::Events::MOUSE_MOVE}
        };
        std::map<int, events::Events> eventkey = {
            {sf::Keyboard::X, events::Events::QUIT},
            {sf::Keyboard::Z, events::Events::UP},
            {sf::Keyboard::S, events::Events::DOWN},
            {sf::Keyboard::Q, events::Events::LEFT},
            {sf::Keyboard::D, events::Events::RIGHT},
            {sf::Keyboard::I, events::Events::I_CHANGE},
            {sf::Keyboard::P, events::Events::BACK},
            {sf::Keyboard::Space, events::Events::A_BUTTON},
            {sf::Keyboard::G, events::Events::G_CHANGE},
            {sf::Keyboard::N, events::Events::B_BUTTON}
        };
};
