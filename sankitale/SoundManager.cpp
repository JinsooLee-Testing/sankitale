#include"SoundManager.h"
#include"fmod_errors.h"

#include<iostream>
SoundManager SoundManager::mSoundManager;

void SoundManager::init()
{
	result = System_Create(&mFmod);
	ErrorCheck(result);
	result = mFmod->init(100, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(result);
}

void SoundManager::loading()
{
	result = mFmod->createSound("Sound/INTRO.mp3", FMOD_DEFAULT, nullptr, &mSound[INTRO_SOUND]);
	result = mFmod->createSound("Sound/TITLE.wav", FMOD_DEFAULT, nullptr, &mSound[TITLE_SOUND]);
	result = mFmod->createSound("Sound/PLAYSTATE.mp3", FMOD_DEFAULT, nullptr, &mSound[PLAY_SOUND]);
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