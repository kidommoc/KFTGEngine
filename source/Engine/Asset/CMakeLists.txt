add_library(Asset
	Filesystem.hpp
	Filesystem.cpp
)

target_link_libraries(Asset
	Common
	Memory
)