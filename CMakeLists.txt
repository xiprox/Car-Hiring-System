cmake_minimum_required(VERSION 3.3)
project(Car_Hiring_System)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c struct.h user.h auth.h print.h car.h)
add_executable(Car_Hiring_System ${SOURCE_FILES})