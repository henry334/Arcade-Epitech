/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Menu
*/

#pragma once

#include "IGame.hpp"
#include "LoadLib.hpp"
#include "ADisplay.hpp"
#include "Core.hpp"
#include "Utils.hpp"

struct btn {
    std::vector<int> vect;
    std::vector<int> rect;
    colors::Color col;
    std::string point_so;
    std::string name;
};

class Menu : public IGame {
    public:
        Menu();
        ~Menu() = default;
        void stop() override;
        void start(IDisplayModule *display) override;
        void render() override;
        void update(IDisplayModule *display) override;
        int getState() override;
        void handleEvent() override;
        int changelib();
        std::string mouseonbutton();
        bool buttonclicked();
        void draw_allbtn();
        void creatbtn(std::string, std::vector<int>, std::vector<int> one, colors::Color);
        const std::string &getName() const override;
        std::vector<std::vector<int>> getInitialMap(
            const std::string &path) override;
        void setLibs(std::map<std::string, std::size_t> libs,
            std::map<std::string, std::size_t> games);
        int getExitCode();
        void startgame(std::string gamestr);
        void checkBtnMouse();
        void getData();
        void writeData(std::string path, std::string text);
        void changePseudo();
        bool changePseudoSec(std::string *, int *, std::string *, std::string *, btn);
        void changePseudoTh(std::string *, std::string *, std::string *, int *);
        void displayHighScores();
        Core *getCore();
        void nextGame();
    private:
        std::string gameon;
        std::string pseudo;
        Core util;
        Utils utils;
        std::map<std::string, std::size_t> libs;
        std::map<std::string, std::size_t> gameslib;
        std::map<std::string, std::size_t> games_highscore;
        int gamestate;
        std::string name;
        events::Event lastev;
        void* lib_handle;
        void* lib_handlegame;
        IDisplayModule *display;
        IGame *game;
        std::string lastbutton_clicked;
        std::map<std::string, btn> buttons;
};
