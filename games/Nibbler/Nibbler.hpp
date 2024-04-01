/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Nibller
*/

struct nibbler_body {
    int x_pos;
    int y_pos;
    int order_x;
    int order_y;
};

#ifndef NIBLLER_HPP_
    #define NIBLLER_HPP_
    #include "IGame.hpp"
    #include "ADisplay.hpp"
    #include "LoadLib.hpp"
    #include <cstdlib>
    #include <chrono>

class Nibbler : IGame {
    public:
        Nibbler();
        ~Nibbler() = default;
        const std::string &getName() const override;
        void start(IDisplayModule *display) override;
        void stop() override;
        void update(IDisplayModule *display) override;
        void render() override;
        void handleEvent() override;
        int getState() override;
        std::vector<std::vector<int>> getInitialMap(
            const std::string &path) override;
        bool checkifalive(int x, int y);
        void nibblerMoove();
        void bodyMoove();
        void addbody(int x_tail, int y_tail);
        void placeApple();
        void GameOver();
        void writeScore();
        int getSpriteDir(int x, int y);
        int addWall(int chr);
        bool checkStuck(int chr, int temp_x, int temp_y);
        void checkAllApl();
        void startLevel(bool restart);
        bool canMoove(int x, int y);
        void makeItMoove(int temp_x, int temp_y);
        void mooveAuto(int x, int y);
        int getHead(int x, int y);
        void printMapForGrap();
        void haveEatApple(int x, int y);
        void cinematique(std::string text, int x, int y, int time, colors::Color);
    private:
        int endlevel;
        int life;
        int nufapple;
        int Level;
        int appleEat;
        bool debug;
        int maxy;
        int maxx;
        int score;
        int x_head;
        int y_head;
        int head_old_y;
        int head_old_x;
        int direction_x;
        int direction_y;
        int head;
        int gamestate;
        int time;
        int last_event_val;
        events::Event lastev;
        IDisplayModule *display;
        std::map<std::size_t, nibbler_body> nibbler_bdy;
        std::chrono::time_point<std::chrono::high_resolution_clock> timetnibller;
        std::chrono::time_point<std::chrono::high_resolution_clock> starttnibller;
        std::chrono::duration<double, std::milli> duration_nibller;
        std::vector<std::vector<int>> map;
};

#endif /* !NIBLLER_HPP_ */
