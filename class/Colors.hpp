/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Colors
*/

#pragma once

#include <cstdbool>
#include <cstdint>

namespace colors {

    /**
     * @brief First octet: foreground color
     *        Second octet: style
     */
    enum Colors {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BOLD,
        UNDERLINE,
        BLINK,
        REVERSE,
        HIDDEN
    };

    typedef uint16_t Color;
}
