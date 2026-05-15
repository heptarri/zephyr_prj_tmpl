cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_SOURCE_DIR})

set(BOARD my_board)

find_package(Zephyr REQUIRED HINTS ${ENV}ZEPHYR_BASE)
project(tmpl_prj)

target_sources(app PRIVATE
    src/main.cpp
)