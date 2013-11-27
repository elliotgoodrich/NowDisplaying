cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror -std=c++11 -g")

project(NowDisplaying)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(HEADERS
	include/QtPtr.hpp
	include/NowDisplayingWindow.hpp)

set(SOURCES
	src/main.cpp
	src/NowDisplayingWindow.cpp)

include_directories(include/)

find_package(Qt5Widgets)
add_executable(NowDisplaying ${HEADERS} ${SOURCES})
qt5_use_modules(NowDisplaying Widgets)
