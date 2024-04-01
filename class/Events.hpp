/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Events
*/

#pragma once

#include <cstdint>

namespace events
{
    enum Events {
        NONE = 0,
        QUIT = 0b1 << 0,
        MOUSE_MOVE = 0b1 << 1,
        MOUSE_CLICK = 0b1 << 2, // Triggered when a mouse button is just pressed
        MOUSE_LEFT = 0b1 << 3, // Triggered when the left mouse button is pressed
        MOUSE_RIGHT = 0b1 << 4, // Triggered when the right mouse button is pressed
        A_BUTTON = 0b1 << 5,
        B_BUTTON = 0b1 << 6,
        UP = 0b1 << 7,
        DOWN = 0b1 << 8,
        LEFT = 0b1 << 9,
        RIGHT = 0b1 << 10,
        BACK = 0b1 << 11,
        BUTTON_CLICKED,
        G_CHANGE,
        I_CHANGE
    };

    typedef uint16_t Event;
}
