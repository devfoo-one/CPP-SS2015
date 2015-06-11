cmake_minimum_required(VERSION 3.1)
project(CPP_Aufgabe01_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test_generic_fix_point.cpp)
add_executable(CPP_Aufgabe01_3 ${SOURCE_FILES} fixpoint.hpp test_generic_fix_point.cpp)