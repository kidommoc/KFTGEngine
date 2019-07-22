project(App)

set (GAME_NAME test)
set(CMAKE_C_FLAG "-target x86_64-pc-windows-gnu")
set(CMAKE_CXX_FLAG "-target x86_64-pc-windows-gnu")
add_executable(${GAME_NAME} main.cpp)

include_directories(../Asset ../Core ../Memory)

target_link_libraries(test
	Core
	Asset
	Memory
)