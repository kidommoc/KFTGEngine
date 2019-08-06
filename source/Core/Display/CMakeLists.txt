set(HEADERS
	DisplayManager.hpp
)

set(SOURCES
	DisplayManager.cpp
)

add_library(Display
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Display
	Core
)