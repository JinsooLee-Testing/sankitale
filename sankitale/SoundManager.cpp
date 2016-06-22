#include"SoundManager.h"
#include"fmod_errors.h"

SoundManager* SoundManager::sharedManager()
{
	if (instance == nullptr) instance = new SoundManager;
	return instance;
}

void SoundManager::loading()
{
	//result = mFmod->createSound("INTRO_SOUND", FMOD_DEFAULT, nullptr, &mSound[INTRO_SOUND]);
	result = mFmod->createSound("Sound/TITLE.wav", FMOD_DEFAULT, nullptr, &mSound[TITLE_SOUND]);
	//result = mFmod->createSound("PLAY_SOUND", FMOD_DEFAULT, nullptr, &mSound[PLAY_SOUND]);
	//result = mFmod->createSound("SAVE_SOUND", FMOD_DEFAULT, nullptr, &mSound[SAVE_SOUND]);
}

void SoundManager::play(int type)
{
	mFmod->update();
	result = mFmod->playSound(FMOD_CHANNEL_FREE, mSound[type], false, &mChannel[type]);
		ErrorCheck(result);
}

void SoundManager::stop(int chNum)
{
	mChannel[chNum]->stop();
}

void SoundManager::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256] = { 0 };
		//std::cout << FMOD_ErrorString << std::endl;
	}
}