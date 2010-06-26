#include "OUAN_Precompiled.h"

#include "GamePausedState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"

using namespace OUAN;


/// Default constructor
GamePausedState::GamePausedState()
:GameState()
{

}
/// Destructor
GamePausedState::~GamePausedState()
{

}

/// init main menu's resources
void GamePausedState::init(ApplicationPtr app)
{
	mApp=app;	
	mApp->mKeyBuffer=-1;
	CameraParametersPtr cameraParameters;
	cameraParameters.reset(new CameraParameters());
	cameraParameters->setDefaultParameters();
	mApp->getCameraManager()->setCameraTrajectory(cameraParameters,"camera-map",false,true);
}

/// Clean up main menu's resources
void GamePausedState::cleanUp()
{
	mApp->mKeyBuffer=500000; //0.5s
	mApp->getCameraManager()->setDefaultThirdPersonCamera(true);
}

/// pause state
void GamePausedState::pause()
{

}
/// resume state
void GamePausedState::resume()
{

}

/// process input events
/// @param app	the parent application
void GamePausedState::handleEvents()
{
	if (mApp.get() && mApp->isPressedPause() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_PAUSE_SCREEN);
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GamePausedState::update(long elapsedTime)
{
	if (mApp.get() && mApp->mKeyBuffer>=0)
		mApp->mKeyBuffer-=elapsedTime;
	mApp->getCameraManager()->update(elapsedTime*0.000001);
}
bool GamePausedState::render()
{
	if (mApp.get() && mApp->getRenderSubsystem().get())
	{
		mApp->getRenderSubsystem()->showOverlay(OVERLAY_PAUSE_SCREEN);
		return mApp->getRenderSubsystem()->render();
	}
	return false;
}
