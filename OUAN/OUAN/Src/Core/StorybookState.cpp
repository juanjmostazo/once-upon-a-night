#include "OUAN_Precompiled.h"

#include "StorybookState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIStorybook.h"
#include "../Utils/Utils.h"
#include "../Game/GameWorldManager.h"
#include "GameStateManager.h"

#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"

using namespace OUAN;

/// Default constructor
StorybookState::StorybookState()
:GameState()
,mWhisperChannel(-1)
,mClickChannel(-1)
{

}
/// Destructor
StorybookState::~StorybookState()
{

}

/// init main menu's resources
void StorybookState::init(ApplicationPtr app)
{
	GameState::init(app);

	mGUI=BOOST_PTR_CAST(GUIStoryBook
		,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_STORYBOOK));
	mGUI->initGUI(shared_from_this());
	mGUI->showBook();

	int numParts=mApp->getGameWorldManager()->getPickedStoryParts();
	int totalParts=mApp->getGameWorldManager()->getTotalStoryParts();
	std::string entryName;
	std::string translatedValue;
	ConfigurationPtr texts=mApp->getStoryTextStrings();
	if (texts.get())
	{
		for (int i=0;i<totalParts;i++)
		{
			//Also use the name of the level...when there are levels (meaning never)
			entryName="STORY#LEVEL2#"+StringConverter::toString(i);
			texts->getOption(entryName,translatedValue);
			mGUI->setPageText(i,translatedValue,i<numParts);
		}
	}
	
	CameraParametersPtr params= CameraParametersPtr(new CameraParameters());
	mApp->getCameraManager()->setToDefaultCameraParameters(params);
	mApp->getCameraManager()->setCameraTrajectory(params,"camera-map",false,
true);
	if (!mApp->getAudioSubsystem()->isLoaded("book_loop"))
		mApp->getAudioSubsystem()->load("book_loop",
		AUDIO_RESOURCES_GROUP_NAME);
	mApp->getAudioSubsystem()->playSound("book_loop",mWhisperChannel);
	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",
		AUDIO_RESOURCES_GROUP_NAME);
}

/// Clean up main menu's resources
void StorybookState::cleanUp()
{
	GameState::cleanUp();

	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();

	mApp->getCameraManager()->setDefaultThirdPersonCamera(false);

	if (mApp->getAudioSubsystem()->isSfxPlaying(mWhisperChannel))
	{
		mApp->getAudioSubsystem()->stopSound(mWhisperChannel);
		mApp->getAudioSubsystem()->unload("book_loop");
	}

	if (mApp->getAudioSubsystem()->isSfxPlaying(mClickChannel))
	{
		mApp->getAudioSubsystem()->stopSound(mClickChannel);
		mApp->getAudioSubsystem()->unload("CLICK");
	}
}

/// pause state
void StorybookState::pause()
{

}
/// resume state
void StorybookState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void StorybookState::handleEvents()
{
	int pad;
	int key;

	if (mApp.get() && mApp->isPressedJump(&pad,&key))
	{
		mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void StorybookState::update(long elapsedTime)
{
	GameState::update(elapsedTime);

	mApp->getCameraManager()->update(elapsedTime*0.000001);
}