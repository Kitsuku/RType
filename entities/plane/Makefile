##
## EPITECH PROJECT, 2018
## rtype
## File description:
## plane
##

NAME	= ../Plane.so

RM	= rm -rf

CXX	= g++

SRC	= Link.cpp

OBJ	= $(SRC:.cpp=.o)

CXXFLAGS	+= -W -Wall -Wextra -fPIC
# wlrpass "wl quelquechose"
CXXFLAGS	+= -I ../../include/engine
CXXFLAGS	+= -I ../../include/engine/utils
CXXFLAGS	+= -I ../../include/engine/display
CXXFLAGS	+= -I ../../include/engine/component
CXXFLAGS	+= -I ../../include/engine/component/renderer

LDFLAGS		= -shared -Wl,-export-dynamic

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
