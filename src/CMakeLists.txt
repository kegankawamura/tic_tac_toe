cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)              # Need to set before or else Mac doesn't use C++11
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(TicTacToe)
add_executable(TicTacToe
                 tictactoe.cpp
                 board.cpp
                 gameplay.cpp
                 translateCmd.cpp)
