project(Memory)
add_library(Memory
	MemoryManager.hpp
	MemoryManager.cpp
)

target_link_libraries(Memory
	Common
)