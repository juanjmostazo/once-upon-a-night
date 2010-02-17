#include "GameRunningState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Game/GameWorldManager.h"

using namespace OUAN;


/// Default constructor
GameRunningState::GameRunningState()
:GameState()
{

}
/// Destructor
GameRunningState::~GameRunningState()
{

}

/// Initialise main menu's resources
void GameRunningState::init(ApplicationPtr app)
{
	mApp=app;	
	//TODO: Do this at proper location
	mApp->getGameWorldManager()->loadLevel("TestLevel.ogscene");
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{

}

/// pause state
void GameRunningState::pause()
{

}
/// resume state
void GameRunningState::resume()
{

}

/// process input events
/// @param app	the parent application
void GameRunningState::handleEvents()
{
	if(mApp->getKeyboard()->isKeyDown(OIS::KC_A))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_NEG_X);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_D))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_POS_X);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_W))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_NEG_Z);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_S))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_POS_Z);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_Q))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_NEG_Y);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_E))
		mApp->getRenderSubsystem()->translateCam(OUAN::AXIS_POS_Y);

	if(mApp->getKeyboard()->isKeyDown(OIS::KC_LSHIFT))
		mApp->getRenderSubsystem()->relativeMoveCam();
	else
		mApp->getRenderSubsystem()->relativeMoveCam(10);
}

void GameRunningState::update(long elapsedTime)
{

	mApp->getRenderSubsystem()->updateCameraParams((float)elapsedTime*0.001);
	mApp->getRenderSubsystem()->relativeMoveCam();

}

bool GameRunningState::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
		mApp->mExitRequested= true;
	return true;
}
bool GameRunningState::mouseMoved(const OIS::MouseEvent &e)
{
	mApp->getRenderSubsystem()->moveCamera(e);
	return true;
}