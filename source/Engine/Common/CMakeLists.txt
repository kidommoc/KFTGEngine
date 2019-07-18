project(Common)
add_library(Common
	Math.hpp
	Math.cpp
	Module.hpp
	Root.hpp
	Root.cpp
	string.hpp
	string.cpp
	Time.hpp
	Time.cpp
	types.hpp
)

target_link_libraries(Common
	Asset
	Memory
)