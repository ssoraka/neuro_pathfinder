cmake_minimum_required(VERSION 3.17)
project(game_with_brain C)

set(CMAKE_C_STANDARD 99)

add_executable(game_with_brain main.c header.h game.c)
target_link_libraries(game_with_brain m)