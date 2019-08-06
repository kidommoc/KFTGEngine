set(HEADERS
	AudioManager.hpp
)

set(SOURCES
	AudioManager.cpp
)

add_library(Audio
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Audio
	Core
)