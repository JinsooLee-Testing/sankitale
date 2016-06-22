#include "TitleState.h"
#include "PlayState.h"
#include "IntroState.h"
using namespace Ogre;

//TitleState TitleState::getInstance()
TitleState TitleState::mTitleState;


void TitleState::enter(void)
{
  
  mContinue = true;
  mTitleOverlay = OverlayManager::getSingleton().getByName("Overlay/Title");
  mIntroSceneOverlay = {};
  mStartMsg = OverlayManager::getSingleton().getOverlayElement("StartMsg");
  mTitleOverlay->show();
  mStartMsg->show();
}

void TitleState::exit(void)
{
  mTitleOverlay->hide();
}

void TitleState::pause(void)
{
  std::cout << "TitleState pause\n";
}

void TitleState::resume(void)
{
  std::cout << "TitleState resume\n";
}

bool TitleState::frameStarted(GameManager* game, const FrameEvent& evt)
{
  static float elapsed = 0.0f;

  elapsed += evt.timeSinceLastFrame;

  if (elapsed >= 3.0f)
  {
	  //game->changeState(PlayState::getInstance());
    mStartMsg->show();
  }
  if (elapsed >= 5.0f)
  {
	  mStartMsg->hide();
	  //game->changeState(IntroState::getInstance());
  }


  return true;
}

bool TitleState::frameEnded(GameManager* game, const FrameEvent& evt)
{
  return mContinue;
}

bool TitleState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
  // Fill Here -------------------------------------------------------
	switch (e.key)
	{
	
	case OIS::KC_ESCAPE:
		mContinue = false;
		break;
	case OIS::KC_Z:
		game->changeState(PlayState::getInstance());
		break;
	default:
		
		break;
	}
  // -----------------------------------------------------------------

  return true;
}
