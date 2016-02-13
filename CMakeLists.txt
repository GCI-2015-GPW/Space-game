cmake_minimum_required(VERSION 3.0)

project(Space-game)


find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

set(Space_SOURCES
	main.cpp
	OpenGL.cpp
)

add_executable(game ${Space_SOURCES})


target_link_libraries(game ${OPENGL_LIBRARIES} SDL2)

target_include_directories(game PUBLIC
	${SDL2_INCLUDE_DIR}
	
	${OPENGL_INCLUDE_DIR}
)

