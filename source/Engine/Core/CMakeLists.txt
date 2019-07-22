project(Core)

set(HEADERS
	map.hpp
	Math.hpp
	Module.hpp
	Root.hpp
	string.hpp
	Time.hpp
	types.hpp
)

set(SOURCES
	Math.cpp
	Root.cpp
	string.cpp
	Time.cpp
)

add_library(Core ${SOURCES} ${HEADERS})

include_directories(../Core ../Memory ../Asset)

target_link_libraries(Core
	Asset
	Memory
)