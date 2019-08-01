cmake_minimum_required(VERSION 3.15)
project(KFTGEngine)

set(CMAKE_C_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_STANDARD_LIBRARIES -lopengl32)

option(GAME_NAME "the name of the game" game)
option(DEBUG "debug mode" OFF)
option(NODATA "test mode" OFF)

if(DEBUG)
	add_compile_definitions(DEBUG)
endif(DEBUG)

if(NODATA)
	add_compile_definitions(NODATA)
endif(NODATA)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(source)