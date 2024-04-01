/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IDisplay
*/

#pragma once

#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <memory>

#include "Colors.hpp"
#include "Events.hpp"
#include "GameState.hpp"

/**
 * @brief Interface for a display module
 * @tparam tileSize Size of a tile in pixels
 */
class IDisplayModule {
public:
    virtual ~IDisplayModule() = default;

////////////////////////////////// UTILS //////////////////////////////////////

    /**
     * @brief Set the Window Size object
     * 
     * @param width 
     * @param height 
     */

    virtual void setWindowSize(int width, int height) = 0;

    /**
     * @brief Gets the name of the library (e.g. "SFML")
     * @return Name of the library
     */
    virtual const std::string getLibName() const = 0;

    /**
     * @brief Gets the size of a tile
     * @return Size of a tile in pixels
     */
    virtual constexpr int getTileSize() const = 0;

    /**
     * @brief Converts map coordinates to window coordinates.
     * @param coord Map coordinates
     * @return Window coordinates
     * @example If tile size is 32,
     * mapToWindow({0, 0}) = {0, 0}
     * mapToWindow({1, 1}) = {32, 32}
     * mapToWindow({-2, 3}) = {-64, 96}
     */
    virtual const std::vector<int> mapToWindow(
        const std::vector<int> &coord) const = 0;

///////////////////////////////// DRAWING /////////////////////////////////////
    /**
     * @brief Clears the screen
     */
    virtual void clear() = 0;

    /**
     * @brief Draws the current frame
     */
    virtual void display() = 0;

    /**
     * @brief Draws a sprite at the given position
     * @param type Number in the map
     * @param pos Map coordinates of the sprite
     */
    virtual void drawSprite(
        int type, const std::vector<float> &pos,
            colors::Color color) = 0;

    /**
     * @brief Gets the path to the sprite corresponding to the given type
     * @param type Number in the map
     * @return Path to the sprite
     */
    virtual const std::string &getSpritePath(int type) const = 0;

    /**
     * @brief Draws game based on the given map.
     * The map is a 2D vector of int. Each int represents a type of sprite.
     * The sprite path is given by getSpritePath()
     * @param map 2D vector of int representing the map
    */
    virtual void drawMap(const std::vector<std::vector<int>> &map) = 0;

    // n & 0XFFFF   // first 16 bits
    // n >> 16      // last 16 bits
    /**
     * @brief Draws a message on the screen
     * @param text The text to draw
     * @param pos Map coordinates of the text
     */
    virtual void drawText(
        const std::string &text, const std::vector<int> &pos,
        colors::Color color) = 0;

    /**
     * @brief Draws a button on the screen
     * @param text The text to draw
     * @param pos Map coordinates of the button
     * @param size Size of the button
     * @param color Color of the button
     */
    virtual void drawButton(
        const std::string &text,
        const std::vector<int> &pos, const std::vector<int> &size,
        colors::Color color) = 0;

////////////////////////////////// EVENTS /////////////////////////////////////

    /**
     * @brief Fetches all events from the window and stores them internally.
     * Use getEvents() to get the events.
     */
    virtual void fetchEvents() = 0;
    /**
     * @brief Gets all events that have been fetched since the last call to
     * fetchEvents()
     * @return Bitset of events
     */
    virtual events::Event getEvents() = 0;

    /**
     * @brief Checks if the mouse is pressed based on the last call to
     * fetchEvents()
     * @return True if the mouse is pressed, false otherwise
     */
    virtual bool isMousePressed() = 0;
    /**
     * @brief Gets the position of the mouse based on the last call to
     * fetchEvents()
     * @return Vector of 2 int containing the x and y coordinates of the mouse
     */
    virtual std::vector<int> getMousePos() = 0;

////////////////////////////////// MUSIC //////////////////////////////////////

    /**
     * @brief Handles music
     * @param path Path to the music file
     * @param loop True if the music should loop, false otherwise
     * @param play True if the music should start, false if it should stop
     */
    virtual void handleMusic(const std::string &path, bool loop,
        bool play) = 0;

};
