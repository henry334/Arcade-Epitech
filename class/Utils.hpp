/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Util
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_
    #include <string>
    #include <vector>
    #include <iostream>
    #include <sstream>
    #include <cctype>

class Utils {
    public:
        Utils() = default;
        ~Utils() = default;
        std::vector<std::string> parser(std::string, char);
        std::string toCap(std::string);
        bool isAllUpperCase(const std::string& str);
};

#endif /* !UTILS_HPP_ */
