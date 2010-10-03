#include "OUAN_Precompiled.h"

#include "GameOptionsState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIOptionsMenu.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "../Utils/Utils.h"
#include "GameStateManager.h"

#include "MainMenuState.h"

using namespace OUAN;


/// Default constructor
GameOptionsState::GameOptionsState()
:GameState()
,mClickChannel(-1)
,mMusicChannel(-1)
{
}
/// Destructor
GameOptionsState::~GameOptionsState()
{

}

/// init main menu's resources
void GameOptionsState::init(ApplicationPtr app)
{
	using namespace CEGUI;
	GameState::init(app);

	mGUI= BOOST_PTR_CAST(GUIOptionsMenu,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_OPTIONS));
	mGUI->initGUI(shared_from_this());

	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_9;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=OPTIONS_MATERIAL_NAME;
	desc.materialGroup=OPTIONS_GROUP;
	desc.textureName=OPTIONS_IMG;
	desc.sceneNodeName=OPTIONS_SCREENNODE;

	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());	

	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);

	//mApp->getAudioSubsystem()->load("MUSIC",AUDIO_RESOURCES_GROUP_NAME);
	//mApp->getAudioSubsystem()->playMusic("MUSIC",mMusicChannel,true);
}

/// Clean up main menu's resources
void GameOptionsState::cleanUp()
{
	GameState::cleanUp();

	//mApp->getGUISubsystem()->unbindAllEvents();
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	//if (mMusicChannel!=-1)
	//	mApp->getAudioSubsystem()->stopMusic(mMusicChannel);
	//mApp->getAudioSubsystem()->unload("MUSIC");
	
	Utils::destroyTexturedRectangle(mScreen,OPTIONS_MATERIAL_NAME,mApp->getRenderSubsystem());
}

/// pause state
void GameOptionsState::pause()
{

}
/// resume state
void GameOptionsState::resume()
{
	GameState::resume();
	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);
}

/// process input events
/// @param app	the parent application
void GameOptionsState::handleEvents()
{
}

/// Update game according to the current state
/// @param app	the parent app
void GameOptionsState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
}

void GameOptionsState::backToMenu()
{
	mApp->getGameStateManager()->popState();
	//GameStatePtr nextState(new MainMenuState());
	//mApp->getGameStateManager()->changeState(nextState,mApp);
}
bool GameOptionsState::keyPressed( const OIS::KeyEvent& e )
{
	if (mGUI.get())
	{
		return mGUI->keyPressed(e);
	}
	return false;
}
bool GameOptionsState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (mGUI.get())
	{
		return mGUI->mousePressed(e,id);
	}
	return false;
}

bool GameOptionsState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	if (mGUI.get())
	{
		return mGUI->buttonPressed(e,button);
	}
	return false;
}

