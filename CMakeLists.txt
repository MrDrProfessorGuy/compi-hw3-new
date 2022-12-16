cmake_minimum_required(VERSION 3.19)
project(compi_hw3_new)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")



add_executable(compi_hw3_new
        hw3_output.cpp hw3_output.hpp
        parser.tab.cpp parser.tab.hpp
        lex.yy.c
        )