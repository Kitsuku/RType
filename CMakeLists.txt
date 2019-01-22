cmake_minimum_required(VERSION 2.8.12)
project(RType)

IF (WIN32)
	include(cmake-build-release/conanbuildinfo.cmake)
	conan_basic_setup()
ELSE (WIN32)
	include(build/conanbuildinfo.cmake)
	conan_basic_setup()
ENDIF(WIN32)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/utils
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component/renderer
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component/controller
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component/collider
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/script
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/script/task
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/exception
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/display
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/sceneScreen
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/screen
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/scene
			${CMAKE_CURRENT_SOURCE_DIR}/include/server
			${CMAKE_CURRENT_SOURCE_DIR}/include/client
			${CMAKE_CURRENT_SOURCE_DIR}/include/masterClient
			${CMAKE_CURRENT_SOURCE_DIR}/include/
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/translate)

IF(WIN32)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/windows)
ELSE (WIN32)
	set(CMAKE_CXX_FLAGS "-ldl -W -Wall -Wextra")
ENDIF(WIN32)

IF(WIN32)
	add_library(engine STATIC engine/GameEngine.cpp
			engine/Transform.cpp
			engine/Objective.cpp
		    engine/Feature.cpp
		    engine/sceneScreen/MenuScreen.cpp
		    engine/sceneScreen/ChannelScreen.cpp
		    engine/sceneScreen/CreateLobbyScreen.cpp
		    engine/sceneScreen/LobbyScreen.cpp
		    engine/sceneScreen/LevelScreen.cpp
		    engine/sceneScreen/ASceneScreen.cpp
		    engine/sceneScreen/Button.cpp
		    engine/utils/Vector.cpp
		    engine/component/Component.cpp
		    engine/component/ScriptedComponent.cpp
		    engine/component/renderer/ARenderer.cpp
		    engine/component/renderer/SfmlRenderer.cpp
		    engine/component/controller/SfmlController.cpp
		    engine/component/collider/Collider.cpp
		    engine/component/collider/ColliderStatic.cpp
		    engine/script/ScriptObject.cpp
		    engine/script/task/TaskDirection.cpp
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
		    engine/screen/Screen.cpp
		    engine/translate/TransDeath.cpp
		    engine/translate/Translater.cpp
		    engine/translate/TransPosition.cpp
		    engine/translate/TransShoot.cpp
		    engine/translate/TransSpawn.cpp
		    source/masterClient/MasterClient.cpp
		    source/client/UdpClient.cpp
		    source/client/LobbyClient.cpp
		    source/client/ClientInLobby.cpp
		    source/Launcher.cpp
		    source/windows/dlfcn.c)
ELSE(WIN32)
	add_library(engine STATIC engine/GameEngine.cpp
			engine/Transform.cpp
			engine/Objective.cpp
			engine/Feature.cpp
			engine/sceneScreen/MenuScreen.cpp
			engine/sceneScreen/ChannelScreen.cpp
			engine/sceneScreen/CreateLobbyScreen.cpp
			engine/sceneScreen/LobbyScreen.cpp
			engine/sceneScreen/LevelScreen.cpp
			engine/sceneScreen/ASceneScreen.cpp
			engine/sceneScreen/Button.cpp
			engine/utils/Vector.cpp
			engine/component/Component.cpp
			engine/component/ScriptedComponent.cpp
			engine/component/renderer/ARenderer.cpp
			engine/component/renderer/SfmlRenderer.cpp
			engine/component/controller/SfmlController.cpp
			engine/component/collider/Collider.cpp
			engine/component/collider/ColliderStatic.cpp
			engine/script/ScriptObject.cpp
			engine/script/task/TaskDirection.cpp
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
			engine/screen/Screen.cpp
			engine/translate/TransDeath.cpp
			engine/translate/Translater.cpp
			engine/translate/TransPosition.cpp
			engine/translate/TransShoot.cpp
			engine/translate/TransSpawn.cpp
			source/masterClient/MasterClient.cpp
			source/client/UdpClient.cpp
			source/client/LobbyClient.cpp
			source/client/ClientInLobby.cpp
			source/Launcher.cpp)
ENDIF(WIN32)


add_executable(rtype-server source/server/Main.cpp
	source/server/UdpServer.cpp
	source/server/Client.cpp
	source/server/ClientManager.cpp
	source/server/Lobby.cpp
	source/server/Game.cpp)

add_executable(rtype-client source/Main.cpp
	source/client/UdpClient.cpp
	source/client/LobbyClient.cpp
	source/client/ClientInLobby.cpp)

target_link_libraries(rtype-client ${CONAN_LIBS} engine)

target_link_libraries(rtype-server ${CONAN_LIBS} engine)
