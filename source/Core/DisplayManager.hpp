#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"
#include "../Common/types.hpp"

namespace KFTG
{

class DisplayManager : public LoopModule, public Singleton
{
public:
	~DisplayManager () {}
	virtual void init ();
	virtual void exit ();
	virtual void loop ();

private:
	DisplayManager () {}
};

}