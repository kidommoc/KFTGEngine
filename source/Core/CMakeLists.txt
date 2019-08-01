project(Core)

set(HEADERS
	AssetManager.hpp
	AssetTypes.hpp
	AudioManager.hpp
	DisplayManager.hpp
	EventManager.hpp
	Filesystem.hpp
	InputManager.hpp
	map.hpp
	Math.hpp
	Root.hpp
	string.hpp
	Time.hpp
)

set(SOURCES
	AssetManager.cpp
	AssetTypes.cpp
	AudioManager.cpp
	DisplayManager.cpp
	EventManager.cpp
	Filesystem.cpp
	InputManager.cpp
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