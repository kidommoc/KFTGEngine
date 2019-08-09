#ifndef KFTG_LOGIC
#define KFTG_LOGIC

#include "../Core/Module.hpp"
#include "../Core/Singleton.hpp"
#include "../Core/types.hpp"

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

	//void loadScene ();

private:
	Logic () {}
};

}

#endif // LOGIC