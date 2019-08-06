set(HEADERS
	AssetManager.hpp
	AssetTypes.hpp
	Filesystem.hpp
)

set(SOURCES
	AssetManager.cpp
	AssetTypes.cpp
	Filesystem.cpp
)

add_library(Asset
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Asset
	Core
)