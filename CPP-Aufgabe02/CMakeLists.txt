cmake_minimum_required(VERSION 3.2)
project(CPP_Aufgabe02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test_fix_point_collection.cpp)
add_executable(CPP_Aufgabe02 ${SOURCE_FILES} fix_point_collection.h fix_point_collection.cpp test_fix_point_collection.cpp fix_point_oo.hpp fix_point_oo.cpp)