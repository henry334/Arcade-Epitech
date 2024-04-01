/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Events
*/

#pragma once

#include <curses.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ADisplay.hpp"

class NCurses : public ADisplay
{
    public:
        NCurses();
        NCurses(std::string name);
        ~NCurses();
        void clear() override;
        void display() override;
        void setWindowSize(int width, int height) override;
        void drawMap(const std::vector<std::vector<int>> &map) override;
        void drawText(const std::string &text, const std::vector<int> &pos, colors::Color color) override;
        void drawSprite(int type, const std::vector<float> &pos, colors::Color color) override;
        const std::string &getSpritePath(int type) const override;
        void drawButton(const std::string &text, const std::vector<int> &pos, const std::vector<int> &size, colors::Color color) override;
        bool isMousePressed() override;
        void fetchEvents() override;
        std::vector<int> getMousePos() override;
        events::Event getEvents() override;
        void handleMusic(const std::string &path, bool loop, bool play) override;
    private:
        double wind_x;
        double wind_y;
        int ch;
        int prev_x;
        int prev_y; 
        MEVENT event;
        std::map<char, std::string> maps = {
            {'#',"#"},
            {'W',""},
            {'.',"@"},
            {'*',"*"},
            {'b', ""},
            {'S', "^"},
            {'V', "v"},
            {'B', ">"},
            {'N', "<"},
            {'G', ""},
            {'U', "^"},
            {'D', "v"},
            {'R', ">"},
            {'L', "<"},
            {'u', "u"},
            {'d', "d"},
            {'r', "r"},
            {'l', "l"},
            {'P', "O"},
            {'Z', "#"},
            {'X', "#"},
            {'z', "#"},
            {'c', "o"},
            {'?', ""},
            {'!', "#"},
        };

        std::map<char, colors::Color> chartocolor = {
            {'Z', colors::GREEN},
            {'X', colors::GREEN},
            {'P', colors::RED},
            {'S', colors::GREEN},
            {'V', colors::GREEN},
            {'B', colors::GREEN},
            {'N', colors::GREEN},
            {'Z', colors::GREEN},
            {'X', colors::GREEN},
            {'U', colors::GREEN},
            {'D', colors::GREEN},
            {'R', colors::GREEN},
            {'L', colors::GREEN},
            {'.', colors::YELLOW},
            {'r', colors::RED},
            {'l', colors::RED},
            {'u', colors::RED},
            {'d', colors::RED}
        };

        std::map<colors::Color, int> getcolor = {
            {colors::RED, 1},
            {colors::GREEN, 2},
            {colors::BLUE, 3},
            {colors::CYAN, 4},
            {colors::BLACK, 5},
            {colors::YELLOW, 6},
            {colors::WHITE, 7},
        };

        std::map<int, events::Events> eventtype = {
            {'x', events::Events::QUIT},
            {BUTTON1_CLICKED, events::Events::MOUSE_LEFT},
            {BUTTON2_CLICKED, events::Events::MOUSE_RIGHT},
            {OK, events::Events::MOUSE_CLICK},
            {-100, events::Events::MOUSE_MOVE},
            {'z', events::Events::UP},
            {'s', events::Events::DOWN},
            {'q', events::Events::LEFT},
            {'d', events::Events::RIGHT},
            {'p', events::Events::BACK},
            {'i', events::Events::I_CHANGE},
            {'g', events::Events::G_CHANGE},
            {' ', events::Events::A_BUTTON},
            {'n', events::Events::B_BUTTON},
        };
};
