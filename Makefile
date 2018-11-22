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

SRC 	= source/Main.cpp

OBJ 	= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Wextra
CXXFLAGS	+= -I include/engine

LDFLAGS	= -L engine -lengine

$(NAME): $(OBJ)
	$(LIBMAKE)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(LIBMAKE) clean
	$(RM) $(OBJ)

fclean: clean
	$(LIBMAKE) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

