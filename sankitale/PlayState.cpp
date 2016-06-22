#include "PlayState.h"
#include "TitleState.h"
#include "OptionState.h"

using namespace Ogre;

PlayState PlayState::mPlayState;


void PlayState::enter(void)
{
	mAnimationOperation = IDLE;
	mContinue = true;
	mRoot = Root::getSingletonPtr();
	mRoot->getAutoCreatedWindow()->resetStatistics();

	mSceneMgr = mRoot->getSceneManager("main");
	mCamera = mSceneMgr->getCamera("main");
	mCamera->setPosition(Ogre::Vector3::ZERO);

	//_drawGridPlane();
	_setLights();
	_drawGroundPlane();

	mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
	mInformationOverlay->show();

	mCharacterRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");
	mCharacterYaw = mCharacterRoot->createChildSceneNode("ProfessorYaw");
	mDoorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Door", Vector3(0, 0, -300.0f));
	//mSavePointRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("SavePoint",Vector3(0,50.0f,30.0f));
	
	//mSavePointYaw = mCharacterRoot->createChildSceneNode("SavePointYaw");
	mCharacterDirection = Ogre::Vector3::ZERO;

	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));
	mCameraYaw->yaw(Degree(180));
	mCameraYaw->setInheritOrientation(false);

	mCharacterEntity = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
	mCharacterYaw->attachObject(mCharacterEntity);
	mCharacterEntity->setCastShadows(true);

	//mSavePointEntity = mSceneMgr->createEntity("SavePoint", "savedefault.mesh");
	//mSavePointRoot->attachObject(mSavePointEntity);
	//mSavePointEntity->setCastShadows(true);
	//mSavePointRoot->setScale(Vector3(1500, 1500, 1500));

	mDoorEntity = mSceneMgr->createEntity("Door", "Door.mesh");
	mDoorNode->attachObject(mDoorEntity);
	mDoorEntity->setCastShadows(true);
	mDoorNode->setScale(Vector3(2000.0f, 2000.0f, 2000.0f));
	mDoorNode->pitch(Degree(90));

	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());


	mAnimationState = mCharacterEntity->getAnimationState("Idle");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);
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
	//	mAnimationState = mCharacterEntity->getA
	//	mAnimationState = mCharacterEntity->getAnimationState("Run");
	//mRunAnimState->setLoop(false);
	//mRunAnimState->setEnabled(false);
}

void PlayState::resume(void)
{
	//	mAnimationState = mCharacterEntity->Anima`
	//mRunAnimState->setLoop(true);
	//mRunAnimState->setEnabled(true);
}

bool PlayState::frameStarted(GameManager* game, const FrameEvent& evt)
{
	mAnimationState->addTime(evt.timeSinceLastFrame);
	const float CHARACTER_MOVE_SPEED = 666.0f;
	if (mCharacterDirection != Vector3::ZERO)
	{
		mCharacterRoot->setOrientation(mCameraYaw->getOrientation());
		Quaternion quat = Vector3(Vector3::UNIT_Z).getRotationTo(mCharacterDirection);
		mCharacterYaw->setOrientation(quat);
		//camerarotate();
		mCharacterRoot->translate(mCharacterDirection.normalisedCopy() * CHARACTER_MOVE_SPEED * evt.timeSinceLastFrame
			, Node::TransformSpace::TS_LOCAL);
	}
	else
	{
	}


	return mContinue;
}

bool PlayState::frameEnded(GameManager* game, const FrameEvent& evt)
{
#if 0
	static Ogre::DisplayString currFps = L"현재 FPS: ";
	static Ogre::DisplayString avgFps = L"평균 FPS: ";
	static Ogre::DisplayString bestFps = L"최고 FPS: ";
	static Ogre::DisplayString worstFps = L"최저 FPS: ";
	OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("AverageFps");
	OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("CurrFps");
	OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("BestFps");
	OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");
	const RenderTarget::FrameStats& stats = mRoot->getAutoCreatedWindow()->getStatistics();
	guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
	guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
	guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS));
	guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS));
#endif
	return mContinue;
}


bool PlayState::keyReleased(GameManager* game, const OIS::KeyEvent &e)
{
	switch (e.key)
	{
	case OIS::KC_W: case OIS::KC_UP:   
		mAnimationOperation = IDLE;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.z -= -1.f;

		break;
	case OIS::KC_S: case OIS::KC_DOWN: 
		mAnimationOperation = IDLE;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.z -= 1.f;
		break;
	case OIS::KC_A: case OIS::KC_LEFT: 
		mAnimationOperation = IDLE;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.x -= -1.f;
		break;
	case OIS::KC_D: case OIS::KC_RIGHT: 
		mAnimationOperation = IDLE;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Idle");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.x -= 1.f; 
		break;
	case OIS::KC_ESCAPE: mContinue = false; break;
	}

	return true;
}

bool PlayState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
	// Fill Here -------------------------------------------
	switch (e.key)
	{
	case OIS::KC_W: case OIS::KC_UP: 
		mAnimationOperation = WALK;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.z += -1.f; 
		break;
	case OIS::KC_S: case OIS::KC_DOWN:  
		mAnimationOperation = WALK;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.z += 1.f;
		break;
	case OIS::KC_A: case OIS::KC_LEFT: 
		mAnimationOperation = WALK;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.x += -1.f;
		break;
	case OIS::KC_D: case OIS::KC_RIGHT: 
		mAnimationOperation = WALK;
		mAnimationState->setEnabled(false);
		mAnimationState = mCharacterEntity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
		mAnimationState->setEnabled(true);
		mCharacterDirection.x += 1.f; 
		break;
	case OIS::KC_ESCAPE: mContinue = false; break;
	}
	// -----------------------------------------------------
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
	mCameraYaw->yaw(Degree(-e.state.X.rel*0.5f));
	mCameraHolder->translate(Ogre::Vector3(0, 0, -e.state.Z.rel * 0.01f));
	return true;
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
			10000, 1000,
			1, 1,
			true, 1, 1, 1,
			Vector3::NEGATIVE_UNIT_Z
			);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	//attachObject(groundEntity);
	mGroundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundPlane");
	mGroundNode->setPosition(0, 0, 4800);
	mGroundNode->yaw(Degree(90));
	mGroundNode->attachObject(groundEntity);
	groundEntity->setMaterialName("UnderGround");
	groundEntity->setCastShadows(false);	

	

	Plane brick(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Brick",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		brick,
		10000, 1000,
		1, 1,
		true, 1,1, 1,
		Vector3::NEGATIVE_UNIT_Z
		);
	Entity* brickEntity = mSceneMgr->createEntity("BrickPlane", "Brick");
	mBrickNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BrickPlane");
	mBrickNode->setPosition(500.0f, 500.0f, 4800.0f);
	mBrickNode->roll(Degree(90), Ogre::Node::TS_WORLD);
	mBrickNode->pitch(Degree(90), Ogre::Node::TS_WORLD);
	//mBrickNode->yaw(Degree(90), Ogre::Node::TS_WORLD);
	mBrickNode->attachObject(brickEntity);
	brickEntity->setMaterialName("BRICK");
	brickEntity->setCastShadows(true);

	Plane brick2(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Brick2",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		brick,
		10000, 1000,
		1, 1,
		true, 1, 1, 1,
		Vector3::NEGATIVE_UNIT_Z
		);
	Entity* brickEntity2 = mSceneMgr->createEntity("BrickPlane2", "Brick2");
	mBrickNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("BrickPlane2");
	mBrickNode2->setPosition(-500.0f, 500.0f, 4800.0f);
	mBrickNode2->roll(Degree(90), Ogre::Node::TS_WORLD);
	mBrickNode2->pitch(Degree(90), Ogre::Node::TS_WORLD);
	mBrickNode2->yaw(Degree(180), Ogre::Node::TS_WORLD);
	mBrickNode2->attachObject(brickEntity2);
	brickEntity2->setMaterialName("BRICK");
	brickEntity2->setCastShadows(true);

	Plane portal(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"portal",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		portal,
		1000, 1000,
		1, 1,
		true, 1, 1, 1,
		Vector3::NEGATIVE_UNIT_Z
		);
	Entity* portalEntity = mSceneMgr->createEntity("portalPlane", "portal");
	mPortalNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("portalPlane");
	mPortalNode->setPosition(0, 250, 10000);
	mPortalNode->roll(Degree(90), Ogre::Node::TS_WORLD);
	//mPortalNode->pitch(Degree(270), Ogre::Node::TS_WORLD);
	mPortalNode->yaw(Degree(270), Ogre::Node::TS_WORLD);
	mPortalNode->attachObject(portalEntity);
	portalEntity->setMaterialName("PORTAL");
	portalEntity->setCastShadows(true);
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
	for (int i = 0; i < 21; i++)
	{
		gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
		gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

		gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
		gridPlane->position(-500.f + i * 50, 0.f, -500.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}