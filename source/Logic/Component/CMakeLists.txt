set(HEADERS
)

set(SOURCES
)

add_library(Component
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Component
	Logic
)