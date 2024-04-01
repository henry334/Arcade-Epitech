##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

CC	=	g++

OBJ1	=	Snake.cpp \

OBJ2	=	Nibbler.cpp \

OBJ3	=	SolarFox.cpp \

CPPFLAGS	=	-I../../class

NAME1	=	arcade_snake.so

NAME2	=	arcade_nibbler.so

NAME3	=	arcade_solarfox.so

all:	snake nibbler solarfox

snake:
	cd Snake && $(CC) -shared -fPIC -g3 -o $(NAME1) $(OBJ1) $(CPPFLAGS)
	mv Snake/$(NAME1) ../lib/

nibbler:
	cd Nibbler && $(CC) -shared -fPIC -g3 -o $(NAME2) $(OBJ2) $(CPPFLAGS)
	mv Nibbler/$(NAME2) ../lib/

solarfox:
	cd SolarFox && $(CC) -shared -fPIC -g3 -o $(NAME3) $(OBJ3) $(CPPFLAGS)
	mv SolarFox/$(NAME3) ../lib/

clean:
	rm -f ../lib/$(NAME1)
	rm -f ../lib/$(NAME2)
	rm -f ../lib/$(NAME3)

fclean: clean

re: fclean all

.PHONY:	all clean fclean re
