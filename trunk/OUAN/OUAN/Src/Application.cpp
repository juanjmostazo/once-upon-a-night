#include "Application.h"

#include "Graphics/RenderSubsystem.h"

#include "Core/GameStateManager.h"
#include "Core/GameState.h"
#include "Core/MainMenuState.h"
#include "Core/GameRunningState.h"

#include "GUI/GUISubsystem.h"

#include "Physics/PhysicsSubsystem.h"

#include "Game/GameWorldManager.h"

#include "Loader/Configuration.h"
#include "Loader/LevelLoader.h"

using namespace OUAN;


Application::Application(const std::string& windowName)
:mWindowName(windowName)
{
}

Application::~Application()
{
}
void Application::cleanUp()
{
	mGUISubsystem->cleanUp();
	mRenderSubsystem->cleanUp();
	FullInputManager::finalise();
}
//Application initialization
void Application::initialise()
{
	ApplicationPtr this_ = shared_from_this();

	mExitRequested=false;

	mStateManager.reset(new GameStateManager());

	mConfiguration.reset(new Configuration());
	//mConfiguration->loadFromFile("something")

	mRenderSubsystem.reset(new RenderSubsystem(mWindowName));
	mRenderSubsystem->initialise(this_,mConfiguration);

	mGUISubsystem.reset(new GUISubsystem());
	mGUISubsystem->initialise(this_);

	mGameWorldManager.reset( new GameWorldManager);
	mGameWorldManager->initialise(this_);

	mLevelLoader.reset(new LevelLoader);
	mLevelLoader->initialise(this_);

	//TODO: Add remaining subsystems (AI, Audio, etc)

	setupInputSystem();

	//TODO: Put this in proper location
	mRenderSubsystem->setupScene(mConfiguration);

	mPhysicsSubsystem.reset(new PhysicsSubsystem());
	mPhysicsSubsystem->initialise(this_,mConfiguration);

}
//Run the app
void Application::go()
{
	Ogre::Timer loopTimer;
	bool continueRunning = true;

	// TODO: Decide for one synchronization method and stick to it
	long nextGameTicks = loopTimer.getMillisecondsCPU();
	int loops;
	float interpolation;

	while ( continueRunning )
	{
		Ogre::WindowEventUtilities::messagePump();
		FullInputManager::capture();

		//Update logic stuff
		loops=0;
		long elapsedTime=0;
		long currentTime=loopTimer.getMillisecondsCPU();
		while(currentTime>nextGameTicks && loops<MAX_FRAMESKIP)
		{
			elapsedTime=currentTime-elapsedTime;
			mStateManager->getCurrentState()->update(elapsedTime);
			nextGameTicks+=SKIP_TICKS;
			loops++;
			currentTime=loopTimer.getMillisecondsCPU();
		}
		interpolation=float(loopTimer.getMillisecondsCPU()+SKIP_TICKS-nextGameTicks)/float(SKIP_TICKS);
		//Update graphics stuff
		//updateGraphics(interpolation);


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
	FullInputManager::initialise( mRenderSubsystem->getWindow(), false );
}
void Application::loadInitialState()
{
	GameStatePtr initialState(new GameRunningState());
	ApplicationPtr this_ = shared_from_this();
	mStateManager->changeState(initialState,this_);
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