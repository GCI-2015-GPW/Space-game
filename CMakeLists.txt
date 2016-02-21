# Copyright (c) 2016 The Space Game Developers. All rights reserved.
# Use of this source code is governed by the MIT license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.0)

project(Space-game)

set(BUILD_DOCS OFF CACHE BOOL "Should cmake build doxygen documentation?")



find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED system thread)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
include_directories(src)

set(Space_SOURCES
	src/log/Logger.cc
	src/thread/ActiveObject.cc
	src/main.cpp
)

set(Space_HEADERS
	src/log/Logger.h	
)

add_executable(game ${Space_SOURCES})

# make sure we get a c++14 compiler
target_compile_features(game PUBLIC
	cxx_defaulted_functions
	cxx_lambda_init_captures
)

# link to the libraries we need
target_link_libraries(game 
	${OPENGL_LIBRARIES} 
	${GLFW_LIBRARIES} 
	${GLEW_LIBRARIES} 
	debug ${Boost_SYSTEM_LIBRARY_DEBUG} ${Boost_THREAD_LIBRARY_DEBUG}
	optimized ${Boost_SYSTEM_LIBRARY_RELEASE} ${Boost_THREAD_LIBRARY_RELEASE}
)

if(UNIX)
	target_link_libraries(game
		pthread
	)
endif(UNIX)


# documentation building


if(${BUILD_DOCS})
	
	message("\nBuilding documentation\n")
	
	find_package(Doxygen REQUIRED)
	
	set(doxyfile_in Doxyfile.in)
	set(doxyfile ${CMAKE_BINARY_DIR}/Doxyfile)
	
	configure_file(${doxyfile_in} ${doxyfile})
	
	add_custom_target(doc
		ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Generating doxygen documentation"
		DEPENDS ${Space_HEADERS} ${Space_SOURCES}
	)

endif(${BUILD_DOCS})
