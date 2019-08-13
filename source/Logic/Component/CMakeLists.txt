set(HEADERS
	Animator.hpp
	Camera.hpp
	Collider.hpp
	Component.hpp
	ComponentHandle.hpp
	ComponentManager.hpp
	HUD.hpp
	Motion.hpp
	Player.hpp
	Sprite.hpp
	Transform.hpp
)

set(SOURCES
	ComponentHandle.cpp
	ComponentManager.cpp
	Components.cpp
)

add_library(Component
	${HEADERS}
	${SOURCES}
)

target_link_libraries(Component
	Logic
)