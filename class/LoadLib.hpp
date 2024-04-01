/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include <sstream>
#include <fstream>
#include <dlfcn.h>
#include <dirent.h>
#include <string>
#include <iostream>
#include "ADisplay.hpp"
#include "IGame.hpp"
#include "Utils.hpp"

class LoadLib {
    public:
        LoadLib() = default;
        ~LoadLib() = default;
        void* lib_handle(std::string path);
        std::map<int, std::string> getLibsName();
        IGame* getLibgame(void *lib_handle);
        int destroyLibgame(IGame *lib, void *lib_handle);
        void *changelibhandler(void *lib_handle, IDisplayModule *display, std::string lib,
            std::map<std::string, std::size_t> libs);
        IDisplayModule* getLib(void *lib_handle, char *name);
        int destroyLib(IDisplayModule *lib, void *lib_handle);
        std::tuple<std::map<std::string, std::size_t>, std::map<std::string, std::size_t>>
            parse_libs(std::map<int, std::string> libs);
};