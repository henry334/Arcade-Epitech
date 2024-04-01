/*
** EPITECH PROJECT, 2023
** SolarFox_hpp
** File description:
** SolarFox_hpp
*/

#ifndef SolarFox_hpp
#define SolarFox_hpp

#include "IGame.hpp"
#include "ADisplay.hpp"
#include "LoadLib.hpp"
#include <thread>
#include <chrono>

#define PRESS 55
#define UNPRESS 0

struct fireball {
    char direction;
    std::vector<int> pos;
    std::vector<int> dir;
    char saved;
};

struct shooting_it {
    std::vector<int> pos;
    int dir;
};

class SolarFox : public IGame
{
    public:
        SolarFox();
        ~SolarFox();
        const std::string &getName() const override;
        void start(IDisplayModule *display) override;
        void stop() override;
        void update(IDisplayModule *display) override;
        void render() override;
        void handleEvent() override;
        int getState() override;
        std::vector<std::vector<int>> getInitialMap(
            const std::string &path) override;
        void moveShip();
        std::vector<std::vector<int>> shipShoot();
        void moveAndShootVilain(void);
        void cinematique(std::string text, int x, int y, int time);
        std::vector<std::vector<int>> shootVilain(std::vector<int>vil_pos, std::vector<std::vector<int>> map, std::vector<int> shoot_dir, std::vector<int> add, char vil_type);
        std::vector<std::vector<int>> moveVilain(int& vil_dir, std::vector<int>vil_pos, std::vector<std::vector<int>> map, char vil_type);
        int getDirection();
        std::vector<int> getShip();
        void setShip(std::vector<int>);
        std::vector<int> getVilain(char vilain);
        int getVilainDir(char vilain);
        bool get_villain_fired_recently();
        std::vector<std::vector<int>> moveFireball(std::vector<std::vector<int>> map);
        std::vector<std::vector<int>> rmvFireball(std::vector<std::vector<int>> map);
        std::vector<fireball> getFireballPos();
        void setFireballPos(std::vector<fireball> shooting_pos);
        std::vector<shooting_it> getShootingPos();
        void setShootingPos(std::vector<shooting_it> shooting_pos);
        void setIsAlive(bool isAlive);
        void setWin(bool win);
        bool getWin();
        bool getIsAlive();
        void writeScore();
        void GameOver();
        void setShooting(int shooting);
        int getShooting();

    private:
        int score;
        bool debug;
        int gamestate;
        std::string name;
        events::Event lastev;
        IDisplayModule *display;
        std::vector<float> ship_rect = {0, 0, 128, 128};
        std::chrono::time_point<std::chrono::high_resolution_clock> startsolar;
        std::chrono::duration<double, std::milli> duration_solar;
        std::vector<std::vector<int>> map;
        int direction = 0;
        std::vector<int> ship_pos = {0, 0};
        std::vector<int> vil_pos_r = {0, 0};
        std::vector<int> vil_pos_l = {0, 0};
        std::vector<int> vil_pos_u = {0, 0};
        std::vector<int> vil_pos_d = {0, 0};
        bool villain_fired_recently = false;
        std::vector<fireball> fireball_pos;
        std::vector<shooting_it> shooting_pos;
        int vil_dir_r = 0;
        int vil_dir_l = 1;
        int vil_dir_u = 0;
        int vil_dir_d = 1;
        int level = 1;
        int life = 3;
        bool win = false;
        bool isAlive = false;
        int spacePress = UNPRESS;
        int shooting = UNPRESS;
        std::chrono::time_point<std::chrono::high_resolution_clock> shoot;
};

#endif /* !SolarFox_hpp */
