cmake_minimum_required(VERSION 2.8.9)

project(NowDisplaying)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
add_executable(NowDisplaying src/main.cpp)
qt5_use_modules(NowDisplaying Widgets)
