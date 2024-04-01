/*
** EPITECH PROJECT, 2023
** SolarFox
** File description:
** SolarFox
*/

#include "SolarFox.hpp"
#include <iostream>

SolarFox::SolarFox()
{
    this->score = 0;
    this->debug = false;
    map = this->getInitialMap("");
    this->gamestate = GameState::RUNNING;
}

SolarFox::~SolarFox()
{
    return;
}

const std::string& SolarFox::getName() const
{
    static const std::string name = "SolarFox";
    return name;
}

void SolarFox::start(IDisplayModule *display)
{
    this->display = display;
    this->shoot = std::chrono::high_resolution_clock::now();
    this->startsolar = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
}

void SolarFox::stop()
{
    this->gamestate = GameState::GAME_OVER;
    return;
}

void SolarFox::update(IDisplayModule *display)
{
    this->display = display;
    this->display->setWindowSize(40, 19);
}

void SolarFox::render()
{
    this->display->clear();
    this->handleEvent();
    this->display->drawMap(map);
    this->moveShip();
    map = this->shipShoot();
    map = this->rmvFireball(map);
    this->moveAndShootVilain();
    this->display->drawText("Score: " + std::to_string(this->score), {0, 0, 40}, colors::Colors::RED);
    this->display->drawText("Level: " + std::to_string(this->level),
        {this->display->mapToWindow({10, 0})[0], 0, 40}, colors::Colors::RED);
    this->display->display();
}

int SolarFox::getState()
{
    return this->gamestate;
}

std::vector<std::vector<int>> SolarFox::getInitialMap(
const std::string &path)
{
    if (path[0] == 'w')
        return {
            { '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', '#', ' '},
            { ' ', '#', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
        };
    else
        return {
            { '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'd', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', '#', ' '},
            { 'r', '#', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', '#', ' '},
            { ' ', '#', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', '#', 'l'},
            { ' ', '#', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', 'R', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
            { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            { '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'u', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
        };
}

std::vector<std::vector<int>> SolarFox::rmvFireball(std::vector<std::vector<int>> map)
{
    std::chrono::duration<double, std::milli> dr;
    dr = (std::chrono::high_resolution_clock::now() - this->shoot);
    if (dr.count() >= 600) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 38; j++) {
                if (map[i][j] == '*') {
                    map[i][j] = ' ';
                }
            }
        }
        this->shoot = std::chrono::high_resolution_clock::now();
    }
    return map;
}

void SolarFox::moveShip(void)
{
    this->ship_pos = getShip();
    this->direction = getDirection();
    static auto last_move_time = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move_time);
    if (elapsed_time.count() >= 110 - this->spacePress) {
        last_move_time = now;
        switch (this->direction) {
        case 3:
            {
                int new_y = ship_pos[1] - 1;
                int new_x = ship_pos[0];
                char new_tile = map[new_y][new_x];
                if (new_tile == '#' || new_tile == 'r' || new_tile == 'l' || new_tile == 'u' || new_tile == 'd') {
                    return;
                }
                if (new_tile == 'c') {
                    this->score += 10;
                }
                if (new_tile == '.') {
                    this->GameOver();
                    return;
                }
                map[ship_pos[1]][ship_pos[0]] = ' ';
                map[ship_pos[1] - 1][ship_pos[0]] = 'U';
                ship_pos = {new_x, new_y};
                setShip(ship_pos);
                break;
            }
        case 1:
            {
                int new_y = ship_pos[1] + 1;
                int new_x = ship_pos[0];
                char new_tile = map[new_y][new_x];
                if (new_tile == '#' || new_tile == 'r' || new_tile == 'l' || new_tile == 'u' || new_tile == 'd') {
                    return;
                }
                if (new_tile == 'c') {
                    this->score += 10;
                }
                if (new_tile == '.') {
                    this->GameOver();
                    return;
                }
                map[ship_pos[1]][ship_pos[0]] = ' ';
                map[ship_pos[1] + 1][ship_pos[0]] = 'D';
                ship_pos = {new_x, new_y};
                setShip(ship_pos);
                break;
            }
        case 0:
            {
                int new_y = ship_pos[1];
                int new_x = ship_pos[0] + 1;
                char new_tile = map[new_y][new_x];
                if (new_tile == '#' || new_tile == 'r' || new_tile == 'l' || new_tile == 'u' || new_tile == 'd') {
                    return;
                }
                if (new_tile == 'c') {
                    this->score += 10;
                }
                if (new_tile == '.') {
                    this->GameOver();
                    return;
                }
                map[ship_pos[1]][ship_pos[0]] = ' ';
                map[ship_pos[1]][ship_pos[0] + 1] = 'R';
                ship_pos = {new_x, new_y};
                setShip(ship_pos);
                break;
            }
        case 2:
            {
                int new_y = ship_pos[1];
                int new_x = ship_pos[0] - 1;
                char new_tile = map[new_y][new_x];
                if (new_tile == '#' || new_tile == 'r' || new_tile == 'l' || new_tile == 'u' || new_tile == 'd') {
                    return;
                }
                if (new_tile == 'c') {
                    this->score += 10;
                }
                if (new_tile == '.') {
                    this->GameOver();
                    return;
                }
                map[ship_pos[1]][ship_pos[0]] = ' ';
                map[ship_pos[1]][ship_pos[0] - 1] = 'L';
                ship_pos = {new_x, new_y};
                setShip(ship_pos);
                break;
            }
        }
    }
}

std::vector<std::vector<int>> SolarFox::shipShoot()
{
    this->ship_pos = getShip();
    this->direction = getDirection();
    this->shooting = getShooting();
    if (this->shooting == PRESS) {
        if (this->direction == 0) {
            if (map[ship_pos[1]][ship_pos[0] + 1] == '#')
                map[ship_pos[1]][ship_pos[0] + 2] = '*';
            else if (map[ship_pos[1]][ship_pos[0] + 2] == '#') {
                map[ship_pos[1]][ship_pos[0] + 1] = '*';
                map[ship_pos[1]][ship_pos[0] + 3] = '*';
            }
            else if (map[ship_pos[1]][ship_pos[0] + 3] == '#') {
                map[ship_pos[1]][ship_pos[0] + 1] = '*';
                map[ship_pos[1]][ship_pos[0] + 2] = '*';
            } else {
                map[ship_pos[1]][ship_pos[0] + 2] = '*';
                map[ship_pos[1]][ship_pos[0] + 3] = '*';
            }
        }
        if (this->direction == 1) {
            if (map[ship_pos[1] + 1][ship_pos[0]] == '#')
                map[ship_pos[1] + 2][ship_pos[0]] = '*';
            else if (map[ship_pos[1] + 2][ship_pos[0]] == '#') {
                map[ship_pos[1] + 1][ship_pos[0]] = '*';
                map[ship_pos[1] + 3][ship_pos[0]] = '*';
            } else if (map[ship_pos[1] + 3][ship_pos[0]] == '#') {
                map[ship_pos[1] + 1][ship_pos[0]] = '*';
                map[ship_pos[1] + 2][ship_pos[0]] = '*';
            } else {
                map[ship_pos[1] + 2][ship_pos[0]] = '*';
                map[ship_pos[1] + 3][ship_pos[0]] = '*';
            }
        }
        if (this->direction == 2) {
            if (map[ship_pos[1]][ship_pos[0] - 1] == '#')
                map[ship_pos[1]][ship_pos[0] - 2] = '*';
            else if (map[ship_pos[1]][ship_pos[0] - 2] == '#') {
                map[ship_pos[1]][ship_pos[0] - 1] = '*';
                map[ship_pos[1]][ship_pos[0] - 3] = '*';
            } else if (map[ship_pos[1]][ship_pos[0] - 3] == '#') {
                map[ship_pos[1]][ship_pos[0] - 1] = '*';
                map[ship_pos[1]][ship_pos[0] - 2] = '*';
            } else {
                map[ship_pos[1]][ship_pos[0] - 2] = '*';
                map[ship_pos[1]][ship_pos[0] - 3] = '*';
            }
        }
        if (this->direction == 3) {
            if (map[ship_pos[1] - 1][ship_pos[0]] == '#')
                map[ship_pos[1] - 2][ship_pos[0]] = '*';
            else if (map[ship_pos[1] - 2][ship_pos[0]] == '#') {
                map[ship_pos[1] - 1][ship_pos[0]] = '*';
                map[ship_pos[1] - 3][ship_pos[0]] = '*';
            } else if (map[ship_pos[1] - 3][ship_pos[0]] == '#') {
                map[ship_pos[1] - 1][ship_pos[0]] = '*';
                map[ship_pos[1] - 2][ship_pos[0]] = '*';
            } else {
                map[ship_pos[1] - 2][ship_pos[0]] = '*';
                map[ship_pos[1] - 3][ship_pos[0]] = '*';
            }
        }
        map = this->rmvFireball(map);
        setShooting(UNPRESS);
    }
    return map;
}

std::vector<std::vector<int>> SolarFox::moveVilain(int& vil_dir, std::vector<int>vil_pos, std::vector<std::vector<int>> map, char vil_type)
{
    if (vil_type == 'r' || vil_type == 'l') {
        if (vil_dir == 0) {
            if (map[vil_pos[1] - 1][vil_pos[0]] == '#')
                vil_dir = 1;
            else {
                map[vil_pos[1]][vil_pos[0]] = ' ';
                map[vil_pos[1] - 1][vil_pos[0]] = vil_type;
                vil_pos = {vil_pos[1] - 1, vil_pos[0]};
            }
        }
        if (vil_dir == 1) {
            if (map[vil_pos[1] + 1][vil_pos[0]] == '#')
                vil_dir = 0;
            else {
                map[vil_pos[1]][vil_pos[0]] = ' ';
                map[vil_pos[1] + 1][vil_pos[0]] = vil_type;
                vil_pos = {vil_pos[1] + 1, vil_pos[0]};
            }
        }
    } else {
        if (vil_dir == 0) {
            if (map[vil_pos[1]][vil_pos[0] - 1] == '#')
                vil_dir = 1;
            else {
                map[vil_pos[1]][vil_pos[0]] = ' ';
                map[vil_pos[1]][vil_pos[0] - 1] = vil_type;
                vil_pos = {vil_pos[1], vil_pos[0] - 1};
            }
        }
        if (vil_dir == 1) {
            if (map[vil_pos[1]][vil_pos[0] + 1] == '#')
                vil_dir = 0;
            else {
                map[vil_pos[1]][vil_pos[0]] = ' ';
                map[vil_pos[1]][vil_pos[0] + 1] = vil_type;
                vil_pos = {vil_pos[1], vil_pos[0] + 1};
            }
        }
    }
    return map;
}

bool SolarFox::get_villain_fired_recently()
{
    return villain_fired_recently;
}

std::vector<fireball> SolarFox::getFireballPos()
{
    return fireball_pos;
}

void SolarFox::setFireballPos(std::vector<fireball> fireball_pos)
{
    this->fireball_pos = fireball_pos;
}

std::vector<shooting_it> SolarFox::getShootingPos()
{
    return shooting_pos;
}

void SolarFox::setShootingPos(std::vector<shooting_it> shooting_pos)
{
    this->shooting_pos = shooting_pos;
}

std::vector<std::vector<int>> SolarFox::moveFireball(std::vector<std::vector<int>> map)
{
    std::vector<fireball> fireball_pos = getFireballPos();
    for (int i = 0; i < fireball_pos.size(); i++) {
        if (map[fireball_pos[i].pos[0] + fireball_pos[i].dir[0]][fireball_pos[i].pos[1] + fireball_pos[i].dir[1]] == '#' || 
        map[fireball_pos[i].pos[0] + fireball_pos[i].dir[0]][fireball_pos[i].pos[1] + fireball_pos[i].dir[1]] == '*') {
            map[fireball_pos[i].pos[0]][fireball_pos[i].pos[1]] = ' ';
            fireball_pos.erase(fireball_pos.begin() + i);
            setFireballPos(fireball_pos);
            i--;
        } else {
            map[fireball_pos[i].pos[0]][fireball_pos[i].pos[1]] = fireball_pos[i].saved;
             if (map[fireball_pos[i].pos[0] + fireball_pos[i].dir[0]][fireball_pos[i].pos[1] + fireball_pos[i].dir[1]] == '.')
                fireball_pos[i].saved = ' ';
            else
                fireball_pos[i].saved = map[fireball_pos[i].pos[0] + fireball_pos[i].dir[0]][fireball_pos[i].pos[1] + fireball_pos[i].dir[1]];
            map[fireball_pos[i].pos[0] + fireball_pos[i].dir[0]][fireball_pos[i].pos[1] + fireball_pos[i].dir[1]] = '.';
            fireball_pos[i].pos = {fireball_pos[i].pos[0] + fireball_pos[i].dir[0], fireball_pos[i].pos[1] + fireball_pos[i].dir[1]};
            setFireballPos(fireball_pos);
        }
    }
    return map;
}

std::vector<std::vector<int>> SolarFox::shootVilain(std::vector<int>vil_pos, std::vector<std::vector<int>> map, std::vector<int> shoot_dir, std::vector<int> add, char vil_type)
{
    villain_fired_recently = get_villain_fired_recently();
    if (!villain_fired_recently) {
        char temp;
        int random_num = rand() % 100 + 1;
        if (random_num <= 15) {
            temp = map[vil_pos[1] + add[0]][vil_pos[0] + add[1]]; 
            map[vil_pos[1] + add[0]][vil_pos[0] + add[1]] = '.';
            fireball_pos.push_back({vil_type, {vil_pos[1] + add[0], vil_pos[0] + add[1]}, shoot_dir, temp});
            villain_fired_recently = true;
        }
    }
    return map;
}


void SolarFox::moveAndShootVilain(void)
{
    this->vil_pos_r = getVilain('r');
    this->vil_pos_l = getVilain('l');
    this->vil_pos_u = getVilain('u');
    this->vil_pos_d = getVilain('d');
    this->vil_dir_r = getVilainDir('r');
    this->vil_dir_l = getVilainDir('l');
    this->vil_dir_u = getVilainDir('u');
    this->vil_dir_d = getVilainDir('d');
    this->fireball_pos = getFireballPos();
    static auto last_move_time = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move_time);
    if (elapsed_time.count() >= 180 - (this->level * 50)) {
        last_move_time = now;
        map = moveVilain(this->vil_dir_r, this->vil_pos_r, this->map, 'r');
        map = moveVilain(this->vil_dir_l, this->vil_pos_l, this->map, 'l');
        map = moveVilain(this->vil_dir_u, this->vil_pos_u, this->map, 'u');
        map = moveVilain(this->vil_dir_d, this->vil_pos_d, this->map, 'd');
        map = shootVilain(this->vil_pos_r, this->map, {0, 1}, {0, 2},'r');
        map = shootVilain(this->vil_pos_l, this->map, {0, -1}, {0, -2},'l');
        map = shootVilain(this->vil_pos_u, this->map, {-1, 0}, {-2, 0},'u');
        map = shootVilain(this->vil_pos_d, this->map, {1, 0}, {2, 0},'d');
        map = moveFireball(map);
    }
    villain_fired_recently = false;
}

void SolarFox::handleEvent(void)
{
    setWin(true);
    setIsAlive(false);
    this->lastev = display->getEvents();
    for (int c = 0; c < map.size(); c++) {
        for (int i = 0; i < map[c].size(); i++) {
            if (map[c][i] == 'R' || map[c][i] == 'L' || map[c][i] == 'U' || map[c][i] == 'D') {
                ship_pos = {i, c};
                setIsAlive(true);
            }
            if (map[c][i] == 'c')
                setWin(false);
            if (map[c][i] == 'r') {
                vil_pos_r = {i, c};
            }
            if (map[c][i] == 'l') {
                vil_pos_l = {i, c};
            }
            if (map[c][i] == 'u') {
                vil_pos_u = {i, c};
            }
            if (map[c][i] == 'd') {
                vil_pos_d = {i, c};
            }
        }
    }
    if (this->lastev == events::Events::A_BUTTON) {
        if (this->spacePress == UNPRESS)
            this->spacePress = PRESS;
        else
            this->spacePress = UNPRESS;
    }
    if (this->lastev == events::Events::B_BUTTON) {
        shooting_pos.push_back({getShip(), getDirection()});
        setShootingPos(shooting_pos);
        setShooting(PRESS);
    }
    if (getIsAlive() == 0) {
        this->GameOver();
        return;
    }
    if (getWin() == 1) {
        this->level++;
        fireball_pos = {};
        setFireballPos(fireball_pos);
        this->map = this->getInitialMap("w");
        cinematique("LEVEL " + std::to_string(this->level)
        + " LIFE: " + std::to_string(this->life), 15, 10, 3);
        return;
    }
    if (this->lastev == events::Events::UP)
        this->direction = 3;
    if (this->lastev == events::Events::DOWN)
        this->direction = 1;
    if (this->lastev == events::Events::RIGHT)
        this->direction = 0;
    if (this->lastev == events::Events::LEFT)
        this->direction = 2;
}

void SolarFox::GameOver()
{
    this->writeScore();
    this->display->clear();
    std::vector<int> t = this->display->mapToWindow({5, 2});
    this->display->drawText("GAME OVER", {t[0], t[1], 40}, colors::Colors::RED);
    t = this->display->mapToWindow({5, 4});
    this->display->drawText("Presse 'P' to go back to Menu", {t[0], t[1], 40}, colors::Colors::WHITE);
    t = this->display->mapToWindow({5, 6});
    this->display->drawText("Your Score: " + std::to_string(this->score), {t[0], t[1], 40}, colors::Colors::RED);
    this->display->display();
    while (1) {
        this->display->fetchEvents();
        this->lastev = this->display->getEvents();
        if (this->lastev == events::BACK) {
            this->stop();
            break;
        }
    }
}

int SolarFox::getDirection(void)
{
    return this->direction;
}

std::vector<int> SolarFox::getShip(void)
{
    return this->ship_pos;
}

void SolarFox::setShip(std::vector<int> ship_pos)
{
    this->ship_pos = ship_pos;
}

std::vector<int> SolarFox::getVilain(char vilain)
{
    if (vilain == 'r')
        return this->vil_pos_r;
    if (vilain == 'l')
        return this->vil_pos_l;
    if (vilain == 'u')
        return this->vil_pos_u;
    return this->vil_pos_d;
}

void SolarFox::setIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}

bool SolarFox::getIsAlive(void)
{
    return this->isAlive;
}

void SolarFox::setWin(bool win)
{
    this->win = win;
}

bool SolarFox::getWin(void)
{
    return this->win;
}

void SolarFox::setShooting(int shooting)
{
    this->shooting = shooting;
}

int SolarFox::getShooting(void)
{
    return this->shooting;
}

int SolarFox::getVilainDir(char vilain)
{
    if (vilain == 'r')
        return this->vil_dir_r;
    if (vilain == 'l')
        return this->vil_dir_l;
    if (vilain == 'u')
        return this->vil_dir_u;
    return this->vil_dir_d;
}

void SolarFox::writeScore()
{
    std::ofstream myfile("save/solarfox.score");

    if (myfile.is_open()) {
        myfile << "HGSCORE=" << std::to_string(this->score);
        myfile.close();
    } else if (this->debug == true) {
        std::cout << "Unable to open file\n";
    }
}

void SolarFox::cinematique(std::string text, int x, int y, int time)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startcinematique;
    startcinematique = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::ratio<1>> dr;
    while (1) {
        dr = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startcinematique);
        if (dr.count() >= time)
            break;
        this->display->clear();
        std::vector<int> t = this->display->mapToWindow({x, y - 2});
        this->display->drawText("Solar-Fox", {t[0], t[1], 40}, colors::Colors::RED);
        t = this->display->mapToWindow({x, y});
        this->display->drawText(text, {t[0], t[1], 40}, colors::Colors::WHITE);
        t = this->display->mapToWindow({x, y + 2});
        this->display->drawText("Starting in: " + std::to_string(time - dr.count()) + " sec", {t[0], t[1], 40}, colors::Colors::RED);
        this->display->display();
    }
}

extern "C"
{
    SolarFox* createGameModule()
    {
        return new SolarFox();
    }
}

extern "C"
{
    void destroyGameModule(SolarFox* module1)
    {
        delete module1;
    }
}
