/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Utils
*/

#ifndef CORE_HPP_
    #define CORE_HPP_
    #include <sstream>
    #include <cctype>
    #include "ADisplay.hpp"
    #include "LoadLib.hpp"

class Core {
    public:
        Core();
        ~Core() = default;
        int getExitCode();
        void setExitCode(int code);
        int changelib(std::map<std::string, std::size_t> libs);
        void setIdisplay(IDisplayModule *display);
        IDisplayModule *getIdisplay();
        void setLibHandle(void *lib_handle);
        void *getlibhandle();
        std::string readFile(std::string path);
    private:
        IDisplayModule *display;
        void *lib_handle;
        int exitcode;
};

#endif /* !CORE_HPP_ */
