project(Core)

set(HEADERS
	AssetManager.hpp
	AssetTypes.hpp
	Filesystem.hpp
	map.hpp
	Math.hpp
	Root.hpp
	string.hpp
	Time.hpp
)

set(SOURCES
	AssetManager.cpp
	AssetTypes.cpp
	Filesystem.cpp
	Math.cpp
	Root.cpp
	string.cpp
	Time.cpp
)

add_library(Core
	${SOURCES}
	${HEADERS}
)

target_link_libraries(Core
	Common
	Memory
)