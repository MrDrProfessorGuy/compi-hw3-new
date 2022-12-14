cmake_minimum_required(VERSION 3.19)
project(compi_hw3_new)

set(CMAKE_CXX_STANDARD 17)

add_executable(compi_hw3_new
        main.cpp
        parser.ypp
        scanner.lex
        hw3_output.cpp hw3_output.hpp
        statement_node.hpp
        exp_node.hpp
        )