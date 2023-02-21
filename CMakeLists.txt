cmake_minimum_required(VERSION 3.24)
project(Bamazon C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/bamdata.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Bamazon
        bamazon.c
        bamazon.h
        main.c)
