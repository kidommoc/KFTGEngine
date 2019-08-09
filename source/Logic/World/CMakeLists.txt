set(HEADERS
	World.hpp
)

set(SOURCES
	World.cpp
)

add_library(World
	${HEADERS}
	${SOURCES}
)

target_link_libraries(World
	Logic
)