project(Common)
add_library(Common
	Module.hpp
	Root.hpp
	Root.cpp
	types.hpp
	Utils.hpp
	Utils.cpp
)

target_link_libraries(Common
	Memory
)