project(Memory)

set(HEADERS
	Allocators.hpp
	MemoryManager.hpp
)

set(SOURCES
	Allocators.cpp
	MemoryManager.cpp
)

add_library(Memory ${SOURCES} ${HEADERS})

target_link_libraries(Memory
	Common
)