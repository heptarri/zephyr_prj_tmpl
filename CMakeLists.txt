cmake_minimum_required(VERSION 3.20.0)

list(APPEND BOARD_ROOT ${CMAKE_SOURCE_DIR})

# set(BOARD my_board)
set(BOARD nucleo_f411re)

find_package(Zephyr REQUIRED HINTS ${ENV}ZEPHYR_BASE)
project(tmpl_prj)

target_sources(app PRIVATE
    src/main.cpp
    # src/app/user-gpio.cpp
    src/app/user-pwm.cpp
    src/app/user-adc.cpp
    src/app/user-spi.cpp
)