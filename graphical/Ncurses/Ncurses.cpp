/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

NCurses::NCurses(std::string name)
{
    this->havebeeno = 1;
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    this->title = 1;
    this->title_height_btn = 1;
    this->title_width_btn = 1;
    this->libname = "NCURSES";
    this->prev_x = 0;
    this->prev_y = 0;
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    return;
}

NCurses::NCurses()
{
    this->havebeeno = 0;
}

NCurses::~NCurses()
{
    if (this->havebeeno == 0)
        return;
    endwin();
}

void NCurses::clear()
{
    erase();
}

void NCurses::display()
{
    refresh();
}

void NCurses::drawMap(const std::vector<std::vector<int>> &map)
{
    std::vector<float> pos = {1.f, 1.f, 1.f, 1.f};
    for (std::size_t c = 0; c < map.size(); c++) {
        pos[1] = c * this->getTileSize();
        pos[2] = map.size();
        for (std::size_t i = 0; i < map[c].size(); i++) {
            pos[0] = i * this->getTileSize();
            pos[3] = map[c].size();
            if (this->chartocolor.count(map[c][i]) > 0) {
                this->drawSprite(map[c][i], pos, this->chartocolor[map[c][i]]);
            } else
                this->drawSprite(map[c][i], pos, colors::WHITE);
        }
    }
}

void NCurses::drawSprite(int type, const std::vector<float> &pos, colors::Color color)
{
    std::vector<int> all = this->mapToWindow({static_cast<int>(pos[0]), static_cast<int>(pos[1]), 0, 0});
    double y = getmaxy(stdscr);
    int col = 7;
    if (this->getcolor.count(color) > 0)
        col = this->getcolor.at(color);
    attron(COLOR_PAIR(col));
    mvprintw(pos[1], pos[0], this->maps[type].c_str());
    attroff(COLOR_PAIR(col));
}

void NCurses::drawText(const std::string &text, const std::vector<int> &pos, colors::Color color)
{
    int col = 7;
    if (this->getcolor.count(color) > 0)
        col = this->getcolor.at(color);
    attron(COLOR_PAIR(col));
    mvprintw(pos[1], pos[0], text.c_str());
    attroff(COLOR_PAIR(col));
}

void NCurses::drawButton(const std::string &text, const std::vector<int> &poss, const std::vector<int> &sizes, colors::Color color)
{
    std::vector<int> all = this->mapToWindow({poss[0], poss[1], sizes[0], sizes[1]});
    int height = all[2];
    int word = text.size();
    int width = all[3];
    if (width % 2 == 0)
        width--;
    if (height % 2 == 0)
        height--;
    attron(COLOR_PAIR(this->getcolor.at(color)));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((j == 0 || j == width - 1) && (i == 0 || i == height - 1)) {
                mvprintw(all[1] + i, all[0] + j, "+");
            } else if ((i == 0 || i == height - 1) && (j != 0 && j != width - 1)) {
                mvprintw(all[1] + i, all[0] + j, "-");
            } else if (j == 0 || j == width - 1) {
                mvprintw(all[1] + i, all[0] + j, "|");
            } else {
                mvprintw(all[1] + i, all[0] + j, " ");
            }
        }
    }
    attroff(COLOR_PAIR(this->getcolor.at(color)));
    if (word > 0 && text[0] != '/') {
        drawText(text, {all[0] + (width / 2) - word / 2, all[1] + (height / 2)}, color);
    }
}

void NCurses::handleMusic(const std::string &path, bool loop, bool play)
{
    (void)(path);
    (void)(loop);
    (void)(play);
}

const std::string &NCurses::getSpritePath(int type) const
{
    return this->maps.at(type);
}

bool NCurses::isMousePressed()
{
    if (ch == KEY_MOUSE) {
        if (getmouse(&this->event) == OK) {
            return true;
        }
    }
    return false;
}

void NCurses::fetchEvents()
{
    getmaxyx(stdscr, this->wind_y, this->wind_x);
    this->ch = getch();
    if (ch == KEY_MOUSE) {
        if (getmouse(&this->event) == OK) {
            this->aenv = this->eventtype[this->event.bstate];
            this->prev_x = this->event.x;
            this->prev_y = this->event.y;
            return;
        }
    }
    if (eventtype.count(ch) > 0) {
        this->aenv = this->eventtype[ch];
    } else
        this->aenv = events::Events::NONE;
}

std::vector<int> NCurses::getMousePos()
{
    return {this->prev_x, this->prev_y};
}

void NCurses::setWindowSize(int width, int height)
{
    (void)(width);
    (void)(height);
}

events::Event NCurses::getEvents()
{
    return this->aenv;
}

extern "C"
{
    NCurses* createDisplayModule(char *name)
    {
        if (name != NULL)
            return new NCurses("NCurses");
        else
            return new NCurses();
    }
}

extern "C"
{
    void destroyDisplayModule(NCurses* module1)
    {
        delete module1;
    }
}