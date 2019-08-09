set(HEADERS
	Entity.hpp
	EntityManager.hpp
)

set(SOURCES
	Entity.cpp
	EntityManager.cpp
)

add_library(Entity
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Entity
	Logic
)