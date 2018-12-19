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

SRC 	= GameEngine.cpp				\
	  Transform.cpp					\
	  Objective.cpp					\
	  Feature.cpp					\
	  sceneScreen/ASceneScreen.cpp			\
	  sceneScreen/MenuScreen.cpp			\
	  sceneScreen/ChannelScreen.cpp			\
	  sceneScreen/Button.cpp			\
	  utils/Vector.cpp				\
	  component/Component.cpp			\
	  component/ScriptedComponent.cpp		\
	  component/renderer/ARenderer.cpp		\
	  component/renderer/SfmlRenderer.cpp		\
	  component/controller/SfmlController.cpp	\
	  script/ScriptObject.cpp			\
	  script/task/TaskMove.cpp			\
	  script/task/TaskShoot.cpp			\
	  script/task/TaskFactory.cpp			\
	  script/task/TaskObjective.cpp			\
	  exception/SceneException.cpp			\
	  exception/EngineException.cpp			\
	  exception/ComponentException.cpp		\
	  exception/DisplayException.cpp		\
	  display/SfmlDisplay.cpp			\
	  scene/Scene.cpp				\
	  scene/SceneLoader.cpp				\
	  scene/ActorLoader.cpp				\
	  screen/Screen.cpp				\
	  ../source/masterClient/MasterClient.cpp	\
	  ../source/client/UdpClient.cpp		\
	  ../source/client/LobbyClient.cpp		\
	  ../source/client/ClientInLobby.cpp		\
	  ../source/Launcher.cpp			\

OBJ 	= $(SRC:.cpp=.o)
LDFLAGS += -lboost_system -lboost_date_time -lboost_thread -lpthread
CXXFLAGS	+= -W -Wall -Wextra -g

CXXFLAGS	+= -I ../include/engine
CXXFLAGS	+= -I ../include/engine/utils
CXXFLAGS	+= -I ../include/engine/component
CXXFLAGS	+= -I ../include/engine/component/renderer
CXXFLAGS	+= -I ../include/engine/component/controller
CXXFLAGS	+= -I ../include/engine/script
CXXFLAGS	+= -I ../include/engine/script/task
CXXFLAGS	+= -I ../include/engine/exception
CXXFLAGS	+= -I ../include/engine/display
CXXFLAGS	+= -I ../include/engine/sceneScreen/
CXXFLAGS	+= -I ../include/engine/screen
CXXFLAGS	+= -I ../include/engine/scene
CXXFLAGS	+= -I ../include/masterClient
CXXFLAGS	+= -I ../include/client
CXXFLAGS	+= -I ../include/

.cpp.o:
	@echo -e "\e[92mCompilation of \e[93m$<\e[92m into \e[94m$@\e[0m"
	@$(CXX) $(CXXFLAGS) $< -c -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

