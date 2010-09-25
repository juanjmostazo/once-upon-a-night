#include "OUAN_Precompiled.h"

#include "GameOverState.h"

#include "GameStateManager.h"
#include "MainMenuState.h"
#include "GameRunningState.h"
#include "LevelLoadingState.h"

#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Audio/AudioSubsystem.h"
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
	GameState::init(app);

	mApp->getGameWorldManager()->getGameObjectViewport()->disableAllCompositors();

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
	GameState::cleanUp();

	mApp->getAudioSubsystem()->unloadAll();
}

/// pause state
void GameOverState::pause()
{

}
/// resume state
void GameOverState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void GameOverState::handleEvents()
{
	int pad1,pad2;
	int key1,key2;

	if (mApp.get())
	{
		if (mApp->isPressedJump(&pad1,&key1))
		{
			mApp->getRenderSubsystem()->hideOverlay(OVERLAY_GAMEOVER_SCREEN);

			LevelLoadingStatePtr levelLoadingState(new LevelLoadingState());
			levelLoadingState->setLevelFileName(LEVEL_2);
			mApp->getGameStateManager()->changeState(levelLoadingState,mApp);

		}
		else if (mApp->isPressedPause(&pad2,&key2))
		{
			mApp->getRenderSubsystem()->hideOverlay(OVERLAY_GAMEOVER_SCREEN);
			
			GameStatePtr mainMenuState = GameStatePtr(new MainMenuState());
			mApp->getGameStateManager()->changeState(mainMenuState,mApp);
		}
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GameOverState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
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
