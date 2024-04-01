/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.fiancette
** File description:
** LoadLib
*/

#include "LoadLib.hpp"

IGame* LoadLib::getLibgame(void *lib_handle)
{
    using CreateGameModuleFunc = IGame* (*)();
    CreateGameModuleFunc create_func = (CreateGameModuleFunc)dlsym(lib_handle, "createGameModule");
    if (!create_func) {
        dlclose(lib_handle);
        return nullptr;
    }

    return create_func();
}

int LoadLib::destroyLibgame(IGame *lib, void *lib_handle)
{
    using DestroyGameModuleFunc = void (*)(IGame*);
    DestroyGameModuleFunc destroy_func = (DestroyGameModuleFunc)dlsym(lib_handle, "destroyGameModule");
    if (!destroy_func) {
        std::cerr << dlerror() << std::endl;
        dlclose(lib_handle);
        return 84;
    }

    destroy_func(lib);
    dlclose(lib_handle);

    return 0;
}

IDisplayModule* LoadLib::getLib(void *lib_handle, char *name)
{
    using CreateDisplayModuleFunc = IDisplayModule* (*)(char *);
    CreateDisplayModuleFunc create_func = (CreateDisplayModuleFunc)dlsym(lib_handle, "createDisplayModule");
    if (!create_func) {
        dlclose(lib_handle);
        return nullptr;
    }

    return create_func(name);
}

int LoadLib::destroyLib(IDisplayModule *lib, void *lib_handle)
{
    using DestroyDisplayModuleFunc = void (*)(IDisplayModule*);
    DestroyDisplayModuleFunc destroy_func = (DestroyDisplayModuleFunc)dlsym(lib_handle, "destroyDisplayModule");
    if (!destroy_func) {
        std::cerr << dlerror() << std::endl;
        dlclose(lib_handle);
        return 84;
    }
    
    destroy_func(lib);
    dlclose(lib_handle);

    return 0;
}

void *LoadLib::changelibhandler(void *lib_handle, IDisplayModule *display,
    std::string lib, std::map<std::string, std::size_t> libs)
{
    Utils utils;
    std::string path;
    std::vector<std::string> t;
    std::vector<std::string> nameslib;
    for (auto l : libs) {
        t.push_back(l.first);
        std::string name = utils.parser(l.first, '_')[1];
        name = utils.parser(name, '.')[0];
        nameslib.push_back(utils.toCap(name));
        
    }
    if (lib == nameslib[0])
        path = "lib/" + t[1];
    if (lib == nameslib[1])
        path = "lib/" + t[2];
    if (lib == nameslib[2])
        path = "lib/" + t[0];
    this->destroyLib(display, lib_handle);
    return this->lib_handle(path);
}

void *LoadLib::lib_handle(std::string path)
{
    void* lib_handle = dlopen(path.c_str(), RTLD_NOW);
    if (!lib_handle) {
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }
    return lib_handle;
}

std::map<int, std::string> LoadLib::getLibsName()
{
    std::map<int, std::string> temp;
    DIR* dir;
    struct dirent* entry;
    std::string path = "path/to/directory";
    dir = opendir("lib/");
    if (dir == NULL) {
        std::cout << "Failed to open directory." << std::endl;
        return temp;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && entry->d_name[0] != '.') {
            temp[temp.size()] = entry->d_name;
        }
    }
    closedir(dir);
    return temp;
}
std::tuple<std::map<std::string, std::size_t>, std::map<std::string, std::size_t>>
    LoadLib::parse_libs(std::map<int, std::string> libs)
{
    std::map<std::string, std::size_t> games;
    std::map<std::string, std::size_t> libss;
    for (auto lib : libs) {
        std::string path = "lib/" + lib.second;
        void *lib_handle = this->lib_handle(path);
        if (lib_handle == nullptr) {
            continue;
        }
        IGame *game = this->getLibgame(lib_handle);
        if (game != nullptr) {
            games[lib.second] = games.size();
            this->destroyLibgame(game, lib_handle);
        } else {
            lib_handle = this->lib_handle(path);
            if (lib_handle == nullptr)
                continue;
            IDisplayModule *display = this->getLib(lib_handle, NULL);
            if (display != nullptr) {
                libss[lib.second] = libss.size();
                this->destroyLib(display, lib_handle);
            }
        }
    }
    return {libss, games};
}
