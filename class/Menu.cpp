/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Menu
*/

#include "Menu.hpp"
#include "LoadLib.hpp"

Menu::Menu()
{
    this->pseudo = "USERNAME";
    this->name = "Menu";
    this->gamestate = GameState::MENU;
    this->lastbutton_clicked = "";
}

const std::string &Menu::getName() const
{
    return this->name;
}

void Menu::startgame(std::string gamestr)
{
    LoadLib loader;
    Core *util = this->getCore();
    this->gameon = gamestr;
    this->lib_handlegame = loader.lib_handle("./lib/" + gamestr + ".so");
    if (this->lib_handlegame == nullptr) {
        this->util.setExitCode(84);
        return;
    }
    this->game = loader.getLibgame(this->lib_handlegame);
    if (this->game == nullptr) {
        util->setExitCode(84);
        return;
    }

    this->game->start(this->display);
}

void Menu::start(IDisplayModule *dis)
{
    (void)(dis);
    LoadLib loader;
    char *temp = strdup("topass");
    this->util.setIdisplay(loader.getLib(this->util.getlibhandle(), temp));
    if (this->util.getIdisplay() == nullptr) {
        this->util.setExitCode(84);
        return;
    }
    free(temp);
    this->display = this->util.getIdisplay();
    std::cout << "Using: "<< this->display->getLibName() << std::endl;
    this->update(nullptr);

    if (loader.destroyLib(this->util.getIdisplay(), this->util.getlibhandle()) != 0) {
        this->util.setExitCode(84);
        return;
    }
    
    return;
}

void Menu::stop()
{
    this->gamestate = GameState::STOPPED;
    return;
}

int Menu::changelib()
{
    if (this->util.changelib(this->libs) == 84)
        return 84;
    this->display = this->util.getIdisplay();
    this->lib_handle = this->util.getlibhandle();
    return 0;
}

void Menu::checkBtnMouse()
{
    this->buttonclicked();
    if (this->lastbutton_clicked == this->utils.toCap(this->pseudo)) {
        this->changePseudo();
    }
    if (this->lastbutton_clicked == "EXIT")
        this->stop();
    for (auto button : this->buttons) {
        if (button.second.point_so.size() == 0)
            continue;
        if (this->lastbutton_clicked == button.second.name || this->gamestate == GameState::ON_GAME) {
            this->gamestate != GameState::ON_GAME ? this->startgame(button.second.point_so) : void();
            this->game->update(this->display);
            this->game->render();
            this->gamestate = GameState::ON_GAME;
            break;
        }
    }
    if (this->gamestate == GameState::ON_GAME &&
        (this->game->getState() == GameState::GAME_WON || this->game->getState() == GameState::GAME_OVER)) {
            this->lastev = events::Events::BACK;
            this->lastbutton_clicked = "";
            this->getData();
            this->handleEvent();
    }
    this->lastbutton_clicked = "";
}

void Menu::handleEvent()
{
    LoadLib loader;
    if (GameState::GameStates::MENU == this->gamestate) {
        this->render();
    }
    if (events::Events::QUIT == this->lastev)
        this->stop();
    if (events::Events::G_CHANGE == this->lastev && this->gamestate == GameState::ON_GAME)
        this->nextGame();
    if (events::Events::BACK == this->lastev) {
        if (this->gamestate != GameState::MENU) {
            loader.destroyLibgame(this->game, this->lib_handlegame);
            this->gamestate = GameState::MENU;
            this->display->setWindowSize(1920, 1080);
            this->gameon = "";
        }
    }
    if (events::Events::I_CHANGE == this->lastev) {
        if (this->changelib() == 84)
            this->stop();
    }
    this->checkBtnMouse();
    return;
}

void Menu::displayHighScores()
{
    int p = 25;
    for (auto h : this->games_highscore) {
        std::vector<int> t = this->display->mapToWindow({0, p, 0, 0});
        std::string name = "HScore_" + this->utils.toCap(h.first) + ": ";
        this->display->drawText(name + std::to_string(h.second),
        {t[0], t[1], 50}, colors::CYAN);
        p += 2;
    }
}

void Menu::render()
{
    this->display->clear();
    int p = 1;
    display->drawSprite('W', {0, 0}, colors::Colors::CYAN);
    for (auto lib : this->libs) {
        colors::Color c = colors::Colors::CYAN;
        std::string name = this->utils.parser(lib.first, '_')[1];
        name = this->utils.parser(name, '.')[0];
        if (this->display->getLibName() == this->utils.toCap(name))
            c = colors::Colors::RED;
        int k = this->display->mapToWindow({0, p, 0, 0})[1];
        display->drawText(this->utils.toCap(name), {5, k, 50}, c);
        p += 3;
    }
    this->draw_allbtn();
    this->displayHighScores();
    this->display->display();
    return;
}

int Menu::getState()
{
    return 1;
}

std::vector<std::vector<int>> Menu::getInitialMap(const std::string &path)
{
    return {{0}};
}

std::string Menu::mouseonbutton()
{
    for (auto val : this->buttons) {
        std::vector<int> all = this->display->mapToWindow({val.second.vect[0], val.second.vect[1], val.second.rect[0], val.second.rect[1]});
        int x = this->display->getMousePos()[0];
        int y = this->display->getMousePos()[1];
        if (x >= all[0] &&
            x <= all[0] + all[3] &&
            y >= all[1] &&
            y <= all[1] + all[2]) {
                val.second.col = colors::Colors::RED;
                return val.first;
        }
    }
    return "";
}

bool Menu::buttonclicked()
{
    std::string b = mouseonbutton();
    if (this->lastev == events::Events::MOUSE_LEFT) {
        if (b.size() > 0 && b != this->lastbutton_clicked) {
            this->lastbutton_clicked = b;
            this->lastev == events::Events::BUTTON_CLICKED;
            return true;
        }
    }
    return false;
}

void Menu::draw_allbtn()
{
    for (auto val : this->buttons) {
        colors::Color c = val.second.col;
        if (val.first == this->mouseonbutton()) {
            c = colors::Colors::RED;
        }
        display->drawButton(val.first, val.second.vect, val.second.rect, c);
    }
    return;
}

void Menu::creatbtn(std::string name, std::vector<int> vect, std::vector<int> rect, colors::Color col)
{
    std::string capname = this->utils.toCap(name);
    btn button;
    button.name = capname;
    if (this->utils.isAllUpperCase(name) == false) {
        button.point_so = "arcade_" + name;
    } else
        button.point_so = "";
    button.col = col;
    button.rect = rect;
    button.vect = vect;
    this->buttons[capname] = button;
    return;
}

void Menu::update(IDisplayModule *r)
{
    (void)(*r);
    int place = 1;
    int loop = 0;
    for (auto gamename : this->gameslib) {
        std::string name = this->utils.parser(gamename.first, '_')[1];
        name = this->utils.parser(name, '.')[0];
        this->games_highscore[name] = 0;
        creatbtn(name, {19, place, 50}, {8, 32, 0, 0}, colors::Colors::CYAN);
        loop++;
        place += 8;
        if (loop == 3)
            break;
    }
    this->getData();
    creatbtn("EXIT", {19, place, 50}, {8, 32, 0, 0}, colors::Colors::CYAN);
    creatbtn(this->utils.toCap(this->pseudo), {44, 1, 50}, {8, 32, 0, 0}, colors::Colors::CYAN);
    while (this->gamestate != GameState::STOPPED) {
        this->display->fetchEvents();
        this->lastev = this->display->getEvents();
        this->handleEvent();
    }
}

Core *Menu::getCore()
{
    return &this->util;
}

void Menu::setLibs(std::map<std::string, std::size_t> libs,
    std::map<std::string, std::size_t> games)
{
    this->gameslib = games;
    this->libs = libs;
}

void Menu::getData()
{
    std::string t = this->util.readFile("./save/data.conf");
    if (t.size() == 0)
        return;
    std::vector<std::string> l = this->utils.parser(t, '\n');
    if (l.size() < 1)
        return;
    std::vector<std::string> k = this->utils.parser(l[0], '=');
    if (k.size() >= 2)
        this->pseudo = k[1];
    for (auto &g : this->games_highscore) {
        t = this->util.readFile("./save/" + g.first + ".score");
        if (t.size() == 0)
            continue;
        std::vector<std::string> l = this->utils.parser(t, '=');
        if (l.size() < 2)
            return;
        if (g.second < std::atoi(l[1].c_str())) {
            g.second = std::atoi(l[1].c_str());
            this->writeData("./save/" + g.first + ".score", "HSCORE="+l[1]);
        } else
            this->writeData("./save/" + g.first + ".score", "HSCORE="+std::to_string(g.second));
    }
}

void Menu::changePseudoTh(std::string *pseudo, std::string *val, std::string *oldval, int *index)
{
    this->buttons.erase(*oldval);
    *index = 0;
    *pseudo = *val;
    *oldval = *pseudo;
}

bool Menu::changePseudoSec(std::string *pseudo, int *index, std::string *val, std::string *oldval, btn bt)
{
    int mode = 0;
    std::vector<std::string> alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    this->lastev = display->getEvents();
    if (this->lastev == events::Events::QUIT) {
        this->pseudo = *val;
        return false;
    }
    if (this->lastev == events::Events::A_BUTTON) {
        this->changePseudoTh(pseudo, val, oldval, index);
        mode = 1;
    }
    if (this->lastev == events::Events::UP) {
        if (*index + 1 > 25) {
            this->changePseudoTh(pseudo, val, oldval, index);
        } else
            *index += 1;
        mode = 1;
    } else if (this->lastev == events::Events::DOWN) {
        if (*index - 1 < 0) {
            this->changePseudoTh(pseudo, val, oldval, index);
        } else
            *index -= 1;
        mode = 1;
    }
    if (mode == 1) {
        this->buttons.erase(*oldval);
        *val = *pseudo + alphabet.at(*index);
        this->buttons[*val] = bt;
        *oldval = *val;
    }
    return true;
}

void Menu::changePseudo()
{
    int index = 0;
    bool exit = true;
    std::string pseudo = "";
    std::string oldval = this->utils.toCap(this->pseudo);;
    std::string val = "A";
    btn bt = this->buttons[oldval];
    this->buttons.erase(oldval);
    this->buttons[val] = bt;
    oldval = val;
    while (exit) {
        display->fetchEvents();
        exit = this->changePseudoSec(&pseudo, &index, &val, &oldval, bt);
        this->render();
    }
    std::string text = "PSEUDO=" + this->utils.toCap(this->pseudo);
    this->writeData("save/data.conf", text);
}

void Menu::writeData(std::string path, std::string text)
{
    std::ofstream myfile;
    myfile.open(path.c_str());

    if (myfile.is_open()) {
        myfile << text;
        myfile.close();
    } else {
        std::cout << "Unable to open file\n";
    }
}

void Menu::nextGame()
{
    std::map<std::size_t, std::string> games;
    for (auto game : this->gameslib)
        games[game.second] = game.first;
    LoadLib loader;
    std::size_t index = 0;
    std::string game;
    std::size_t t = this->gameslib.size();
    std::string actual_game = this->gameon + ".so";
    if (this->gameslib[actual_game] + 1 < t)
        index = this->gameslib[actual_game] + 1;
    game = this->utils.parser(games[index], '.')[0];
    loader.destroyLibgame(this->game, this->lib_handlegame);
    this->startgame(game);
    this->gamestate = GameState::ON_GAME;
}