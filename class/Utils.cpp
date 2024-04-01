/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Util
*/

#include "Utils.hpp"

std::vector<std::string> Utils::parser(std::string str, char parse)
{
    std::vector<std::string> temp;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, parse)) {
        temp.push_back(token);
    }
    return temp;
}

std::string Utils::toCap(std::string str)
{
    for (int i = 0; i < str.size(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

bool Utils::isAllUpperCase(const std::string& str) {
    for (auto c : str) {
        if (!std::isupper(c)) {
            return false;
        }
    }
    return true;
}