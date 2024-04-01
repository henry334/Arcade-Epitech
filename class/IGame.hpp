/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGame
*/

#pragma once

#include "IDisplay.hpp"
#include <string>

/**
 * @brief Interface for a game
 */
class IGame {
public:
    virtual ~IGame() = default;

    /**
     * @brief Gets the name of the game (e.g. "Nibbler")
     * @return Name of the game
     */
    virtual const std::string &getName() const = 0;
    /**
     * @brief Starts the game
     */
    virtual void start(IDisplayModule *display) = 0;
    /**
     * @brief Stops the game
     */
    virtual void stop() = 0;
    /**
     * @brief Process one frame of the game
     */
    virtual void update(IDisplayModule *display) = 0;
    /**
     * @brief Draws the current frame of the game
     */
    virtual void render() = 0;
    /**
     * @brief Handles player input
     */
    virtual void handleEvent() = 0;

    virtual int getState() = 0;

    /**
     * @brief Returns the initial state of the game
     * @param path Path to the map file (might be empty if map is
     * auto generated)
     * @return
     */
    virtual std::vector<std::vector<int>> getInitialMap(
            const std::string &path) = 0;
};

