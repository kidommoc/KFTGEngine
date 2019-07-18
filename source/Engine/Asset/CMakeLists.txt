add_library(Asset
	AssetManager.hpp
	AssetManager.cpp
	AssetTypes.hpp
	AssetTypes.cpp
	Filesystem.hpp
	Filesystem.cpp
)

target_link_libraries(Asset
	Common
	Memory
)