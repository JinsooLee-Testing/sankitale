#include "PlayState.h"
#include "TitleState.h"
#include "OptionState.h"

using namespace Ogre;

PlayState PlayState::mPlayState;


void PlayState::enter(void)
{
	mCharacterAnimState = IDLE;
	mCharacterRotateState = NORMAL;
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

	mCharacterDirection = Ogre::Vector3::ZERO;

	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, -500.0f));

	mCharacterEntity = mSceneMgr->createEntity("Professor", "DustinBody.mesh");
	mCharacterYaw->attachObject(mCharacterEntity);
	mCharacterEntity->setCastShadows(true);

	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());

	mAnimatonState = mCharacterEntity->getAnimationState("Idle");
	mAnimatonState->setLoop(true);
	mAnimatonState->setEnabled(true);
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
	mAnimatonState->addTime(evt.timeSinceLastFrame);

	static Vector3 offsetCamera = Vector3::ZERO;
	static const float cameraDragSpeed = 100.f;

	static const float mCharacterSpeed = 400.f;
	camerarotate();
	//static Vector3 offsetCamera = Vector3::ZERO;
	//static const float cameraDragSpeed = 100.f;
	if (mCharacterAnimState = WALK)
	{
		if (mCharacterDirection != Vector3::ZERO)
		{
			
			const Vector3 direction = mCharacterDirection.normalisedCopy();
			mCharacterRoot->translate(direction * mCharacterSpeed * evt.timeSinceLastFrame, Node::TS_PARENT);
			//Node::TransformSpace::TS_LOCAL);
		}
	}
	//mCharacterRoot->setOrientation(mCameraYaw->getOrientation());
	//const Vector3 direction = mCharacterDirection.normalisedCopy();
	//Quaternion quat = Vector3(Vector3::UNIT_Z).getRotationTo(mCharacterDirection);
	//mCharacterYaw->setOrientation(quat);
	//mCameraYaw->setOrientation(quat);
	//mCharacterRoot->translate(direction * 400.f,
	//	Node::TransformSpace::TS_LOCAL);
	/*mCharacterRoot->setOrientation(mCameraYaw->getOrientation());
	const Vector3 direction = mCharacterDirection.normalisedCopy();
	Quaternion quat = Vector3(Vector3::UNIT_Z).getRotationTo(mCharacterDirection);
	mCharacterYaw->setOrientation(quat);

	mCharacterRoot->translate(direction * mCharacterSpeed * evt.timeSinceLastFrame,
		Node::TransformSpace::TS_LOCAL);*/

	// Fill Here -------------------------------------------------------------------
	//if (mCharacterDirection != Vector3::ZERO)
	//{
	//	//if (!mRunState->getEnabled())
	//	//{
	//	//	mRunState->setEnabled(true);
	//	//	mIdleState->setEnabled(false);
	//	//}
	//	//mRunState->addTime(evt.timeSinceLastFrame);

	//	static const float mCharacterSpeed = 400.f;

	//	mCharacterRoot->setOrientation(mCameraYaw->getOrientation());
	//	const Vector3 direction = mCharacterDirection.normalisedCopy();
	//	Quaternion quat = Vector3(Vector3::UNIT_Z).getRotationTo(mCharacterDirection);
	//	mCharacterYaw->setOrientation(quat);

	//	mCharacterRoot->translate(direction * mCharacterSpeed * evt.timeSinceLastFrame,
	//		Node::TransformSpace::TS_LOCAL);

	//	if (offsetCamera.length() < 150.f)
	//	{
	//		mCameraHolder->translate(-direction * cameraDragSpeed * evt.timeSinceLastFrame);
	//		offsetCamera += -direction * cameraDragSpeed * evt.timeSinceLastFrame;
	//	}
	//}
	//else
	//{
	//	//if (!mIdleState->getEnabled())
	//	//{
	//	//	mIdleState->setEnabled(true);
	//	//	mRunState->setEnabled(false);
	//	//}
	//	//mIdleState->addTime(evt.timeSinceLastFrame);

	//	if (offsetCamera.length() > 0)
	//	{
	//		const static float minLength = 10.f;
	//		if (offsetCamera.length() < minLength)
	//		{
	//			mCameraHolder->translate(-offsetCamera);
	//			offsetCamera = Vector3::ZERO;
	//		}
	//		else
	//		{
	//			const Vector3 cameraMovDir = -1 * offsetCamera.normalisedCopy();
	//			mCameraHolder->translate(cameraMovDir * cameraDragSpeed * evt.timeSinceLastFrame);
	//			offsetCamera += cameraMovDir * cameraDragSpeed * evt.timeSinceLastFrame;
	//		}
	//	}
	//}
	return mContinue;
}

bool PlayState::frameEnded(GameManager* game, const FrameEvent& evt)
{
#if 0
	static Ogre::DisplayString currFps = L"���� FPS: ";
	static Ogre::DisplayString avgFps = L"��� FPS: ";
	static Ogre::DisplayString bestFps = L"�ְ� FPS: ";
	static Ogre::DisplayString worstFps = L"���� FPS: ";
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
		mCharacterAnimState = IDLE;
		mAnimatonState = mCharacterEntity->getAnimationState("Idle");   
		mCharacterDirection.z -= 1.f;
		break;
	case OIS::KC_S: case OIS::KC_DOWN: mCharacterAnimState = IDLE;
		mAnimatonState = mCharacterEntity->getAnimationState("Idle");
		mCharacterDirection.z -= -1.f;
		break;
	case OIS::KC_A: case OIS::KC_LEFT: mCharacterRotateState = NORMAL;  break;
		//case OIS::KC_A: case OIS::KC_LEFT:  mCharacterDirection.x -= -1.f; break;
	case OIS::KC_D: case OIS::KC_RIGHT:  mCharacterRotateState = NORMAL; break;
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
		mCharacterAnimState = WALK;
		mAnimatonState = mCharacterEntity->getAnimationState("Walk");  
		mCharacterDirection.z += 1.f;
		break;
	case OIS::KC_S: case OIS::KC_DOWN:
		mCharacterAnimState = WALK;
		mAnimatonState = mCharacterEntity->getAnimationState("Walk");  
		mCharacterDirection.z += -1.f;
		break;
	case OIS::KC_A: case OIS::KC_LEFT: mCharacterRotateState = LEFT_ROTATE; break;
		//case OIS::KC_A: case OIS::KC_LEFT:  mCharacterDirection.x += -1.f; break;
	case OIS::KC_D: case OIS::KC_RIGHT: mCharacterRotateState = RIGHT_ROTATE; break;
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
	/*mCameraYaw->yaw(Degree(-e.state.X.rel));
	mCameraPitch->pitch(Degree(-e.state.Y.rel));

	mCameraHolder->translate(Ogre::Vector3(0, 0, -e.state.Z.rel * 0.1f));*/
	return true;
}

void PlayState::camerarotate()
{
	if (RIGHT_ROTATE == mCharacterRotateState)
	{

		
		mCameraYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(-1.f),
			Ogre::Node::TS_PARENT);
		mCharacterYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(-1.f),
			Ogre::Node::TS_PARENT);
	}
	else if (LEFT_ROTATE == mCharacterRotateState)
	{
		mCameraYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(1.f),
			Ogre::Node::TS_PARENT);
		mCharacterYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(1.f),
			Ogre::Node::TS_PARENT);
	}
	else if (NORMAL == mCharacterRotateState)
	{
		mCameraYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(0.f),
			Ogre::Node::TS_PARENT);
		mCharacterYaw->rotate(Ogre::Vector3::UNIT_Y,
			Ogre::Degree(0.f),
			Ogre::Node::TS_PARENT);
	}
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
		500, 500,
		1, 1,
		true, 1, 5, 5,
		Vector3::NEGATIVE_UNIT_Z
		);

	Entity* groundEntity = mSceneMgr->createEntity("GroundPlane", "Ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setMaterialName("KPU_LOGO");
	groundEntity->setCastShadows(false);
}

void PlayState::_drawGridPlane(void)
{
	// ��ǥ�� ǥ��
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