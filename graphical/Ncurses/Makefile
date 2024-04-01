##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CC	=	g++

OBJ	=	Ncurses.cpp \
		../../class/ADisplay.cpp

NAME	=	arcade_ncurses.so

CPPFLAGS	=	-I../../class -lncurses

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
