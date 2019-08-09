set(HEADERS
	World.hpp
)

set(SOURCES
	World.cpp
)

add_library(System
	${HEADERS}
	${SOURCES}
)

target_link_libraries(System
	Logic
)