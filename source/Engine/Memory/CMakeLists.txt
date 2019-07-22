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

include_directories(. ../Core ../Asset)

target_link_libraries(Memory
	Asset
	Core
)