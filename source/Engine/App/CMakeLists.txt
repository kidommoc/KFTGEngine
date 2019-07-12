cmake_minimum_required(VERSION 2.6)
project(App)
set(CMAKE_C_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_FLAG "-target x86_64-pc-windows-gnu")
add_executable(test main.cpp)

target_link_libraries(test
	Common
)