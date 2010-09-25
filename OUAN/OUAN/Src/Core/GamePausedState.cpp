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
	GameState::init(app);

	CameraParametersPtr params= CameraParametersPtr(new CameraParameters());
	mApp->getCameraManager()->setToDefaultCameraParameters(params);
	mApp->getCameraManager()->setCameraTrajectory(params,"camera-map",false,true);
}

/// Clean up main menu's resources
void GamePausedState::cleanUp()
{
	GameState::cleanUp();

	mApp->getCameraManager()->setDefaultThirdPersonCamera(false);
}

/// pause state
void GamePausedState::pause()
{

}
/// resume state
void GamePausedState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void GamePausedState::handleEvents()
{
	int pad;
	int key;

	if (mApp.get() && mApp->isPressedPause(&pad,&key))
	{
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_PAUSE_SCREEN);
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GamePausedState::update(long elapsedTime)
{
	GameState::update(elapsedTime);

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
