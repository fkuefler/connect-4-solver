cmake_minimum_required(VERSION 3.10)

project(Connect-4-Solver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set up the source files
set(SOURCE_FILES
    src/Board.cpp
    src/Player.cpp
    src/Minimax.cpp
    src/Main.cpp
)

# Set up the include directories
include_directories(include)

# Add the executable
add_executable(Connect-4-Solver ${SOURCE_FILES})