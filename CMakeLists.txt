cmake_minimum_required(VERSION 2.8.12)
project(RType)

include(build/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/utils
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component/renderer
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component/controller
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/script
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/script/task
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/exception
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/display
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/sceneScreen
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/screen
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/scene
			${CMAKE_CURRENT_SOURCE_DIR}/include/server
			${CMAKE_CURRENT_SOURCE_DIR}/include/client)

set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -ldl")

add_library(engine STATIC engine/GameEngine.cpp
			   engine/Transform.cpp
			   engine/Objective.cpp
			   engine/Feature.cpp
			   engine/sceneScreen/LobbyScreen.cpp
			   engine/sceneScreen/ASceneScreen.cpp
			   engine/sceneScreen/Button.cpp
			   engine/utils/Vector.cpp
			   engine/component/Component.cpp
			   engine/component/ScriptedComponent.cpp
			   engine/component/renderer/ARenderer.cpp
			   engine/component/renderer/SfmlRenderer.cpp
			   engine/component/controller/SfmlController.cpp
			   engine/script/ScriptObject.cpp
			   engine/script/task/TaskMove.cpp
			   engine/script/task/TaskShoot.cpp
			   engine/script/task/TaskFactory.cpp
			   engine/script/task/TaskObjective.cpp
			   engine/exception/SceneException.cpp
			   engine/exception/EngineException.cpp
			   engine/exception/ComponentException.cpp
			   engine/exception/DisplayException.cpp
			   engine/display/SfmlDisplay.cpp
			   engine/scene/Scene.cpp
			   engine/scene/SceneLoader.cpp
			   engine/scene/ActorLoader.cpp
			   engine/screen/Screen.cpp)

add_executable(rtype-server source/server/Main.cpp
	source/server/UdpServer.cpp
	source/server/Client.cpp
	source/server/ClientManager.cpp
	source/server/Lobby.cpp
	source/server/Game.cpp)

add_executable(rtype-client source/client/Main.cpp
	source/client/UdpClient.cpp
	source/client/LobbyClient.cpp
	source/client/ClientInLobby.cpp)
target_link_libraries(rtype-client ${CONAN_LIBS} engine)

target_link_libraries(rtype-server ${CONAN_LIBS} engine)
