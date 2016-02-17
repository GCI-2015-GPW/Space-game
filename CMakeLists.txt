cmake_minimum_required(VERSION 3.0)

project(Space-game)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;")


find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED system thread)

pkg_search_module(GLFW REQUIRED glfw3)


include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
include_directories(src)

set(Space_SOURCES
	src/log/LogMessage.cc
	src/log/LogLevel.cc
	src/log/LogSink.cc
	src/log/Logger.cc
	src/thread/ActiveObject.cc
	src/main.cpp
)

add_executable(game ${Space_SOURCES})

target_compile_features(game PUBLIC
    cxx_defaulted_functions
)

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
