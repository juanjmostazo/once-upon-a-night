#include "MainMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIMainMenu.h"
#include "GameStateManager.h"
#include "GameRunningState.h"
#include "GameOptionsState.h"
#include "ExtrasState.h"

#include "../Audio/AudioDefs.h"
#include "../Audio/AudioSubsystem.h"

using namespace OUAN;

/// Default constructor
MainMenuState::MainMenuState()
:GameState()
{
	mMusicChannel=-1;
}
/// Destructor
MainMenuState::~MainMenuState()
{

}

/// init main menu's resources
void MainMenuState::init(ApplicationPtr app)
{
	mApp=app;	
	//mApp->getGUISubsystem()->loadScheme("OUANLookSkin.scheme","OUANLook");
	mGUI= boost::dynamic_pointer_cast<GUIMainMenu>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_MAINMENU));
	mGUI->initGUI(shared_from_this());

	TSoundData desc;
	desc.mId="MUSIC";
	desc.mFileName=MAINMENU_MUSIC_TRACK;
	desc.mChannelGroupID=SM_CHANNEL_MUSIC_GROUP;
	desc.mHardware=true;
	desc.m3D=false;
	desc.mStream=true;
	desc.mLoop=true;
	mApp->getAudioSubsystem()->addSound(desc);
	mApp->getAudioSubsystem()->playMusic("MUSIC",mMusicChannel,true);
}

/// Clean up main menu's resources
void MainMenuState::cleanUp()
{
	//Unsubscribe from events
	mGUI->destroy();
	if (mMusicChannel!=-1)
	mApp->getAudioSubsystem()->stopSound(mMusicChannel);
	mApp->getAudioSubsystem()->removeSound("MUSIC");
	mApp->getGUISubsystem()->destroyGUI();
	//mApp->getGUISubsystem()->unbindAllEvents();
}

/// pause state
void MainMenuState::pause()
{

}
/// resume state
void MainMenuState::resume()
{

}

/// process input events
/// @param app	the parent application
void MainMenuState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void MainMenuState::update(long elapsedTime)
{
	mApp->getAudioSubsystem()->update(elapsedTime*0.000001);
}

void MainMenuState::gotoPlay()
{
	//TODO: Change to ProfileSelectState when it's implemented
	GameStatePtr nextState(new GameRunningState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}

void MainMenuState::gotoOptions()
{
	GameStatePtr nextState(new GameOptionsState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}

void MainMenuState::gotoExtras()
{
	GameStatePtr nextState(new ExtrasState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}

void MainMenuState::quit()
{
	mApp->mExitRequested=true;
}