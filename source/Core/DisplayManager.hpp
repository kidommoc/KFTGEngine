#ifndef KFTG_DISPLAY_MANAGER
#define KFTG_DISPLAY_MANAGER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"
#include "../Common/types.hpp"
#include "string.hpp"
#include "AssetTypes.hpp"

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

	GLFWwindow* getWindowHandle () const { return _window; }
	void drawImg (const Image *img, u32 x, u32 y, f32 scale);
	//void drawText (const string &str, u32 x, u32 y, u16 typeSize);

private:
	DisplayManager () {}
	void initShaderProgram ();
	void clearCanvas ();

	GLFWwindow *_window;
	string _windowName;
	u32 _windowWidth;
	u32 _windowHeight;
	u32 _bufWidth;
	u32 _bufHeight;
	Image *_canvas;

	GLfloat *_vertices;
	GLuint *_indices;
	GLuint _texture;
	GLuint _VBO;
	GLuint _VAO;
	GLuint _EBO;
	GLuint _shaderProgram;
};

}

#endif // DISPLAY_MANAGER