#ifndef KFTG_LOGIC
#define KFTG_LOGIC

#include "../Core/Module.hpp"
#include "../Core/Singleton.hpp"
#include "../Core/types.hpp"
#include "World/World.hpp"

namespace KFTG
{

class Logic : public LoopModule, public Singleton
{
public:
	static Logic* instance ();
	~Logic () {}

	virtual void init () override;
	virtual void loop () override;
	virtual void exit () override;

private:
	Logic () {}

	World *_scene;
};

}

#endif // LOGIC