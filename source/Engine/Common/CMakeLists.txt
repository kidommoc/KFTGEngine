project(Common)
add_library(Common
	Module.hpp
	Root.hpp
	Root.cpp
	types.hpp
	string.hpp
	string.cpp
)

target_link_libraries(Common
	Memory
)