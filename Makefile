##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##

CC	=	g++

SRC_CORE	=	main.cpp \
				class/LoadLib.cpp \
				class/Utils.cpp \
				class/Core.cpp \
				class/Menu.cpp

OBJ_CORE	=	$(SRC_CORE:.cpp=.o)


CFLAGS	=	-std=c++20 -Wall -Wextra -Werror -g3 -lm -ldl

CPPFLAGS	=	-I./class -I./graphical/Ncurses -I./graphical/SFML -I./graphical/SDL -I./include/

NAME	=	arcade

all:	core games graphicals

core:	$(OBJ_CORE)
	$(CC) -g3 -o $(NAME) $(OBJ_CORE) $(CFLAGS) $(CPPFLAGS)

games:
	make -C games/ --no-print-directory

graphicals:
	make -C graphical/Ncurses/ --no-print-directory
	make -C graphical/SDL/ --no-print-directory
	make -C graphical/SFML/ --no-print-directory

clean:
	$(RM) $(OBJ_CORE)
	make -C games/ clean --no-print-directory
	make -C graphical/Ncurses/ clean --no-print-directory
	make -C graphical/SDL/ clean --no-print-directory
	make -C graphical/SFML/ clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	make -C games/ fclean --no-print-directory
	make -C graphical/Ncurses/ fclean --no-print-directory
	make -C graphical/SDL/ fclean --no-print-directory
	make -C graphical/SFML/ fclean --no-print-directory

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re games graphicals
