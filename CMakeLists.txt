cmake_minimum_required(VERSION 3.7)
project(openNES_Pong)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c src/structures.h src/input.c src/update.c src/render.c src/globals.h)
add_executable(openNES_Pong ${SOURCE_FILES})