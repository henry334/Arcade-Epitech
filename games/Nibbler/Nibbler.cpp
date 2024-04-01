/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Nibller
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    this->endlevel = 25;
    this->life = 2;
    this->nufapple = 3;
    this->debug = false;
    this->Level = 1;
    this->appleEat = 0;
    this->maxy = 23; // 20 default
    this->maxx = 42; // 34 default
    this->last_event_val = ' ';
    this->score = 0;
    this->head = 'B';
    this->direction_x = 1;
    this->direction_y = 0;
    this->time = 500;
    this->gamestate = GameState::RUNNING;
}

void Nibbler::printMapForGrap()
{
    for (auto p : this->map) {
        for (auto x : p) {
            printf("%c", x);
        }
        printf("\n");
    }
}

const std::string& Nibbler::getName() const
{
    static const std::string name = "Nibbler";
    return name;
}

void Nibbler::start(IDisplayModule *display)
{
    this->display = display;
    this->starttnibller = std::chrono::high_resolution_clock::now();
    this->timetnibller = std::chrono::high_resolution_clock::now();
    this->startLevel(false);
}

void Nibbler::stop()
{
    this->gamestate = GameState::GAME_OVER;
    return;
}

void Nibbler::startLevel(bool restart)
{
    if (restart == false && this->Level % 2 == 0)
        this->nufapple++;
    this->appleEat = 0;
    std::map<std::size_t, nibbler_body> empty;
    this->nibbler_bdy = empty;
    this->map = this->getInitialMap("");
    this->addbody(this->x_head, this->y_head);
    this->addbody(this->x_head, this->y_head);
    this->addbody(this->x_head, this->y_head);
    for (int x = 0; x < this->nufapple; x++) {
        this->placeApple();
    }
    colors::Color c = colors::GREEN;
    if (restart == true)
        c = colors::RED;
    this->cinematique("LEVEL " + std::to_string(this->Level)
        + " LIFE: " + std::to_string(this->life), 15, 10, 2, c);
}

void Nibbler::update(IDisplayModule *display)
{
    this->display = display;
    this->display->setWindowSize(this->maxx, this->maxy);
    this->handleEvent();
    this->nibblerMoove();
    std::chrono::duration<double, std::milli> dr = std::chrono::high_resolution_clock::now() - this->timetnibller;
    if (dr.count() > 1000) {
        this->time--;
        if (this->time == 0) {
            this->GameOver();
        }
        this->timetnibller = std::chrono::high_resolution_clock::now();
    }
}

void Nibbler::render()
{
    this->display->clear();
    this->display->drawSprite('?', {0, 0}, colors::WHITE);
    this->display->drawMap(this->map);
    this->display->drawText("Score: " + std::to_string(this->score), {0, 0, 40}, colors::Colors::RED);
    this->display->drawText("Time: " + std::to_string(this->time),
        {this->display->mapToWindow({10, 0})[0], 0, 40}, colors::Colors::RED);
    this->display->drawText("Life: " + std::to_string(this->life),
        {this->display->mapToWindow({20, 0})[0], 0, 40}, colors::Colors::RED);
    this->display->drawText("Level: " + std::to_string(this->Level),
        {this->display->mapToWindow({30, 0})[0], 0, 40}, colors::Colors::RED);
    this->display->display();
}

void Nibbler::addbody(int x_tail, int y_tail)
{
    nibbler_body bd;
    int temp_y = y_tail;
    int temp_x = x_tail;
    temp_y += this->direction_y * -1;
    temp_x += this->direction_x * -1;
    this->map[temp_y][temp_x] = 'Z';
    bd.x_pos = temp_x;
    bd.y_pos = temp_y;
    if (this->nibbler_bdy.size() == 0) {
        bd.order_x = this->head_old_x;
        bd.order_y = this->head_old_y;
    } else {
        bd.order_x = this->nibbler_bdy[this->nibbler_bdy.size() -1].order_x;
        bd.order_y = this->nibbler_bdy[this->nibbler_bdy.size() -1].order_y;
    }
    this->nibbler_bdy[this->nibbler_bdy.size()] = bd;
    if (this->debug == true)
        printf("Body size=%d\n", this->nibbler_bdy.size());
}

void Nibbler::bodyMoove()
{
    int chr = 'Z';
    for (auto &body : this->nibbler_bdy) {
        int old_x = body.second.x_pos;
        int old_y = body.second.y_pos;
        if (body.first != 0) {
            body.second.x_pos = this->nibbler_bdy[body.first - 1].order_x;
            body.second.y_pos = this->nibbler_bdy[body.first - 1].order_y;
        } else {
            body.second.x_pos = this->head_old_x;
            body.second.y_pos = this->head_old_y;
        }
        chr = this->getSpriteDir(old_x - body.second.x_pos, old_y - body.second.y_pos);
        body.second.order_x = old_x;
        body.second.order_y = old_y;
        this->map[body.second.y_pos][body.second.x_pos] = chr;
        this->map[old_y][old_x] = ' ';
    }
}

bool Nibbler::canMoove(int x, int y)
{
    if (this->map[this->y_head + y][this->x_head + x] == '!')
        return false;
    return true;
}

void Nibbler::mooveAuto(int x, int y)
{
    if (this->map[this->y_head - x][this->x_head - y] != '!') {
        this->direction_x = y * -1;
        this->direction_y = x * -1;
        this->head = this->getHead(this->direction_x, this->direction_y);
        this->checkifalive(this->x_head - y, this->y_head - x);
    } else if (this->map[this->y_head + x][this->x_head + y] != '!') {
        this->direction_x = y;
        this->direction_y = x;
        this->head = this->getHead(this->direction_x, this->direction_y);
        this->checkifalive(this->x_head + y, this->y_head + x);
    }
}

bool Nibbler::checkStuck(int chr, int temp_x, int temp_y)
{
    int y = this->direction_y;
    int x = this->direction_x;
    int block = 0;
    if (chr == 'X' || chr == 'Z') {
        if (this->life > 0) {
            this->life--;
            this->score -= this->appleEat;
            this->startLevel(true);
            return true;
        }
        return false;
    }
    if (this->map[this->y_head - x][this->x_head - y] == '!') {
        block++;
    }
    if (this->map[this->y_head + x][this->x_head + y] == '!') {
        block++;
    }
    if (chr == '!') {
        block++;
        if (block == 3)
            return false;
        else
            this->mooveAuto(x, y);
    }
    return true;
}

void Nibbler::makeItMoove(int temp_x, int temp_y)
{
    this->map[this->y_head][this->x_head] = ' ';
    this->head_old_x = this->x_head;
    this->head_old_y = this->y_head;
    this->x_head = temp_x;
    this->y_head = temp_y;
    this->map[this->y_head][this->x_head] = this->head;
    this->bodyMoove();
    this->checkAllApl();
}

void Nibbler::haveEatApple(int x, int y)
{
    this->appleEat++;
    if (debug == true) {
        this->printMapForGrap();
        printf("%d appleEat y=%d x=%d\n", this->appleEat, x, y);
    }
    this->display->handleMusic("./ressource/apple-crunch.ogg", false, true);
    this->score++;
    this->addbody(this->nibbler_bdy[this->nibbler_bdy.size() -1].x_pos,
    this->nibbler_bdy[this->nibbler_bdy.size() -1].y_pos);
}

bool Nibbler::checkifalive(int temp_x, int temp_y)
{
    int chr = this->map[temp_y][temp_x];
    this->last_event_val = this->head;
    if (chr != ' ' && chr != this->head
        || temp_y >= this->map.size() || temp_x >= this->map[0].size()) {
        if (chr == 'P') {
            this->haveEatApple(temp_x, temp_y);
        } else
            return this->checkStuck(chr, temp_y, temp_x);
    }
    this->makeItMoove(temp_x, temp_y);
    return true;
}

void Nibbler::nibblerMoove()
{
    int wait = 100;
    int temp_y = this->y_head;
    int temp_x = this->x_head;
    this->duration_nibller = std::chrono::high_resolution_clock::now() - this->starttnibller;
    if (this->direction_y == -1 || this->direction_y == 1)
        wait = 117;
    if (this->duration_nibller.count() > wait) {
        temp_y += this->direction_y;
        temp_x += this->direction_x;
        if (this->checkifalive(temp_x, temp_y) == false) {
            this->GameOver();
            return;
        }
        this->starttnibller = std::chrono::high_resolution_clock::now();
    }
}

void Nibbler::handleEvent()
{
    this->lastev = display->getEvents();
    int dy = this->direction_y;
    int dx = this->direction_x;
    int hd = this->head;
    if (this->lastev == events::UP && this->direction_y != 1 && this->last_event_val != 'V') {
        //UP
        this->direction_y = -1;
        this->direction_x = 0;
        this->head = 'S';
    } else if (this->lastev == events::DOWN && this->direction_y != -1 && this->last_event_val != 'S') {
        //DOWN
        this->direction_y = 1;
        this->direction_x = 0;
        this->head = 'V';
    } else if (this->lastev == events::RIGHT && this->direction_x != -1 && this->last_event_val != 'N') {
        //RIGHT
        this->direction_y = 0;
        this->direction_x = 1;
        this->head = 'B';
    } else if (this->lastev == events::LEFT && this->direction_x != 1 && this->last_event_val != 'B') {
        //LEFT
        this->direction_y = 0;
        this->direction_x = -1;
        this->head = 'N';
    }
    if (this->canMoove(this->direction_x, this->direction_y) == false) {
        this->head = hd;
        this->direction_x = dx;
        this->direction_y = dy;
    }
}

int Nibbler::getSpriteDir(int x, int y)
{
    if (x == 0) {
        return 'X';
    }
    return 'Z';
}

int Nibbler::getHead(int x, int y)
{
    if (x == 1) {
        return 'B';
    } else if (x == -1)
        return 'N';
    if (y == -1) {
        return 'S';
    } else if (y == 1)
        return 'V';
    return 'V';
}

void Nibbler::checkAllApl()
{
    if (this->appleEat >= this->nufapple) {
        this->Level++;
        this->startLevel(false);
    }
}

void Nibbler::placeApple()
{
    int random_x = rand() % (this->maxx - 2) + 1;
    int random_y = rand() % (this->maxy - 2) + 1;
    int chr = this->map[random_y][random_x];
    if (chr != ' ' || random_y >= this->maxy - 1 || random_x >= this->maxx - 1) {
        if (this->debug == true)
            printf("New apple going to be gen %d %d\n", random_y, random_x);
        this->placeApple();
    } else {
        this->map[random_y][random_x] = 'P';
        if (this->debug == true)
            printf("Apple spawned at y:%d x:%d\n", random_y, random_x);
    }
}

int Nibbler::getState()
{
    return this->gamestate;
}

int Nibbler::addWall(int chr)
{
    int m = this->Level;
    if (chr != ' ')
        return chr;
    if (m >= this->endlevel)
        m = this->endlevel - 1;
    //std::srand(std::time(nullptr));
    int p = rand() % ((this->endlevel + 1) - m);
    if (p == 0) {
        return '!';
    }
    return chr;
}

std::vector<std::vector<int>> Nibbler::getInitialMap(
    const std::string &path)
{
    std::vector<std::vector<int>> maps;
    for (int i = 0; i < this->maxy; i++) {
        std::vector<int> temp;
        for (int c = 0; c < this->maxx; c++) {
            int chr = i == 0 || c == 0 || c == this->maxx - 1 || i == this->maxy - 1? '!' : ' ';
            chr = c == this->maxx / 2 && i == this->maxy / 2 ? this->head : chr;
            temp.push_back(this->addWall(chr));
        }
        maps.push_back(temp);
    }
    this->y_head = this->maxy / 2;
    this->x_head = this->maxx / 2;
    return maps;
}

void Nibbler::GameOver()
{
    this->writeScore();
    this->display->clear();
    std::vector<int> t = this->display->mapToWindow({5, 2});
    this->display->drawText("GAME OVER", {t[0], t[1], 40}, colors::Colors::RED);
    t = this->display->mapToWindow({5, 4});
    this->display->drawText("Presse 'P' to go back to Menu", {t[0], t[1], 40}, colors::Colors::WHITE);
    t = this->display->mapToWindow({5, 6});
    this->display->drawText("Your Score: " + std::to_string(this->score), {t[0], t[1], 40}, colors::Colors::RED);
    t = this->display->mapToWindow({5, 8});
    this->display->drawText("Time Left: " + std::to_string(this->time), {t[0], t[1], 40}, colors::Colors::WHITE);
    t = this->display->mapToWindow({5, 10});
    this->display->drawText("Level: " + std::to_string(this->Level), {t[0], t[1], 40}, colors::Colors::RED);
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

void Nibbler::writeScore()
{
    std::ofstream myfile("save/nibbler.score");

    if (myfile.is_open()) {
        myfile << "HGSCORE=" << std::to_string(this->score);
        myfile.close();
    } else if (this->debug == true) {
        std::cout << "Unable to open file\n";
    }
}

void Nibbler::cinematique(std::string text, int x, int y, int time, colors::Color c)
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
        this->display->drawText("NIBBLER", {t[0], t[1], 40}, colors::Colors::RED);
        t = this->display->mapToWindow({x, y});
        this->display->drawText(text, {t[0], t[1], 40}, c);
        t = this->display->mapToWindow({x, y + 2});
        this->display->drawText("Starting in: " + std::to_string(time - dr.count()) + " sec", {t[0], t[1], 40}, colors::Colors::RED);
        this->display->display();
    }
    
}

extern "C"
{
    Nibbler* createGameModule()
    {
        return new Nibbler();
    }
}

extern "C"
{
    void destroyGameModule(Nibbler* module1)
    {
        delete module1;
    }
}