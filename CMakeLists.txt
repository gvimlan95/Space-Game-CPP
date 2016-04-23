cmake_minimum_required(VERSION 3.3)
project(SpaceGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(-std=c++0x)

set(SOURCE_FILES main.cpp Fleet.cpp Ship.h)
add_executable(SpaceGame ${SOURCE_FILES})