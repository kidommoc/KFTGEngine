add_executable(${GAME_NAME} main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(LIBS)

find_library(glew_LIB glew32.dll ${CMAKE_SOURCE_DIR}/lib)
if(glew_LIB)
	set(LIBS ${LIBS} ${glew_LIB})
	target_link_libraries(${GAME_NAME} ${glew_LIB})
else()
	message("not found glew")
endif(glew_LIB)

find_library(glfw_LIB glfw3.dll ${CMAKE_SOURCE_DIR}/lib)
if(glfw_LIB)
	set(LIBS ${LIBS} ${glfw_LIB})
	target_link_libraries(${GAME_NAME} ${glfw_LIB})
else()
	message("not found glfw")
endif(glfw_LIB)

file(COPY ${LIBS} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_subdirectory(Common)
add_subdirectory(Core)
add_subdirectory(Memory)

target_link_libraries(${GAME_NAME}
	Common
	Memory
	Core
)