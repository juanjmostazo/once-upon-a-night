#include "GameOverState.h"

#include "GameStateManager.h"
#include "MainMenuState.h"
#include "GameRunningState.h"

#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Graphics/RenderSubsystem.h"


using namespace OUAN;


/// Default constructor
GameOverState::GameOverState()
:GameState()
{

}
/// Destructor
GameOverState::~GameOverState()
{

}

/// init main menu's resources
void GameOverState::init(ApplicationPtr app)
{
	mApp=app;	
	mApp->mKeyBuffer=-1;
	if (mApp->getGameWorldManager()->isGameBeaten())
	{
		mApp->getRenderSubsystem()->showOverlayElement("OUAN/GameOver/Gratz");
		mApp->getRenderSubsystem()->hideOverlayElement("OUAN/GameOver/GameOver");
	}
	else
	{
		mApp->getRenderSubsystem()->showOverlayElement("OUAN/GameOver/GameOver");
		mApp->getRenderSubsystem()->hideOverlayElement("OUAN/GameOver/Gratz");
	}
}

/// Clean up main menu's resources
void GameOverState::cleanUp()
{
	mApp->mKeyBuffer=-1;
}

/// pause state
void GameOverState::pause()
{

}
/// resume state
void GameOverState::resume()
{

}

/// process input events
/// @param app	the parent application
void GameOverState::handleEvents()
{
	if (mApp && (mApp->isPressedJump() || mApp->isPressedPause()) && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_GAMEOVER_SCREEN);
		mApp->mKeyBuffer=500000;
		GameStatePtr continueGameState = GameStatePtr(new GameRunningState());
		mApp->getGameStateManager()->changeState(continueGameState,mApp);
	}
	if (mApp && mApp->isPressedWeaponAction() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_GAMEOVER_SCREEN);
		mApp->mKeyBuffer=500000;
		GameStatePtr mainMenuState = GameStatePtr(new MainMenuState());
		mApp->getGameStateManager()->changeState(mainMenuState,mApp);
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GameOverState::update(long elapsedTime)
{
	if (mApp.get() && mApp->mKeyBuffer>=0)
		mApp->mKeyBuffer-=elapsedTime;
}
bool GameOverState::render()
{
	if (mApp.get() && mApp->getRenderSubsystem().get())
	{
		mApp->getRenderSubsystem()->showOverlay(OVERLAY_GAMEOVER_SCREEN);
		return mApp->getRenderSubsystem()->render();
	}
	return false;
}
