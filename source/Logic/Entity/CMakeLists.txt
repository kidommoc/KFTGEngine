set(HEADERS
	Entity.hpp
	EntityHandle.hpp
	EntityManager.hpp
)

set(SOURCES
	EntityHandle.cpp
	EntityManager.cpp
)

add_library(Entity
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Entity
	Logic
)