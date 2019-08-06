set(HEADERS
	EventManager.hpp
	InputManager.hpp
)

set(SOURCES
	EventManager.cpp
	InputManager.cpp
)

add_library(Event
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Event
	Core
)