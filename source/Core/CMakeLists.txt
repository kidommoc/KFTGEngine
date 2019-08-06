project(Core)

set(HEADERS
	map.hpp
	Math.hpp
	Root.hpp
	Singleton.hpp
	string.hpp
	types.hpp
)

set(SOURCES
	Math.cpp
	Root.cpp
	string.cpp
)

add_library(Core
	${HEADERS}
	${SOURCES}
)

add_subdirectory(Asset)
add_subdirectory(Audio)
add_subdirectory(Display)
add_subdirectory(Event)
add_subdirectory(Memory)
add_subdirectory(Time)

target_link_libraries(Core
	Asset
	Audio
	Display
	Event
	Memory
	Time
)