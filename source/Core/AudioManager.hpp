#pragma once

#include "../Common/types.hpp"
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"

namespace KFTG
{

// TODO: LEARN THEN FINISH IT
class AudioManager : public LoopModule, public Singleton
{
public:
	static AudioManager* instance ();
	~AudioManager ();
	virtual void init () override;
	virtual void exit () override;
	virtual void loop () override;

private:
	AudioManager ();
};

}