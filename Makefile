##
## EPITECH PROJECT, 2018
## rtype
## File description:
## Makefile
##

CXX 	= g++

RM 	= rm -rf

NAME 	= rtype-client

LIBMAKE	= make -C engine

ENTITIESMAKE = make -C entities

SRC 	= source/Main.cpp

OBJ 	= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Wextra -g
CXXFLAGS	+= -I include/engine
CXXFLAGS	+= -I include/engine/utils
CXXFLAGS	+= -I include/engine/component
CXXFLAGS	+= -I include/engine/component/renderer
CXXFLAGS	+= -I include/engine/component/controller
CXXFLAGS	+= -I include/engine/script
CXXFLAGS	+= -I include/engine/script/task
CXXFLAGS	+= -I include/engine/exception
CXXFLAGS	+= -I include/engine/display/
CXXFLAGS	+= -I engine/display
CXXFLAGS	+= -I include/engine/sceneScreen/
CXXFLAGS	+= -I include/engine/screen
CXXFLAGS	+= -I include/engine/scene

LDFLAGS	= -L engine -lengine
LDFLAGS	+= -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS += -ldl

$(NAME): $(OBJ)
	$(LIBMAKE)
	$(ENTITIESMAKE)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(LIBMAKE) clean
	$(RM) $(OBJ)

fclean: clean
	$(LIBMAKE) fclean
	$(ENTITIESMAKE) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

