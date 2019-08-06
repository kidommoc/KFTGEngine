#ifndef KFTG_AUDIO_MANAGER
#define KFTG_AUDIO_MANAGER

#include "../types.hpp"
#include "../Module.hpp"
#include "../Singleton.hpp"

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

#endif // AUDIO_MANAGER