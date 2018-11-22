cmake_minimum_required(VERSION 2.8.12)
project(RType)

add_definitions("-std=c++11")

include(build/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/engine
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/component
			${CMAKE_CURRENT_SOURCE_DIR}/include/engine/utils)
set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -I include/engine -I include/engine/component -I include/engine/utils")
add_library(engine STATIC engine/GameEngine.cpp
			       engine/Renderer.cpp
			       engine/Transform.cpp
			       engine/component/AComponent.cpp
			       engine/utils/Vector.cpp)

add_executable(rtype-client source/Main.cpp)
target_link_libraries(rtype-client ${CONAN_LIBS} engine)
