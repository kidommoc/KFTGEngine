set(HEADERS
)

set(SOURCES
)

add_library(Entity
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Entity
	Logic
)