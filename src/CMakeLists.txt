cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)              # Need to set before or else Mac doesn't use C++11
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(TicTacToe)

message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")
set(HEADERS board.hpp gameplay.hpp translateCmd.hpp)
set(SOURCE board.cpp gameplay.cpp translateCmd.cpp)

add_library(my_lib STATIC ${SOURCE})
target_include_directories(my_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(TicTacToe tictactoe.cpp )
target_link_libraries(TicTacToe PRIVATE my_lib)