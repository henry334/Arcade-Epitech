/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** Utils
*/

#include "Core.hpp"

Core::Core()
{
    this->exitcode = 0;
}

int Core::getExitCode()
{
    return this->exitcode;
}

void Core::setExitCode(int code)
{
    this->exitcode = code;
}

int Core::changelib(std::map<std::string, std::size_t> libs)
{
    LoadLib loader;
    this->setLibHandle(loader.changelibhandler(this->lib_handle, this->display, this->display->getLibName(), libs));
    if (this->getlibhandle() == nullptr) {
        this->exitcode = 84;
        return 84;
    }
    char *temp = strdup("topass");
    this->setIdisplay(loader.getLib(this->getlibhandle(), temp));
    if (this->getIdisplay() == nullptr) {
        this->exitcode = 84;
        return 84;
    }
    free(temp);
    return 0;
}

void Core::setIdisplay(IDisplayModule *display)
{
    this->display = display;
}

IDisplayModule *Core::getIdisplay()
{
    return this->display;
}

void Core::setLibHandle(void *lib)
{
    this->lib_handle = lib;
}

void *Core::getlibhandle()
{
    return this->lib_handle;
}

std::string Core::readFile(std::string path)
{
    std::string data;
    std::ifstream files;
    files.open(path);
    if (files.fail()) {
        //std::cout << "Error loading: " << path << std::endl;
        return "";
    }
    std::ostringstream buffer;
    buffer << files.rdbuf();
    data = buffer.str();
    files.close();
    return data;
}