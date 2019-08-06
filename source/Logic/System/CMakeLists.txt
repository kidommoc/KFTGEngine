set(HEADERS
)

set(SOURCES
)

add_library(System
	${HEADERS}
	${SOURCES}
)

target_link_libraries(System
	Logic
)