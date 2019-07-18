project(Memory)
add_library(Memory
	MemoryManager.hpp
	MemoryManager.cpp
	Allocators.hpp
	Allocators.cpp
)

target_link_libraries(Memory
	Asset
	Common
)