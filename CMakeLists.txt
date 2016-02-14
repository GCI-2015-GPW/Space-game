cmake_minimum_required(VERSION 3.0)

project(Space-game)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;")


find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2Image REQUIRED)


include_directories(${GLM_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

set(Space_SOURCES
	main.cpp
	OpenGL.cpp
	OpenGL.h
	Texture.cpp
	Texture.h
	lodepng.cpp
)

add_executable(game ${Space_SOURCES})

target_compile_features(game PUBLIC
    cxx_variable_templates
)

target_link_libraries(game ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARIES})
