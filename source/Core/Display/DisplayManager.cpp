#include "../Display/DisplayManager.hpp"
#include "../Keys.hpp"
#include "../Event/EventManager.hpp"
#include "../Memory/MemoryManager.hpp"
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
		case GLFW_KEY_TAB:           k = Keys::TAB;         break;
		case GLFW_KEY_ESCAPE:        k = Keys::ESC;         break;
		case GLFW_KEY_UP:            k = Keys::ARROW_UP;    break;
		case GLFW_KEY_DOWN:          k = Keys::ARROW_DOWN;  break;
		case GLFW_KEY_LEFT:          k = Keys::ARROW_LEFT;  break;
		case GLFW_KEY_RIGHT:         k = Keys::ARROW_RIGHT; break;
		case GLFW_KEY_BACKSPACE:     k = Keys::BACKSPACE;   break;
		case GLFW_KEY_LEFT_CONTROL:  k = Keys::LEFT_CTRL;   break;
		case GLFW_KEY_RIGHT_CONTROL: k = Keys::RIGHT_CTRL;  break;
		case GLFW_KEY_LEFT_SHIFT:    k = Keys::LEFT_SHIFT;  break;
		case GLFW_KEY_RIGHT_SHIFT:   k = Keys::RIGHT_SHIFT; break;
		case GLFW_KEY_LEFT_ALT:      k = Keys::LEFT_ALT;    break;
		case GLFW_KEY_RIGHT_ALT:     k = Keys::RIGHT_ALT;   break;
		case GLFW_KEY_CAPS_LOCK:     k = Keys::CAPS_LOCK;   break;
		case GLFW_KEY_F1:            k = Keys::F1;          break;
		case GLFW_KEY_F2:            k = Keys::F2;          break;
		case GLFW_KEY_F3:            k = Keys::F3;          break;
		case GLFW_KEY_F4:            k = Keys::F4;          break;
		case GLFW_KEY_F5:            k = Keys::F5;          break;
		case GLFW_KEY_F6:            k = Keys::F6;          break;
		case GLFW_KEY_F7:            k = Keys::F7;          break;
		case GLFW_KEY_F8:            k = Keys::F8;          break;
		case GLFW_KEY_F9:            k = Keys::F9;          break;
		case GLFW_KEY_F10:           k = Keys::F10;         break;
		case GLFW_KEY_F11:           k = Keys::F11;         break;
		case GLFW_KEY_F12:           k = Keys::F12;         break;
		default:                     k = key;               break;
	}

	switch (action)
	{
		case GLFW_PRESS:
			EventManager::instance ()->fireEvent (Event::KeyPress,   &k);
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

#ifndef NODATA
	// TODO: get window name and size from data
#else
	_windowName = "test";
	_windowWidth  = 1280;
	_windowHeight = 720;
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

	_canvas = (Image*) MemoryManager::instance ()->allocAsset
		(sizeof (Image) + _windowWidth * _windowHeight * sizeof (Color));
	_canvas->width  = _windowWidth;
	_canvas->height = _windowHeight;
	clearCanvas ();

	GLuint texture;
	glGenTextures (1, &texture);
	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture (GL_TEXTURE_2D, 0);

	GLfloat vertices[] = {
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,	 0.0f, 1.0f
	};
	_vertices = new GLfloat[32];
	memcpy (_vertices, vertices, 32 * sizeof (GLfloat));

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	_indices = new GLuint[6];
	memcpy (_indices, indices, 6 * sizeof (GLuint));

	glGenBuffers (1, &_VBO);
	glGenVertexArrays (1, &_VAO);
	glGenBuffers (1, &_EBO);

	glBindVertexArray (_VAO);
	glBindBuffer (GL_ARRAY_BUFFER, _VBO);
	glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, 32 * sizeof (GLfloat), _indices,
		GL_STATIC_DRAW);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
		(GLvoid*) 0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
		(GLvoid*) (3 * sizeof (GLfloat)));
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (GLfloat),
		(GLvoid*) (6 * sizeof (GLfloat)));
	glEnableVertexAttribArray (2);
	glBindVertexArray (0);

	initShaderProgram ();
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
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClear (GL_COLOR_BUFFER_BIT);

	// draw
	glBindTexture (GL_TEXTURE_2D, _texture);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, _canvas->width, _canvas->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, _canvas);
	glGenerateMipmap (GL_TEXTURE_2D);
	glUseProgram (_shaderProgram);
	glBindVertexArray (_VAO);
	glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray (0);
	glBindTexture (GL_TEXTURE_2D, 0);

	glfwSwapBuffers (_window);
	clearCanvas ();
}

// scale algorithm: bilinear interpolation

void DisplayManager::drawImg (const Image *img, u32 x, u32 y, f32 scale)
{
	u16 newWidth  = img->width  * scale;
	u16 newHeight = img->height * scale;
	// old central coord
	u16 oX = img->width  / 2;
	u16 oY = img->height / 2;
	// new central coord
	u16 nX = newWidth  / 2;
	u16 nY = newHeight / 2;
	for (int i = 0; i < newHeight; ++i)
		for (int j = 0; j < newWidth; ++j)
		{
			Color c;
			if (scale == 1.0f)
			{
				u32 ind = i * img->height + j;
				c.red   = img->image[ind].red;
				c.green = img->image[ind].green;
				c.blue  = img->image[ind].blue;
				c.alpha = img->image[ind].alpha;
			}
			else
			{
				// coord calculated
				u16 cX = j / scale;
				u16 cY = i / scale; 
				u32 ind1 =  cX      * img->height + cY;
				u32 ind2 = (cX + 1) * img->height + cY;
				u32 ind3 =  cX      * img->height + cY + 1;
				u32 ind4 = (cX + 1) * img->height + cY + 1;
				// fractional part
				f32 fX = j / scale - cX;
				f32 fY = i / scale - cY; 
				// weight of (cX,cY), (cX+1,cY), (cX,cY+1), (cX+1,cY+1)
				f32 w1 = (1 - fX) * (1 - fY);
				f32 w2 =      fX  * (1 - fY);
				f32 w3 = (1 - fX) *      fY;
				f32 w4 =      fX  *      fY;
				c.red   = img->image[ind1].red   * w1 + img->image[ind2].red   * w2
				         +img->image[ind3].red   * w3 + img->image[ind4].red   * w4;
				c.green = img->image[ind1].green * w1 + img->image[ind2].green * w2
				         +img->image[ind3].green * w3 + img->image[ind4].green * w4;
				c.blue  = img->image[ind1].blue  * w1 + img->image[ind2].blue  * w2
				         +img->image[ind3].blue  * w3 + img->image[ind4].blue  * w4;
				c.alpha = img->image[ind1].alpha * w1 + img->image[ind2].alpha * w2
				         +img->image[ind3].alpha * w3 + img->image[ind4].alpha * w4;
			}
			u16 rX = nX + (j - oX);
			u16 rY = nY + (i - oY);
			_canvas->image[rY * _canvas->width + rX] = c;
		}
}

void DisplayManager::initShaderProgram ()
{
	// vertex shader

	const char *vertexShaderCode = "\
	#version 330 core\n\
	layout (location = 0) in vec3 position;\
	layout (location = 1) in vec3 color;\
	layout (location = 2) in vec2 texCoord;\
	out vec4 vertexColor;\
	out vec2 TexCoord;\
	void main ()\
	{\
		gl_Position = vec4 (position.x, position.y, position.z, 1.0f);\
		vertexColor = vec4 (color, 1.0f);\
		TexCoord = vec2 (texCoord.x, 1.0f - texCoord.y);\
	}\
	";
	GLuint vertexShader = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader (vertexShader);
	GLint vertexShaderSuccess;
	GLchar infoLog[512];
	glGetShaderiv (vertexShader, GL_COMPILE_STATUS, &vertexShaderSuccess);
	if (!vertexShaderSuccess)
	{
		// TODO: error handling
		//glGetShaderInfoLog (vertexShader, 512, NULL, infoLog);
		//std::cout << "Vertex shader compilation failed!" << std::endl
		//	<< infoLog << std::endl;
	}

	// fragment shader
	
	const char *fragmentShaderCode = "\
	#version 330 core\n\
	in vec4 vertexColor;\
	in vec2 TexCoord;\
	out vec4 color;\
	uniform sampler2D Texture;\
	void main ()\
	{\
		color = texture (Texture, TexCoord);\
	}\
	";
	GLuint fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader (fragmentShader);
	GLint fragmentShaderSuccess;
	glGetShaderiv (fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSuccess);
	if (!fragmentShaderSuccess)
	{
		// TODO: error handling
		//glGetShaderInfoLog (vertexShader, 512, NULL, infoLog);
		//std::cout << "Fragment shader compilation failed!" << std::endl
		//	<< infoLog << std::endl;
	}

	// shader program

	_shaderProgram = glCreateProgram ();
	glAttachShader (_shaderProgram, vertexShader);
	glAttachShader (_shaderProgram, fragmentShader);
	glLinkProgram (_shaderProgram);
	GLint shaderProgramSuccess;
	glGetProgramiv (_shaderProgram, GL_LINK_STATUS, &shaderProgramSuccess);
	if (!shaderProgramSuccess)
	{
		// TODO: error handling
		//glGetProgramInfoLog (_shaderProgram, 512, NULL, infoLog);
		//std::cout << "Shader program linking failed!" << std::endl
		//	<< infoLog << std::endl;
	}

	glDeleteShader (vertexShader);
	glDeleteShader (fragmentShader);
}

void DisplayManager::clearCanvas ()
{
	for (int i = 0; i < _canvas->height; ++i)
		for (int j = 0; j < _canvas->width; ++j)
			_canvas->image[i * _canvas->width + j] = Color (0, 0, 0, 255);
}

}