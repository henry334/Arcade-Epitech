/*
** EPITECH PROJECT, 2021
** epitech
** File description:
** the_code
*/

#include "ADisplay.hpp"

ADisplay::ADisplay()
{
    return;
}

const std::string ADisplay::getLibName() const
{
    return this->libname;
}

int ADisplay::getTileSize() const
{
    return this->title;
}

void ADisplay::drawMap(const std::vector<std::vector<int>> &map)
{
    std::vector<float> pos = {1.f, 1.f, 1.f, 1.f};
    for (std::size_t c = 0; c < map.size(); c++) {
        pos[1] = c * this->getTileSize();
        pos[2] = map.size();
        for (std::size_t i = 0; i < map[c].size(); i++) {
            pos[0] = i * this->getTileSize();
            pos[3] = map[c].size();
            this->drawSprite(map[c][i], pos, colors::WHITE);
        }
    }
}

const std::vector<int> ADisplay::mapToWindow(const std::vector<int> &coord) const
{
    std::vector<int> vect(coord);

    vect[0] *= this->title;
    vect[1] *= this->title;
    if (vect.size() > 2) {
        vect[2] *= this->title_height_btn;
        vect[3] *= this->title_width_btn;
    }
    if (vect.size() > 4) {
        vect[4] *= title;
        vect[5] *= title;
    }
    return vect;
}