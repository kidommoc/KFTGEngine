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

void keycb (GLFWwindow *w, int key, int scancode, int action, int mode)
{
	u32 k;
	switch (key)
	{
		case GLFW_KEY_TAB:				k = Keys::TAB;			break;
		case GLFW_KEY_ESCAPE:			k = Keys::ESC;			break;
		case GLFW_KEY_UP:				k = Keys::ARROW_UP;		break;
		case GLFW_KEY_DOWN:				k = Keys::ARROW_DOWN;	break;
		case GLFW_KEY_LEFT:				k = Keys::ARROW_LEFT;	break;
		case GLFW_KEY_RIGHT:			k = Keys::ARROW_RIGHT;	break;
		case GLFW_KEY_BACKSPACE:		k = Keys::BACKSPACE;	break;
		case GLFW_KEY_LEFT_CONTROL:		k = Keys::LEFT_CTRL;	break;
		case GLFW_KEY_RIGHT_CONTROL:	k = Keys::RIGHT_CTRL;	break;
		case GLFW_KEY_LEFT_SHIFT:		k = Keys::LEFT_SHIFT;	break;
		case GLFW_KEY_RIGHT_SHIFT:		k = Keys::RIGHT_SHIFT;	break;
		case GLFW_KEY_LEFT_ALT:			k = Keys::LEFT_ALT;		break;
		case GLFW_KEY_RIGHT_ALT:		k = Keys::RIGHT_ALT;	break;
		case GLFW_KEY_CAPS_LOCK:		k = Keys::CAPS_LOCK;	break;
		case GLFW_KEY_F1:				k = Keys::F1;			break;
		case GLFW_KEY_F2:				k = Keys::F2;			break;
		case GLFW_KEY_F3:				k = Keys::F3;			break;
		case GLFW_KEY_F4:				k = Keys::F4;			break;
		case GLFW_KEY_F5:				k = Keys::F5;			break;
		case GLFW_KEY_F6:				k = Keys::F6;			break;
		case GLFW_KEY_F7:				k = Keys::F7;			break;
		case GLFW_KEY_F8:				k = Keys::F8;			break;
		case GLFW_KEY_F9:				k = Keys::F9;			break;
		case GLFW_KEY_F10:				k = Keys::F10;			break;
		case GLFW_KEY_F11:				k = Keys::F11;			break;
		case GLFW_KEY_F12:				k = Keys::F12;			break;
		default:						k = key;				break;
	}

	switch (action)
	{
		case GLFW_PRESS:
			EventManager::instance ()->fireEvent (Event::KeyPress, &k);
			break;
		case GLFW_RELEASE:
			EventManager::instance ()->fireEvent (Event::KeyRelease, &k);
			break;
		default:
			break;
	}
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
	// TODO: get window name from data
#else
	_windowName = "test";
#endif
	_window = glfwCreateWindow (_windowWidth, _windowHeight,
		_windowName.getCStr (), nullptr, nullptr);
	if (!_window)
		return; // TODO: error handling
	glfwMakeContextCurrent (_window);	

	glewExperimental = GL_TRUE;
	if (glewInit () != GLEW_OK)
		return;

	glfwGetFramebufferSize (_window, (int*) &_bufWidth, (int*) &_bufHeight);
	glViewport (0, 0, _bufWidth, _bufHeight);

	glfwSetKeyCallback (_window, keycb);
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
	// draw
	glfwSwapBuffers (_window);
}

}