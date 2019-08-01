#include "DisplayManager.hpp"
#include "EventManager.hpp"
#include <windows.h>

namespace KFTG
{

DisplayManager* DisplayManager::instance ()
{
	static DisplayManager _instance;
	return &_instance;
}

void DisplayManager::init ()
{
#ifndef DEBUG
	::ShowWindow (::GetConsoleWindow (), SW_HIDE);
#endif
	glfwInit ();
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_windowWidth = 1280;
	_windowHeight = 720;
#ifndef NODATA
	// get window name from data
	_windowName = "test";
#else
	_windowName = "test";
#endif
	_window = glfwCreateWindow (_windowWidth, _windowHeight,
		_windowName.getCStr (), nullptr, nullptr);
	if (!_window)
		return;
	glfwMakeContextCurrent (_window);	

	glewExperimental = GL_TRUE;
	if (glewInit () != GLEW_OK)
		return;

	glfwGetFramebufferSize (_window, (int*) &_bufWidth, (int*) &_bufHeight);
	glViewport (0, 0, _bufWidth, _bufHeight);
}

void DisplayManager::exit ()
{
	glfwTerminate ();
}

void DisplayManager::loop ()
{
	if (glfwWindowShouldClose (_window))
		EventManager::instance ()->fireEvent (Event::QuitGame, nullptr);
	glfwPollEvents ();
	glfwSwapBuffers (_window);
}

}