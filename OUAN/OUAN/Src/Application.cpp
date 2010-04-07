#include "Application.h"

#include "Graphics/RenderSubsystem.h"
#include "Graphics/CameraManager/CameraManager.h"
#include "Graphics/TrajectoryManager/TrajectoryManager.h"

#include "Core/GameStateManager.h"
#include "Core/GameState.h"
#include "Core/MainMenuState.h"
#include "Core/GameRunningState.h"

#include "GUI/GUISubsystem.h"

#include "Physics/PhysicsSubsystem.h"

#include "RayCasting/RayCasting.h"

#include "Logic/LogicSubsystem.h"

#include "Game/GameWorldManager.h"
#include "Component/ComponentFactory.h"

#include "Loader/Configuration.h"
#include "Loader/LevelLoader.h"

#include "Audio/AudioSubsystem.h"

#include "Game/GameObject/GameObjectTripollo.h"
#include "Graphics/RenderComponent/RenderComponentPositional.h"

using namespace OUAN;

Application::Application(const std::string& windowName) : mWindowName(windowName)
,mDebugMode(DEBUGMODE_NONE)
,mKeyBuffer(-1)
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
	mPhysicsSubsystem->cleanUp();
	mGUISubsystem->cleanUp();
	mRenderSubsystem->cleanUp();
	mLogicSubsystem->cleanUp();
	mAudioSubsystem->cleanUp();
	ControlInputManager::finalise();
}
//Application initialization
void Application::init()
{	
	ApplicationPtr this_ = shared_from_this();

	mExitRequested=false;

	ComponentFactory::getInstance()->init(this_);

	mStateManager.reset(new GameStateManager());

	mConfiguration.reset(new Configuration());
	//mConfiguration->loadFromFile("something")

	mRenderSubsystem.reset(new RenderSubsystem(mWindowName));
	mRenderSubsystem->init(this_, mConfiguration);

	mPhysicsSubsystem.reset(new PhysicsSubsystem());
	mPhysicsSubsystem->init(this_, mConfiguration);
	
	mRayCasting.reset(new RayCasting());
	mRayCasting->init(mRenderSubsystem,mPhysicsSubsystem);

	mTrajectoryManager.reset(new TrajectoryManager());
	mTrajectoryManager->init(mRenderSubsystem);

	mCameraManager.reset(new CameraManager());
	mCameraManager->init(mRenderSubsystem,mTrajectoryManager,mPhysicsSubsystem,mRayCasting);

	mGUISubsystem.reset(new GUISubsystem());
	mGUISubsystem->init(this_);

	mGameWorldManager.reset(new GameWorldManager());
	mGameWorldManager->init(this_);

	mLogicSubsystem.reset(new LogicSubsystem());
	mLogicSubsystem->init(this_);

	mLevelLoader.reset(new LevelLoader());
	mLevelLoader->init(this_);

	ConfigurationPtr audioCfg(new Configuration());
	audioCfg->loadFromFile(SOUND_CONFIG_FILE);
	TAudioSubsystemConfigData audioDesc;
	audioDesc.set(audioCfg);
	mAudioSubsystem.reset(new AudioSubsystem());
	mAudioSubsystem->init(audioDesc,this_);

	//TODO: Add remaining subsystems ()


	setupInputSystem();
}
//Run the app
void Application::go()
{
	Ogre::Timer loopTimer;
	bool continueRunning = true;

	long nextGameTicks = loopTimer.getMicroseconds();
	long lastTick=nextGameTicks;
	long currentTime;
	int loops;

	while ( continueRunning )
	{
		loops=0;
		while((currentTime=loopTimer.getMicroseconds())>nextGameTicks && loops<MAX_FRAMESKIP)
		{
			Ogre::WindowEventUtilities::messagePump();
			ControlInputManager::capture();

			mGUISubsystem->injectTimePulse((currentTime-lastTick)*0.000001);
			mStateManager->getCurrentState()->handleEvents();
			mStateManager->getCurrentState()->update(currentTime-lastTick);

			nextGameTicks+=SKIP_TICKS;
			loops++;
			lastTick=currentTime;
		}

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
	GameStatePtr initialState(new MainMenuState());
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