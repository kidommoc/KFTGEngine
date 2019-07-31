cmake_minimum_required(VERSION 3.15)
project(KFTGEngine)

set(CMAKE_C_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_STANDARD_LIBRARIES -lopengl32)

option(GAME_NAME "the name of the game" game)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(source)