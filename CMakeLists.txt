cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(SnakeConsole)

set(CMAKE_CXX_STANDARD 17)

include_directories(./header)

file (GLOB SRC_FILES main.cpp source/*.cpp)

add_executable(snake ${SRC_FILES})

TARGET_LINK_LIBRARIES( snake
pthread
ncurses
)