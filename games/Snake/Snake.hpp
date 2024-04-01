/*
** EPITECH PROJECT, 2023
** Snake_hpp
** File description:
** Snake_hpp
*/

#ifndef Snake_hpp
#define Snake_hpp

#include "IGame.hpp"
#include "ADisplay.hpp"
#include "LoadLib.hpp"
#include <chrono>

struct Snake_body {
    int x_pos;
    int y_pos;
    int order_x;
    int order_y;
};

class Snake : public IGame
{
    public:
        Snake();
        ~Snake() = default;
        const std::string &getName() const override;
        void start(IDisplayModule *display) override;
        void stop() override;
        void update(IDisplayModule *display) override;
        void render() override;
        void handleEvent() override;
        int getState() override;
        std::vector<std::vector<int>> getInitialMap(
            const std::string &path) override;
        int checkSnakeLife(int x, int y);
        void SnakeMoove();
        int drawSnakeAndApple(int letter);
        void savePos(int x_tmp, int y_tmp);
        void bodyMove();
        void dispBody(int x_tail, int y_tail);
        void drawRandomApple();
        void GameOver();
        void writeScore();
        int getDirection(int x, int y);
        void firstBack();
        void addBody(Snake_body body);
        void Move(int x, int y);
        void dispFirstBody(int x, int y);
    private:
        bool debug;
        bool first;
        int wait;
        int nb_apple;
        int gamestate;
        int last_event_val;
        bool menu;
        std::string name;
        IDisplayModule *display;
        events::Event lastev;
        int maxy;
        int maxx;
        int x_head;
        int y_head;
        int old_direction_x;
        int old_direction_y;
        int x_direction;
        int y_direction;
        int head;
        std::map<std::size_t, Snake_body> Snake_bdy;
        std::chrono::time_point<std::chrono::high_resolution_clock> timeStartSnake;
        std::chrono::time_point<std::chrono::high_resolution_clock> starttSnake;
        std::chrono::duration<double, std::milli> durationSnake;
        std::vector<std::vector<int>> map;
};

#endif /* !Snake_hpp */
