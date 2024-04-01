##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CC	=	g++

OBJ	=	SFML.cpp \
		../../class/ADisplay.cpp

CPPFLAGS	=	-I../../class -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

NAME	=	arcade_sfml.so

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
