cmake_minimum_required(VERSION 3.0)

project(Space-game)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/dependencies/hana/cmake/")

# tell hana where hana is :)
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/hana/include)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

set(MOD_ECS_TEST OFF)
add_subdirectory(dependencies/ECS)

include_directories(${GLM_INCLUDE_DIRS})
include_directories(${MOD_ECS_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

set(Space_SOURCES
	main.cpp
	OpenGL.cpp
)

add_executable(game ${Space_SOURCES})

target_compile_features(game PUBLIC
    cxx_variable_templates
)

target_link_libraries(game ${OPENGL_LIBRARIES} ${SDL2_LIBRARY})
