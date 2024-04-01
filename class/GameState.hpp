/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** GameStart
*/

#ifndef GAMESTART_HPP_
    #define GAMESTART_HPP_

#include <cstdint>

namespace GameState
{
    enum GameStates {
        /* @brief Game is running */
        RUNNING,
        /* @brief Game is not running anymore */
        STOPPED,
        /* @brief Game is paused */
        PAUSED,
        /* @brief Game is over */
        GAME_OVER,
        /* @brief Game is won */
        GAME_WON,
        ON_GAME,
        MENU
    };

    typedef uint16_t Key;
}

#endif /* !GAMESTART_HPP_ */
