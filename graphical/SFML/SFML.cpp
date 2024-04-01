/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML(std::string name)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->havebeeno = 1;
    this->title = 32;
    this->title_height_btn = 17.5;
    this->title_width_btn = 16;
    this->libname = "SFML";
    this->window.create(sf::VideoMode(1920, 1080), name.c_str(), sf::Style::Close | sf::Style::Titlebar);
    this->window.setPosition(sf::Vector2i((desktop.width - 1920) / 2, (desktop.height - 1080) / 2));
    this->window.setFramerateLimit(60);
    this->window.setKeyRepeatEnabled(true);
    this->font.loadFromFile("./ressource/ttf/RobotoCondensed-Light.ttf");
    return;
}

SFML::SFML()
{
    this->havebeeno = 0;
}

SFML::~SFML()
{
    if (this->havebeeno == 0)
        return;
    this->window.close();
}

void SFML::clear()
{
    this->window.clear();
}

void SFML::display()
{
    window.display();
}

void SFML::drawSprite(int type, const std::vector<float> &pos, colors::Color color)
{
    (void)(color);
    if (this->sprites.count(type) <= 0) {
        std::unique_ptr<Sprite>(sp) = std::make_unique<Sprite>();
        sp->textu.loadFromFile(this->maps[type].c_str());
        sp->sfsprite.setTexture(sp->textu);
        this->sprites[type] = std::move(sp);
    }
    this->sprites[type]->sfsprite.setPosition(pos[0], pos[1]);
    window.draw(this->sprites[type]->sfsprite);
}

void SFML::drawText(const std::string &text, const std::vector<int> &pos, colors::Color color)
{
    int p = 40;
    if (pos.size() >= 3)
        p = pos[2];
    this->texts.setFont(font);
    this->texts.setString(text);
    this->texts.setCharacterSize(p);
    this->texts.setPosition(pos[0], pos[1]);
    this->texts.setFillColor(this->color[color]);
    window.draw(texts);
}

void SFML::drawButton(const std::string &text, const std::vector<int> &poss, const std::vector<int> &sizes, colors::Color color)
{
    std::vector<int> all = this->mapToWindow({poss[0], poss[1], sizes[0], sizes[1]});
    std::vector<float> pos = {static_cast<float>(all[0]), static_cast<float>(all[1]), static_cast<float>(all[2]), static_cast<float>(all[3])};
    int word = text.size();
    this->drawSprite('b', pos, color);
    if (strlen(text.c_str()) > 0 && text[0] != '/') {
        drawText(text, {(all[0] + all[3] / 2) - word * 15, all[1] + 37, poss[2]}, color);
    }
}

void SFML::handleMusic(const std::string &path, bool loop, bool play)
{
    static sf::Music music;

    if (play) {
        if (!music.openFromFile(path)) {
            std::cerr << "Error loading music file: " << path << std::endl;
            return;
        }

        music.setLoop(loop);
        music.setVolume(50);
        music.play();
    } else {
        music.stop();
    }
}

bool SFML::isMousePressed()
{
    if (this->event.type == sf::Event::MouseButtonPressed) {
        return true;
    }
    return false;
}

const std::string &SFML::getSpritePath(int type) const
{
    return this->maps.at(type);
}

void SFML::fetchEvents()
{
    this->window.pollEvent(this->event);
    switch (this->event.type) {
        case sf::Event::Closed:
            this->aenv = events::Events::QUIT;
            break;
        case sf::Event::MouseButtonPressed:
            this->aenv = this->eventmouse.count(this->event.mouseButton.button) > 0 ?
                this->eventmouse.at(this->event.mouseButton.button) : events::Events::NONE;
            break;
        case sf::Event::KeyPressed:
            this->aenv = this->eventkey.count(this->event.key.code) > 0 ?
                this->eventkey.at(this->event.key.code) : events::Events::NONE;
            break;
        default:
            this->aenv = events::Events::NONE;
            break;
    }
}

std::vector<int> SFML::getMousePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return {mousePos.x, mousePos.y};
}

events::Event SFML::getEvents()
{
    return this->aenv;
}

void SFML::setWindowSize(int width, int height)
{
    width *= this->getTileSize();
    height *= this->getTileSize();
    width = width > 1920 ? 1920 : width;
    height = height > 1080 ? 1080 : height;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->window.setSize(sf::Vector2u(width, height));
    sf::FloatRect visibleArea(0.f, 0.f, width, height);
    this->window.setView(sf::View(visibleArea));
    this->window.setPosition(sf::Vector2i((desktop.width - width) / 2, (desktop.height - height) / 2));
}

extern "C"
{
    ADisplay* createDisplayModule(char *name)
    {
        if (name != NULL)
            return new SFML("Arcade SFML");
        else
            return new SFML();
    }
}

extern "C"
{
    void destroyDisplayModule(ADisplay* module1)
    {
        delete module1;
    }
}