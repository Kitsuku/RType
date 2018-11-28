cmake_minimum_required(VERSION 2.8.12)
project(RType)

add_definitions("-std=c++11")

include(build/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/utils
			${CMAKE_CURRENT_SOURCE_DIR}/include/server)
set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")

add_library(engine STATIC engine/GameEngine.cpp
			       engine/Renderer.cpp
			       engine/Transform.cpp
			       engine/component/AComponent.cpp
			       engine/utils/Vector.cpp)

add_executable(rtype-client source/Main.cpp)
target_link_libraries(rtype-client ${CONAN_LIBS} engine)

add_executable(rtype-server source/server/Main.cpp
	source/server/UdpServer.cpp
	source/server/Client.cpp
	source/server/ClientManager.cpp
	source/server/Lobby.cpp)
target_link_libraries(rtype-server ${CONAN_LIBS} engine)
