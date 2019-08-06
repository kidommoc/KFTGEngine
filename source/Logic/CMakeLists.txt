project(Logic)

set(HEADERS
)

set(SOURCES
)

add_library(Logic
	${HEADERS}
	${SOURCES}
)

add_subdirectory(Component)
add_subdirectory(Entity)
add_subdirectory(System)

target_link_libraries(Logic
	Component
	Core
	Entity
	System
)