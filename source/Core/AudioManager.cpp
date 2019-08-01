#include "AudioManager.hpp"

namespace KFTG
{

AudioManager* AudioManager::instance ()
{
	static AudioManager _instance;
	return &_instance;
}

void AudioManager::init ()
{
}

void AudioManager::exit ()
{
}

void AudioManager::loop ()
{
}

}