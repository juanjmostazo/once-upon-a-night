#include "OUAN_Precompiled.h"

#include "Application.h"

#include "Graphics/RenderSubsystem.h"
#include "Graphics/CameraManager/CameraManager.h"
#include "Graphics/TrajectoryManager/TrajectoryManager.h"

#include "Core/GameStateManager.h"
#include "Core/GameState.h"
#include "Core/IntroState.h"
#include "Core/GameRunningState.h"
#include "Core/LevelLoadingState.h"

#include "GUI/GUISubsystem.h"

#include "Physics/PhysicsSubsystem.h"

#include "RayCasting/RayCasting.h"

#include "Logic/LogicSubsystem.h"

#include "Game/GameWorldManager.h"
#include "Component/ComponentFactory.h"

#include "Loader/Configuration.h"
#include "Loader/LevelLoader.h"

#include "Audio/AudioSubsystem.h"

#include "Game/GameObject/GameObjectTripolloDreams.h"
#include "Graphics/RenderComponent/RenderComponentPositional.h"

#include "Utils/Utils.h"

using namespace OUAN;

Application::Application(const std::string& windowName) : mWindowName(windowName)
,mDebugMode(DEBUGMODE_NONE)
,mKeyBuffer(-1)
,mUniqueId(1000)
,mSkipIntro(false)
,mBackToMenu(false)
{
	instance = this;
}

Application::~Application()
{

}

Application* Application::instance = NULL;

Application* Application::getInstance()
{
	return instance;
}

void Application::cleanUp()
{
	mAudioSubsystem->cleanUp();
	mPhysicsSubsystem->cleanUp();
	mGUISubsystem->cleanUp();
	mRenderSubsystem->cleanUp();
	mLogicSubsystem->cleanUp();
	ControlInputManager::finalise();
}

bool Application::init(int argc,char** argv)
{
	mConfiguration.reset(new Configuration());
	mConfiguration->loadFromFile(OUAN_CONFIG_FILE);

	mSkipIntro = mConfiguration->parseBool(CONFIG_KEYS_SKIP_INTRO);

	std::string languages;
	mConfiguration->getOption(CONFIG_KEYS_SUPPORTED_LANGUAGES,languages);
	mSupportedLanguages=Ogre::StringUtil::split(Ogre::String(languages),";");

	mConfiguration->getOption(CONFIG_KEYS_INITIAL_LANGUAGE, mLanguage);
	if (mLanguage.empty())
		mLanguage=DEFAULT_LANGUAGE;

	if (argc>1)
	{
		std::string option=argv[1];
		if (option.compare(SKIP_INTRO_CMD_LONG)==0 || option.compare(SKIP_INTRO_CMD_SHORT)==0)
		{
			mSkipIntro=true;
		}
	}
	//TODO: Reverse order, as the logical thing would be that the command line superceded
	// the config file options (since no options other than sound's are being processed at the moment,
	// it doesn't matter)
	return init();
}

//Application initialization
bool Application::init()
{	
	ApplicationPtr this_ = shared_from_this();

	mExitRequested=false;
	Utils::Random::getInstance()->init((unsigned)time(NULL));

	mStateManager.reset(new GameStateManager());


	mRenderSubsystem.reset(new RenderSubsystem(mWindowName));
	
	// Initialization has been split into two stages so the resourceManager for the
	// audio can be successfully registered
	mRenderSubsystem->create(this_, mConfiguration);

	ConfigurationPtr audioCfg(new Configuration());
	audioCfg->loadFromFile(SOUND_CONFIG_FILE);
	TAudioSubsystemConfigData audioDesc;
	audioDesc.set(audioCfg);
	mAudioSubsystem.reset(new AudioSubsystem());
	mAudioSubsystem->init(audioDesc,this_);
	//mSoundFileManager=SoundFileManagerPtr(new SoundFileManager());

	//Initialization is now effective.
	if (!mRenderSubsystem->init(mConfiguration)){
		return false;
	}

	mPhysicsSubsystem.reset(new PhysicsSubsystem());
	mPhysicsSubsystem->init(this_, mConfiguration);
	
	mRayCasting.reset(new RayCasting());
	mRayCasting->init(mRenderSubsystem,mPhysicsSubsystem);

	mTrajectoryManager.reset(new TrajectoryManager());
	mTrajectoryManager->init(mRenderSubsystem);

	mGameWorldManager.reset(new GameWorldManager());
	mGameWorldManager->init(this_);

	mCameraManager.reset(new CameraManager());
	mCameraManager->init(mRenderSubsystem,mTrajectoryManager,mPhysicsSubsystem,mRayCasting,mGameWorldManager);

	mGUISubsystem.reset(new GUISubsystem());
	mGUISubsystem->init(this_);

	mLogicSubsystem.reset(new LogicSubsystem());
	mLogicSubsystem->init(this_);

	mLevelLoader.reset(new LevelLoader());
	mLevelLoader->init(this_);

	//TODO: Add remaining subsystems ()

	setupInputSystem();

	return true;
}

//Run the app
void Application::go()
{
	Ogre::Timer loopTimer;
	bool continueRunning = true;

	unsigned long nextGameTicks = loopTimer.getMicroseconds();
	unsigned long lastTick=nextGameTicks;
	unsigned long currentTime;

	while ( continueRunning )
	{
		//int loops=0;
		//while((currentTime=loopTimer.getMicroseconds())>nextGameTicks && loops<MAX_FRAMESKIP)
		//{
			Ogre::WindowEventUtilities::messagePump();
			ControlInputManager::capture();

			currentTime=loopTimer.getMicroseconds();

			mGUISubsystem->injectTimePulse((currentTime-lastTick)*0.000001);
			mStateManager->getCurrentState()->handleEvents();
			mStateManager->getCurrentState()->update(currentTime-lastTick);

			//nextGameTicks+=SKIP_TICKS;
			//loops++;
			lastTick=currentTime;
		//}

		bool windowClosed = mRenderSubsystem->isWindowClosed();
		continueRunning &= ! windowClosed;
		bool renderFrameSuccess = mStateManager->getCurrentState()->render();
		continueRunning &= renderFrameSuccess;
		continueRunning &= ! mExitRequested;
	}
}

//------------------------
// Input event handling
//------------------------
bool Application::keyPressed( const OIS::KeyEvent& e )
{
	mGUISubsystem->injectKeyInput(OUAN::GUI_KEYDOWN,e);
	return mStateManager->getCurrentState()->keyPressed(e);
}

bool Application::keyReleased(const OIS::KeyEvent& e)
{	
	mGUISubsystem->injectKeyInput(OUAN::GUI_KEYUP,e);
	return mStateManager->getCurrentState()->keyReleased(e);
}

bool Application::mouseMoved(const OIS::MouseEvent &e)
{
	mGUISubsystem->injectMouseInput(OUAN::GUI_MOUSEMOVE,OIS::MB_Left,e);
	return mStateManager->getCurrentState()->mouseMoved(e);
}

bool Application::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	mGUISubsystem->injectMouseInput(OUAN::GUI_MOUSEDOWN,id,e);
	return mStateManager->getCurrentState()->mousePressed(e,id);
}

bool Application::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	mGUISubsystem->injectMouseInput(OUAN::GUI_MOUSEUP,id,e);
	return mStateManager->getCurrentState()->mouseReleased(e,id);
}

bool Application::buttonPressed( const OIS::JoyStickEvent& e, int button )
{
	//TODO: Bind to GUI
	// It might involve injecting fake key presses
	return mStateManager->getCurrentState()->buttonPressed(e,button);
}

bool Application::buttonReleased( const OIS::JoyStickEvent& e, int button )
{
	//TODO: Bind to GUI
	// It might involve injecting fake key presses, as CEGUI::System
	// does not seem to provide joystick injectors
	return mStateManager->getCurrentState()->buttonReleased(e,button);
}

void Application::setupInputSystem()
{
	//Set mouse pointer non-visible
	ControlInputManager::init( mRenderSubsystem->getWindow(), false );
}
void Application::loadInitialState()
{
	//GameStatePtr initialState(new GameRunningState());
	GameStatePtr initialState;
	if (mSkipIntro)
	{
		initialState.reset(new LevelLoadingState());
		LevelLoadingStatePtr ll = boost::dynamic_pointer_cast<LevelLoadingState>(initialState);
		if (ll.get())
		{
			ll->setLevelFileName(LEVEL_CLOCK);
		}
	}
	else
		initialState.reset(new IntroState());
	ApplicationPtr this_ = shared_from_this();
	mStateManager->changeState(initialState,this_);
}

int Application::getDebugMode() const{
	return mDebugMode;
}

void Application::setDebugMode(int debugMode)
{
	mDebugMode=debugMode;
}

GameStateManagerPtr Application::getGameStateManager() const
{
	return mStateManager;
}

RenderSubsystemPtr Application::getRenderSubsystem() const
{
	return mRenderSubsystem;
}

GUISubsystemPtr Application::getGUISubsystem() const
{
	return mGUISubsystem;
}

GameWorldManagerPtr Application::getGameWorldManager() const
{
	return mGameWorldManager;
}

PhysicsSubsystemPtr Application::getPhysicsSubsystem() const
{
	return mPhysicsSubsystem;
}

LevelLoaderPtr Application::getLevelLoader() const
{
	return mLevelLoader;
}

ConfigurationPtr Application::getConfiguration() const
{
	return mConfiguration;
}

ConfigurationPtr Application::getTextStrings() const
{
	return mTextStrings;
}

LogicSubsystemPtr Application::getLogicSubsystem() const
{
	return mLogicSubsystem;
}

AudioSubsystemPtr Application::getAudioSubsystem() const
{
	return mAudioSubsystem;
}

CameraManagerPtr Application::getCameraManager() const
{
	return mCameraManager;
}

TrajectoryManagerPtr Application::getTrajectoryManager() const
{
	return mTrajectoryManager;
}

RayCastingPtr Application::getRayCasting() const
{
	return mRayCasting;
}

void Application::getAudioConfig(TAudioSubsystemConfigData& audioCfg)
{
	if (mAudioSubsystem.get())
		audioCfg=mAudioSubsystem->getConfigData();
}

void Application::setAudioConfig(const TAudioSubsystemConfigData& audioCfg)
{
	if (mAudioSubsystem.get())
		mAudioSubsystem->setConfigData(audioCfg);
}

void Application::saveAudioConfig(const TAudioSubsystemConfigData& audioCfg)
{
	if (mAudioSubsystem.get())
	{
		mAudioSubsystem->setConfigData(audioCfg);
		mAudioSubsystem->saveCurrentConfigData();
	}
}

void Application::modifyVolume(const std::string& groupName, double volume)
{
		mAudioSubsystem->setChannelGroupVolume(groupName,volume);
}

void Application::modifyEnable(const std::string& groupName, bool isEnabled)
{
		mAudioSubsystem->pauseChannelGroup(groupName,!isEnabled);
}

int Application::getUniqueId()
{
	mUniqueId++;
	return mUniqueId;
}

std::string Application::getStringUniqueId(){
	return Ogre::StringConverter::toString(Ogre::Real(getUniqueId()));
}

std::vector<std::string>& Application::getSupportedLanguages()
{
	return mSupportedLanguages;
}
void Application::changeCurrentLanguage(const std::string& newLanguage)
{
	if (find(mSupportedLanguages.begin(),mSupportedLanguages.end(),newLanguage)!=mSupportedLanguages.end())
	{
		mLanguage=newLanguage;
		//TODO: mStateManager->getCurrentState()->languageChanged(newLanguage);
	}
}
const std::string& Application::getCurrentLanguage() const
{
	return mLanguage;
}