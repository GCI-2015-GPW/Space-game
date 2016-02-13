cmake_minimum_required(VERSION 3.0)

project(Space-game)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

set(Space_SOURCES
	main.cpp
	OpenGL.cpp
)

add_executable(game ${Space_SOURCES})


target_link_libraries(game ${OPENGL_LIBRARIES} ${SDL2_LIBRARY})
