#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"
#include "../Common/types.hpp"
#include "string.hpp"

namespace KFTG
{

class DisplayManager : public LoopModule, public Singleton
{
public:
	static DisplayManager* instance ();
	~DisplayManager () {}
	virtual void init () override;
	virtual void exit () override;
	virtual void loop () override;

	GLFWwindow* getWindowHandle () { return _window; }

private:
	DisplayManager () {}

	GLFWwindow *_window;
	u32 _windowWidth;
	u32 _windowHeight;
	u32 _bufWidth;
	u32 _bufHeight;
	string _windowName;
};

}