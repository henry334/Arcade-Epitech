/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** main.c
*/

#include "arcade.h"

void usage(void)
{
    std::cout << "USAGE\n";
    std::cout << "./arcade [lib]\n";
    std::cout << "FLAGS\n";
    std::cout << "  -h, \t--help\t\t\tDisplay this help\n";
    std::cout << "  -l, \t--libs\t\t\tDisplay available libs\n";
    std::cout << "COMMANDS\n";
    std::cout << "  p \tGo back to menu\n";
    std::cout << "  x \tExit the program or the username box\n";
    std::cout << "  g \tChange the game to the next one\n";
    std::cout << "  i \tChange the graphical library to the next one\n";
}

int init(LoadLib loader, char **av,
    std::tuple<std::map<std::string, std::size_t>,
    std::map<std::string, std::size_t>> lib_game) {
        Menu menu;
        menu.setLibs(std::get<0>(lib_game), std::get<1>(lib_game));
        menu.getCore()->setLibHandle(loader.lib_handle(av[1]));
        if (menu.getCore()->getlibhandle() == nullptr) {
            printf("Error in libHandle\n");
            return 84;
        }
        menu.start(nullptr);
        return menu.getCore()->getExitCode();
}

int main(int ac, char **av)
{   
    if (ac != 2) {
        usage();
        return 84;
    } else if (std::string(av[1]) == "-h" || std::string(av[1]) == "--help") {
        usage();
        return 0;
    }

    LoadLib loader;
    std::tuple<std::map<std::string, std::size_t>,
        std::map<std::string, std::size_t>> lib_game;
    std::map<int, std::string> temp;
    temp = loader.getLibsName();
    if (temp.size() <= 0) {
        printf("No libs\n");
        return 84;
    }
    lib_game = loader.parse_libs(temp);
    if (std::string(av[1]) == "-l" || std::string(av[1]) == "--libs") {
        std::cout << "Available libs:\n";
        for (auto l : std::get<0>(lib_game)) {
            std::cout << l.first << std::endl;
        }
        std::cout << "\nAvailable games:\n";
        for (auto l : std::get<1>(lib_game)) {
            std::cout << l.first << std::endl;
        }
        return 0;
    }

    return init(loader, av, lib_game);
}
