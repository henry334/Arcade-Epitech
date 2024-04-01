##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CC	=	g++

OBJ	=	SDL.cpp \
		../../class/ADisplay.cpp

CPPFLAGS	=	-I../../class -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

NAME	=	arcade_sdl2.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -shared -fPIC -o $(NAME) $(OBJ) $(CPPFLAGS)
	mv $(NAME) ../../lib/

clean:
	$(RM)
	rm -f ../../lib/$(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
