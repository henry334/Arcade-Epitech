/*
** EPITECH PROJECT, 2023
** Snake
** File description:
** Snake
*/

#include "Snake.hpp"
#include "LoadLib.hpp"
#include <iostream>

Snake::Snake()
{
    this->debug = true;
    this->maxy = 25; // 20 default
    this->maxx = 40; // 34 default
    this->last_event_val = ' ';
    this->nb_apple = 0;
    this->wait = 100;
    this->first = true;
    this->head = 'B';
    this->name = "Menu";
    this->menu = false;
    this->x_direction = 1;
    this->y_direction = 0;
    this->gamestate = GameState::RUNNING;
    this->map = this->getInitialMap("");
    this->dispBody(this->x_head, this->y_head);
    this->drawRandomApple();
}

std::vector<std::vector<int>> Snake::getInitialMap(
    const std::string &path)
{
    std::vector<std::vector<int>> maps;

    for (int i = 0; i < this->maxy; i++) {
        std::vector<int> temp;
        for (int c = 0; c < this->maxx; c++) {
            int chr = i == 0 || c == 0 || c == this->maxx - 1 || i == this->maxy - 1? '#' : ' ';
            chr = c == this->maxx / 2 && i == this->maxy / 2 ? this->head : chr;
            temp.push_back(chr);
        }
        maps.push_back(temp);
    }
    this->y_head = this->maxy / 2;
    this->x_head = this->maxx / 2;
    return maps;
}

const std::string& Snake::getName() const
{
    static const std::string name = "Snake";
    return name;
}

void Snake::start(IDisplayModule *display)
{
    this->display = display;
    this->starttSnake = std::chrono::high_resolution_clock::now();
}

void Snake::firstBack()
{
    while (1) {
        this->display->clear();
        this->display->drawSprite('Y', {0, 0}, colors::WHITE);
        std::vector<int> t = this->display->mapToWindow({10, 20});
        this->display->drawText("Press 'Space' to start", {t[0], t[1], 40}, colors::Colors::WHITE);
        this->display->display();
        this->display->fetchEvents();
        this->lastev = this->display->getEvents();
        if (this->lastev == events::A_BUTTON) {
            break;
        }
    }
}

void Snake::stop()
{
    this->gamestate = GameState::GAME_OVER;
    return;
}

void Snake::addBody(Snake_body body)
{
    if (this->Snake_bdy.empty()) {
        body.order_x = this->old_direction_x;
        body.order_y = this->old_direction_y;
    } else {
        body.order_x = this->Snake_bdy[this->Snake_bdy.size() - 1].order_x;
        body.order_y = this->Snake_bdy[this->Snake_bdy.size() - 1].order_y;
    }
}

void Snake::dispFirstBody(int x_tail, int y_tail)
{
    for (int i = 0; i < 2; i++) {
        Snake_body body;
        int x_tmp = x_tail + this->x_direction * -1;
        int y_tmp = y_tail + this->y_direction * -1;

        this->map[y_tmp][x_tmp] = 'Z';
        body.x_pos = x_tmp;
        body.y_pos = y_tmp;
        this->addBody(body);
        this->Snake_bdy[this->Snake_bdy.size()] = body;

        // Move tail position for the next body segment
        x_tail = x_tmp;
        y_tail = y_tmp;
    }
}

void Snake::dispBody(int x_tail, int y_tail)
{
    Snake_body body;
    int x_tmp = x_tail + this->x_direction * -1;
    int y_tmp = y_tail + this->y_direction * -1;

    this->map[y_tmp][x_tmp] = 'Z';
    body.x_pos = x_tmp;
    body.y_pos = y_tmp;
    this->addBody(body);
    this->Snake_bdy[this->Snake_bdy.size()] = body;
}

void Snake::bodyMove()
{
    int letter = 'Z';

    for (auto &body : this->Snake_bdy) {
        int x_old = body.second.x_pos;
        int y_old = body.second.y_pos;
        if (body.first != 0) {
            body.second.x_pos = this->Snake_bdy[body.first - 1].order_x;
            body.second.y_pos = this->Snake_bdy[body.first - 1].order_y;
        } else {
            body.second.x_pos = this->old_direction_x;
            body.second.y_pos = this->old_direction_y;
        }
        letter = this->getDirection(x_old - body.second.x_pos, y_old - body.second.y_pos);
        body.second.order_x = x_old;
        body.second.order_y = y_old;
        this->map[body.second.y_pos][body.second.x_pos] = letter;
        this->map[y_old][x_old] = ' ';
    }
}

int Snake::drawSnakeAndApple(int letter)
{
    if (letter == 'P') {
        this->display->handleMusic("./ressource/apple-crunch.ogg", false, true);
        this->drawRandomApple();
        this->nb_apple++;
        this->dispBody(this->Snake_bdy[this->Snake_bdy.size() - 1].x_pos,
            this->Snake_bdy[this->Snake_bdy.size() - 1].y_pos);
        this->wait -= 5;
    } else
        return -1;
    return 0;
}

void Snake::savePos(int x_tmp, int y_tmp)
{
    this->map[this->y_head][this->x_head] = ' ';
    this->old_direction_x = this->x_head;
    this->old_direction_y = this->y_head;
    this->x_head = x_tmp;
    this->y_head = y_tmp;
    this->map[this->y_head][this->x_head] = this->head;
}

int Snake::checkSnakeLife(int x_tmp, int y_tmp)
{
    int letter = this->map[y_tmp][x_tmp];

    this->last_event_val = this->head;
    if (letter != ' ' && letter != this->head
        || y_tmp >= this->map.size() || x_tmp >= this->map[0].size())
        if (this->drawSnakeAndApple(letter) == -1)
            return -1;
    this->savePos(x_tmp, y_tmp);
    return 0;
}

void Snake::Move(int x_tmp, int y_tmp)
{
    x_tmp += this->x_direction;
    y_tmp += this->y_direction;
    if (this->first == true) {
        this->dispFirstBody(this->x_head, this->y_head);
        this->first = false;
    }
    if (this->checkSnakeLife(x_tmp, y_tmp) == -1) {
        this->GameOver();
        return;
    }
    this->bodyMove();
}

void Snake::SnakeMoove()
{
    int y_tmp = this->y_head;
    int x_tmp = this->x_head;

    this->durationSnake = std::chrono::high_resolution_clock::now() - this->starttSnake;
    if (this->durationSnake.count() > this->wait) {
        this->Move(x_tmp, y_tmp);
        this->starttSnake = std::chrono::high_resolution_clock::now();
    }
}

void Snake::handleEvent()
{
    this->lastev = display->getEvents();
    if (this->lastev == events::UP && this->y_direction != 1 && this->last_event_val != 'V') {
        this->y_direction = -1;
        this->x_direction = 0;
        this->head = 'S';
    } else if (this->lastev == events::DOWN && this->y_direction != -1 && this->last_event_val != 'S') {
        this->y_direction = 1;
        this->x_direction = 0;
        this->head = 'V';
    } else if (this->lastev == events::RIGHT && this->x_direction != -1 && this->last_event_val != 'N') {
        this->y_direction = 0;
        this->x_direction = 1;
        this->head = 'B';
    } else if (this->lastev == events::LEFT && this->x_direction != 1 && this->last_event_val != 'B') {
        this->y_direction = 0;
        this->x_direction = -1;
        this->head = 'N';
    }
    if (this->lastev == events::QUIT)
        this->stop();
}

int Snake::getDirection(int x, int y)
{
    if (x == 0)
        return 'X';
    return 'Z';
}

void Snake::drawRandomApple()
{
    int random_x = rand() % (this->maxx - 2) + 1;
    int random_y = rand() % (this->maxy - 2) + 1;
    int chr = this->map[random_y][random_x];

    if (chr != ' ' || random_y >= this->maxy - 1 || random_x >= this->maxx - 1)
        this->drawRandomApple();
    else
        this->map[random_y][random_x] = 'P';
}

int Snake::getState()
{
    return this->gamestate;
}

void Snake::GameOver()
{
    this->writeScore();
    this->display->clear();
    this->display->drawSprite('O', {0, 0}, colors::WHITE);
    std::vector<int> t = this->display->mapToWindow({13, 20});
    this->display->drawText("Press 'P' to go back to Menu", {t[0], t[1], 40}, colors::Colors::WHITE);
    t = this->display->mapToWindow({13, 22});
    this->display->drawText("Your Score: " + std::to_string(this->nb_apple), {t[0], t[1], 40}, colors::Colors::RED);
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

void Snake::writeScore()
{
    std::ofstream myfile("save/snake.score");

    if (myfile.is_open()) {
        myfile << "HGSCORE=" << std::to_string(this->nb_apple);
        myfile.close();
    } else if (this->debug == true) {
        std::cout << "Unable to open file\n";
    }
}

void Snake::render()
{
    this->display->clear();
    this->display->drawSprite('G', {0, 0}, colors::WHITE);
    this->display->drawMap(this->map);
    this->display->drawText("Score: " + std::to_string(this->nb_apple), {0, 0, 40}, colors::Colors::WHITE);
    this->display->display();
}

void Snake::update(IDisplayModule *display)
{
    this->display = display;
    this->display->setWindowSize(this->maxx, this->maxy);
    if (this->menu == false) {
        this->firstBack();
        this->menu = true;
    }
    this->handleEvent();
    this->SnakeMoove();
}

extern "C"
{
    Snake* createGameModule()
    {
        return new Snake();
    }
}

extern "C"
{
    void destroyGameModule(Snake* module1)
    {
        delete module1;
    }
}
