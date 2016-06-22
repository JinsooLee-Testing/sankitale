#pragma once
#include "fmod.hpp"
using namespace FMOD;
enum SOUND{
	INTRO_SOUND = 0,
	TITLE_SOUND,
	PLAY_SOUND,
	SAVE_SOUND
};

class SoundManager 
{
public:
	
	static SoundManager* getInstance() { return &mSoundManager; }
	void init();
	void loading();
	void play(int type);
	void stop(int chNum);
	void ErrorCheck(FMOD_RESULT r);

private:
	static SoundManager mSoundManager;
	System* mFmod;
	Channel* mChannel[4];
	Sound* mSound[4];
	FMOD_RESULT result;

};