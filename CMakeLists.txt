cmake_minimum_required(VERSION 3.7)
project(openNES_Pong)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c src/structures.h)
add_executable(openNES_Pong ${SOURCE_FILES})