set(HEADERS
	Component.hpp
	ComponentManager.hpp
)

set(SOURCES
	ComponentManager.cpp
)

add_library(Component
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Component
	Logic
)