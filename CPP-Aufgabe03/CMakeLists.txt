cmake_minimum_required(VERSION 3.2)
project(CPP_Aufgabe03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CPP_Aufgabe03 ${SOURCE_FILES} fix_point_oo.cpp fix_point_oo.hpp)