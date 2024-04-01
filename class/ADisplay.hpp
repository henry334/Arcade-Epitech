/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** ADisplay
*/

#ifndef ADISPLAY_HPP_
#define ADISPLAY_HPP_

#include "IDisplay.hpp"

class ADisplay : public IDisplayModule {
    public:
        const std::string getLibName() const override;
        int getTileSize() const override;
        void clear() override = 0;
        const std::vector<int> mapToWindow(const std::vector<int> &coord) const override;
        void display() override = 0;
        void drawSprite(int type, const std::vector<float> &pos, colors::Color color) override = 0;
        void drawMap(const std::vector<std::vector<int>> &map) override;
        void drawText(const std::string &text, const std::vector<int> &pos, colors::Color color) override = 0;
        void drawButton(const std::string &text, const std::vector<int> &pos, const std::vector<int> &size, colors::Color color) override = 0;
        const std::string &getSpritePath(int type) const override = 0;
        bool isMousePressed() override = 0;
        void fetchEvents() override = 0;
        std::vector<int> getMousePos() override = 0;
        events::Event getEvents() override = 0;
        void handleMusic(const std::string &path, bool loop, bool play) override = 0;
        virtual void setWindowSize(int width, int height) override = 0;
        ADisplay();
        ~ADisplay() = default;
    protected:
        int havebeeno;
        float title_width_btn;
        float title_height_btn;
        int title;
        std::string lastbutton_clicked;
        std::string libname;
        events::Event aenv;
};

#endif /* !ADISPLAY_HPP_ */
