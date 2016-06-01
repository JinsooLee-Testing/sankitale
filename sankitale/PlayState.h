#pragma once

#include "GameState.h"

class PlayState : public GameState
{
public:
	void enter(void);
	void exit(void);

	void pause(void);
	void resume(void);

	bool frameStarted(GameManager* game, const Ogre::FrameEvent& evt);
	bool frameEnded(GameManager* game, const Ogre::FrameEvent& evt);

	bool mouseMoved(GameManager* game, const OIS::MouseEvent &e);
	bool mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool keyPressed(GameManager* game, const OIS::KeyEvent &e);
	bool keyReleased(GameManager* game, const OIS::KeyEvent &e);

	static PlayState* getInstance() { return &mPlayState; }

	void setAnimState(Ogre::AnimationState* anim) { mAnimationState = anim; }

private:
	//const Ogre::FrameEvent& evt;
	void _setLights(void);
	void _drawGroundPlane(void);
	void _drawGridPlane(void);
	void _drawStatusPlane(void);
	bool mContinue;
	static PlayState mPlayState;

	Ogre::Root *mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	Ogre::Light *mLightP, *mLightD, *mLightS;

	Ogre::SceneNode* mCharacterRoot;
	Ogre::SceneNode* mCharacterYaw;
	Ogre::SceneNode* mCameraHolder;
	Ogre::SceneNode* mCameraYaw;
	Ogre::SceneNode* mCameraPitch;
	

	
	Ogre::Vector3 mCharacterDirection;
	Ogre::Entity* mCharacterEntity;
	
	

	Ogre::AnimationState* mAnimationState;
	Ogre::AnimationState* mEnemyAnimState;
	Ogre::Overlay*           mInformationOverlay;
	int mPlayerState;
	int mCameraState;
	int mStatusState;
	int mStatusHeartState;
	enum {RIGHT_ROTATION,LEFT_ROTATION,NORMAL};
	enum  {IDLE,WALK,RUN};
	enum{STATUSOVERLAY,PLAY};
	enum{SAVE,BACK};

	Ogre::SceneNode* mSavePointRoot;
	Ogre::Entity* mSavePointEntity;


	Ogre::Overlay* mStatusOverlay;
	Ogre::Overlay* mHeartOverlay;
	//Ogre::Overlay* mBackHeartOverlay;
	Ogre::OverlayElement* mStatusMsg;
};