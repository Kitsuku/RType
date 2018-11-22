##
## EPITECH PROJECT, 2018
## rtype
## File description:
## Engine Makefile
##

CXX	= g++

AR 	= ar rc

RM 	= rm -rf

NAME 	= libengine.a

SRC 	= GameEngine.cpp		\
	  Transform.cpp			\
	  Renderer.cpp			\
	  utils/Vector.cpp		\
	  component/AComponent.cpp	\

OBJ 	= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Wextra
CXXFLAGS	+= -I ../include/engine
CXXFLAGS	+= -I ../include/engine/utils
CXXFLAGS	+= -I ../include/engine/component

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

