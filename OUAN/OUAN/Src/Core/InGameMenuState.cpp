#include "OUAN_Precompiled.h"

#include "InGameMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIInGame.h"
#include "GameStateManager.h"

#include "MainMenuState.h"
#include "GameOptionsState.h"
#include "GameRunningState.h"

using namespace OUAN;


/// Default constructor
InGameMenuState::InGameMenuState()
:GameState()
,mClickChannel(-1)
{

}
/// Destructor
InGameMenuState::~InGameMenuState()
{

}

/// init main menu's resources
void InGameMenuState::init(ApplicationPtr app)
{
	Logger::getInstance()->log("IN GAME MENU INIT");
	GameState::init(app);

	mGUI=BOOST_PTR_CAST(GUIInGame,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_INGAMEMENU));
	mGUI->initGUI(shared_from_this());

	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
	{
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);
	}

	mApp->getGUISubsystem()->showCursor();
}

/// Clean up main menu's resources
void InGameMenuState::cleanUp()
{
	GameState::cleanUp();

	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	mApp->getGUISubsystem()->hideCursor();
}

/// pause state
void InGameMenuState::pause()
{
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
}
/// resume state
void InGameMenuState::resume()
{
	mGUI=BOOST_PTR_CAST(GUIInGame,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_INGAMEMENU));
	mGUI->initGUI(shared_from_this());
	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);
}

/// process input events
/// @param app	the parent application
void InGameMenuState::handleEvents()
{
	int pad;
	int key;

	if (mApp->isPressedMenu(&pad,&key))
	{
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void InGameMenuState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
}

void InGameMenuState::backToGame()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	mApp->getGameStateManager()->popState();
}

void InGameMenuState::goToOptions()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	GameStatePtr nextState(new GameOptionsState());
	//mApp->getGameStateManager()->changeState(nextState,mApp);
	mApp->getGameStateManager()->pushState(nextState,mApp);
}
void InGameMenuState::backToMenu()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	// if (openYesNoDialog("Are you sure you want to quit?"))
	mApp->mBackToMenu=true;
	mApp->getGameStateManager()->popState();
}
void InGameMenuState::quit()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	// if (openYesNoDialog("Are you sure you want to quit?"))
	mApp->mExitRequested=true;
}