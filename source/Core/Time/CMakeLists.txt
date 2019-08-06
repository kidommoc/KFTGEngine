set(HEADERS
	Time.hpp
)

set(SOURCES
	Time.cpp
)

add_library(Time
	${HEADERS}
	${SOURCES}
)

target_link_libraries (Time
	Core
)