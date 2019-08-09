set(HEADERS
	Component.hpp
	ComponentHandle.hpp
	ComponentManager.hpp
)

set(SOURCES
	ComponentHandle.cpp
	ComponentManager.cpp
)

add_library(Component
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Component
	Logic
)