cmake_minimum_required(VERSION 3.1)
project(CPP_Aufgabe01_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test_fix_point_oo.cpp)
add_executable(CPP_Aufgabe01_2 ${SOURCE_FILES} fix_point_oo.cpp fix_point_oo.hpp)