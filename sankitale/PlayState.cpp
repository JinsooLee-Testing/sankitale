#include "PlayState.h"
#include "TitleState.h"
#include "OptionState.h"

using namespace Ogre;

PlayState PlayState::mPlayState;


void PlayState::enter(void)
{
	/*mStatusOverlay = OverlayManager::getSingleton().getByName("Overlay/Status");
	mHeartOverlay = OverlayManager::getSingleton().getByName("Overlay/SaveHeart");
	mStatusMsg = OverlayManager::getSingleton().getOverlayElement("IDMsg");
	mStatusHeartState = SAVE;
	mContinue = true;
	mStatusState = PLAY;*/
	mRoot = Root::getSingletonPtr();
	mRoot->getAutoCreatedWindow()->resetStatistics();

	mSceneMgr = mRoot->getSceneManager("main");
	mCamera = mSceneMgr->getCamera("main");
	mCamera->setPosition(Ogre::Vector3::ZERO);

	_drawGridPlane();
	_setLights();
	_drawGroundPlane();

	mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
	mInformationOverlay->show();

	
	mCharacterRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerRoot");
	mCharacterYaw = mCharacterRoot->createChildSceneNode("PlayerYaw");
	//mCharacterYaw->yaw(Degree(180));
	
	mCharacterYaw->setScale(Vector3(10.0f, 10.0f, 10.0f));
	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));

	mCharacterEntity = mSceneMgr->createEntity("Player", "fish.mesh");
	mCharacterYaw->attachObject(mCharacterEntity);
	//mCharacterYaw->setScale(1000.0f, 1000.0f, 1000.0f);
	mCharacterEntity->setCastShadows(true);

	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());

	mCharacterDirection = Ogre::Vector3::ZERO;



	mSavePointRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");

	mSavePointEntity = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
	mSavePointRoot->attachObject(mSavePointEntity);
	mSavePointRoot->setPosition(Vector3(150.f, 0.0f, 150.f));
	mEnemyAnimState = mSavePointEntity->getAnimationState("Lift");
	mEnemyAnimState->setLoop(true);
	mEnemyAnimState->setEnabled(true);

}

void PlayState::exit(void)
{
	// Fill Here -----------------------------

	mSceneMgr->clearScene();
	mInformationOverlay->hide();
	// ---------------------------------------
}

void PlayState::pause(void)
{
	//_drawStatusPlane();
	mHeartOverlay->show();
	//if (mStatusHeartState == SAVE)	{ mBackHeartOverlay->show();   }
	//else if (mStatusHeartState == BACK)	{ mSaveHeartOverlay->show(); }
	mStatusOverlay->show();
	mStatusMsg->show();
	mEnemyAnimState->setLoop(false);
	mEnemyAnimState->setEnabled(false);
}

void PlayState::resume(void)
{
	mHeartOverlay->hide();
	/*mBackHeartOverlay->hide();  
	mSaveHeartOverlay->hide(); */
	mStatusOverlay->hide();
	mStatusMsg->hide();
	mEnemyAnimState->setLoop(true);
	mEnemyAnimState->setEnabled(true);
}

bool PlayState::frameStarted(GameManager* game, const FrameEvent& evt)
{
	mInformationOverlay =
		OverlayManager::getSingleton().getByName("Overlay/Information");
	mInformationOverlay->show();

	/*mAnimationState->addTime(evt.timeSinceLastFrame);*/
	mEnemyAnimState->addTime(evt.timeSinceLastFrame);
	static Vector3 offsetCamera = Vector3::ZERO;
	static const float cameraDragSpeed = 100.f;

	// Fill Here -------------------------------------------------------------------
	if (mCharacterDirection != Vector3::ZERO)
	{
		/*if (!mRunState->getEnabled())
		{
			mRunState->setEnabled(true);
			mIdleState->setEnabled(false);
		}*/
		//mRunState->addTime(evt.timeSinceLastFrame);

		static const float mCharacterSpeed = 400.f;

		mCharacterRoot->setOrientation(mCameraYaw->getOrientation());
		const Vector3 direction = mCharacterDirection.normalisedCopy();
		Quaternion quat = Vector3(Vector3::UNIT_Z).getRotationTo(mCharacterDirection);
		mCharacterYaw->setOrientation(quat);

		mCharacterRoot->translate(direction * mCharacterSpeed * evt.timeSinceLastFrame,
			Node::TransformSpace::TS_LOCAL);

		if (offsetCamera.length() < 150.f)
		{
			mCameraHolder->translate(-direction * cameraDragSpeed * evt.timeSinceLastFrame);
			offsetCamera += -direction * cameraDragSpeed * evt.timeSinceLastFrame;
		}
	}
	else
	{
		/*if (!mIdleState->getEnabled())
		{
			mIdleState->setEnabled(true);
			mRunState->setEnabled(false);
		}*/
		//mIdleState->addTime(evt.timeSinceLastFrame);

		if (offsetCamera.length() > 0)
		{
			const static float minLength = 10.f;
			if (offsetCamera.length() < minLength)
			{
				mCameraHolder->translate(-offsetCamera);
				offsetCamera = Vector3::ZERO;
			}
			else
			{
				const Vector3 cameraMovDir = -1 * offsetCamera.normalisedCopy();
				mCameraHolder->translate(cameraMovDir * cameraDragSpeed * evt.timeSinceLastFrame);
				offsetCamera += cameraMovDir * cameraDragSpeed * evt.timeSinceLastFrame;
			}
		}
	}

	//if (WALK == mPlayerState)
	//{
	//	mAnimationState->setEnabled(false);
	//	//mAnimationState = mCharacterEntity->getAnimationState("Walk");
	//	mAnimationState->setLoop(true);
	//	mAnimationState->setEnabled(true);
	//}
	//else if (RUN == mPlayerState)
	//{
	//	mAnimationState->setEnabled(false);
	//	//mAnimationState = mCharacterEntity->getAnimationState("Run");
	//	mAnimationState->setLoop(true);
	//	mAnimationState->setEnabled(true);
	//}
	//else if (IDLE == mPlayerState)
	//{
	//	mAnimationState->setEnabled(false);
	//	mAnimationState = mCharacterEntity->getAnimationState("Idle");
	//	mAnimationState->setLoop(true);
	//	mAnimationState->setEnabled(true);
	//}
	return mContinue;
}

bool PlayState::frameEnded(GameManager* game, const FrameEvent& evt)
{
//#if 0
	static Ogre::DisplayString currFps = L"현재 FPS: ";
	static Ogre::DisplayString avgFps = L"평균 FPS: ";
	static Ogre::DisplayString bestFps = L"최고 FPS: ";
	static Ogre::DisplayString worstFps = L"최저 FPS: ";
	static Ogre::DisplayString position = L"Position: ";
	OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("AverageFps");
	OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("CurrFps");
	OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("BestFps");
	OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");
	OverlayElement* guiPos = OverlayManager::getSingleton().getOverlayElement("PlayerPos");
	const RenderTarget::FrameStats& stats = mRoot->getAutoCreatedWindow()->getStatistics();
	guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
	guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
	guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS));
	guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));
	guiPos->setCaption(position + StringConverter::toString(mCharacterRoot->getPosition()));
//#endif
	return mContinue;
}


bool PlayState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
	// Fill Here -------------------------------------------
	if (PLAY == mStatusState)
	{
		switch (e.key)
		{
		case OIS::KC_W: case OIS::KC_UP:    mCharacterDirection.z += -1.f; break;
		case OIS::KC_S: case OIS::KC_DOWN:  mCharacterDirection.z += 1.f; break;
		case OIS::KC_A: case OIS::KC_LEFT:  mCharacterDirection.x += -1.f; break;
		case OIS::KC_D: case OIS::KC_RIGHT: mCharacterDirection.x += 1.f; break;
		//case OIS::KC_UP:case OIS::KC_W:
		//{mPlayerState = WALK;
		//mCharacterDirection.z += -1.f;	}break;
		//case OIS::KC_DOWN:case OIS::KC_S:
		//{mPlayerState = WALK; mCharacterDirection.z += 1.f;	}break;
		//case OIS::KC_LEFT: case OIS::KC_A:
		//{mPlayerState = WALK; mCharacterDirection.x += -1.f; }break;
		//case OIS::KC_RIGHT: case OIS::KC_D:
		//{mPlayerState = WALK; mCharacterDirection.x += 1.f; }break;
		//case OIS::KC_LSHIFT:
		//	//if (WALK == mPlayerState)
		//{mPlayerState = RUN; }break;
		case OIS::KC_ESCAPE:
			mContinue = false;
			//game->changeState(TitleState::getInstance());
			break;
		case OIS::KC_X:
				pause();
				mStatusState = STATUSOVERLAY;

			break;

		}
	}
	else if (STATUSOVERLAY == mStatusState)
	{
		switch (e.key)
		{
		case OIS::KC_LEFT:
		{
			if (mStatusHeartState == SAVE)	{ 
				
				mStatusHeartState = BACK; }
			else if (mStatusHeartState == BACK)	{ mStatusHeartState = SAVE; }

		}
		break;
		case OIS::KC_RIGHT:
		{
			if (mStatusHeartState == SAVE)	{ mStatusHeartState = BACK; }
			else if (mStatusHeartState == BACK)	{ mStatusHeartState = SAVE; }
		}
		break;
		case OIS::KC_X:
			resume();
			mStatusState = PLAY;
			break;
		case OIS::KC_ESCAPE:
			mContinue = false;
			break;
		}
		
	}
	// -----------------------------------------------------
	return true;
}

bool PlayState::keyReleased(GameManager* game, const OIS::KeyEvent &e)
{
	if (PLAY == mStatusState){
		switch (e.key)
		{
		case OIS::KC_W: case OIS::KC_UP:    mCharacterDirection.z -= -1.f; break;
		case OIS::KC_S: case OIS::KC_DOWN:  mCharacterDirection.z -= 1.f; break;
		case OIS::KC_A: case OIS::KC_LEFT:  mCharacterDirection.x -= -1.f; break;
		case OIS::KC_D: case OIS::KC_RIGHT: mCharacterDirection.x -= 1.f; break;
		}
	}
	//case OIS::KC_UP: case OIS::KC_W:
	//	if (WALK == mPlayerState || RUN == mPlayerState){ mPlayerState = IDLE; mCharacterDirection.z -= -1.f; }break;
	//case OIS::KC_DOWN:case OIS::KC_S:
	//	if (WALK == mPlayerState || RUN == mPlayerState){ mPlayerState = IDLE; mCharacterDirection.z -= 1.f; }break;
	//case OIS::KC_LEFT: case OIS::KC_A:
	//	if (WALK == mPlayerState || RUN == mPlayerState){ mPlayerState = IDLE; mCharacterDirection.x -= -1.f; }break;
	//case OIS::KC_RIGHT: case OIS::KC_D:
	//	if (WALK == mPlayerState || RUN == mPlayerState){ mPlayerState = IDLE; mCharacterDirection.x -= 1.f; }break;
	//case OIS::KC_LSHIFT:
	//	//if (RUN == mPlayerState)
	//{ mPlayerState = WALK; }break;
	//}
	return true;
}
bool PlayState::mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

bool PlayState::mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}


bool PlayState::mouseMoved(GameManager* game, const OIS::MouseEvent &e)
{
	if (PLAY == mStatusState)
	{
		mCameraYaw->yaw(Degree(-e.state.X.rel));
		mCameraPitch->pitch(Degree(-e.state.Y.rel));

		mCameraHolder->translate(Ogre::Vector3(0, 0, -e.state.Z.rel * 0.1f));
	}
	return true;
}

void PlayState::_drawStatusPlane(void)
{
	
	
	
	/*Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		2000, 2000,
		1, 1,
		true, 1, 1, 1,
		Vector3::NEGATIVE_UNIT_Z
		);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("ruin_first");
	groundEntity->setCastShadows(false);*/
}

void PlayState::_setLights(void)
{
	mSceneMgr->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	mLightD = mSceneMgr->createLight("LightD");
	mLightD->setType(Light::LT_DIRECTIONAL);
	mLightD->setDirection(Vector3(1, -2.0f, -1));
	mLightD->setVisible(true);
}

void PlayState::_drawGroundPlane(void)
{
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		2000, 2000,
		1, 1,
		true, 1, 1, 1,
		Vector3::NEGATIVE_UNIT_Z
		);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("ruin_first");
	groundEntity->setCastShadows(false);
}

void PlayState::_drawGridPlane(void)
{
	// 좌표축 표시
	Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode", Ogre::Vector3(0, 0, 0))->attachObject(mAxesEntity);
	mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

	Ogre::ManualObject* gridPlane = mSceneMgr->createManualObject("GridPlane");
	Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

	Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
	gridPlaneMaterial->setReceiveShadows(false);
	gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

	gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	for (int i = 0; i<21; i++)
	{
		gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
		gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

		gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
		gridPlane->position(-500.f + i * 50, 0.f, -500.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}

