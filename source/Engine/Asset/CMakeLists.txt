project (Asset)

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

add_library(Asset ${SOURCES} ${HEADERS})

include_directories(. ../Core ../Memory)

target_link_libraries(Asset
	Core
	Memory
)