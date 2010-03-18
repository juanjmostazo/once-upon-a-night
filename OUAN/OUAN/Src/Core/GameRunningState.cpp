#include "GameRunningState.h"

#include "GameStateManager.h"
#include "GameOverState.h"
#include "GamePausedState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIConsole.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectOny.h"

#include <fstream>

using namespace OUAN;

/// Default constructor
GameRunningState::GameRunningState()
:GameState()
{

}

/// Destructor
GameRunningState::~GameRunningState()
{

}

/// init game running state's resources
void GameRunningState::init(ApplicationPtr app)
{
	mApp=app;	

	mApp->getGameWorldManager()->setWorld(DREAMS);
	mApp->getGameWorldManager()->loadLevel(LEVEL_2);

	//mApp->getRenderSubsystem()->getCameraManager()->setCameraType(CAMERA_TRAJECTORY);

	mApp->mKeyBuffer=-1;
	
	initRouletteData();
	mCurrentRouletteState=ROULETTE_COLOUR_RED;
	updateRouletteHUD();

	mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
	mGUI->initGUI(shared_from_this());
	mGUI->hideConsole();	
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_INGAME_HUD);
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
	mApp->getGameWorldManager()->unloadLevel();
	mApp->getGUISubsystem()->cleanUp();
	//mApp->getPhysicsSubsystem()->clear(); Done into mApp->getGameWorldManager()->unloadLevel();
	//mApp->getRenderSubsystem()->clear(); Done into mApp->getGameWorldManager()->unloadLevel();
	mApp->getGUISubsystem()->init(mApp);
	mApp->mKeyBuffer=-1;
	mRouletteData.clear();
}

/// pause state
void GameRunningState::pause()
{
	//the following method is called to stop 
	//particle systems and other automatically animated
	//elements
	mApp->getRenderSubsystem()->pauseRendering();
}
/// resume state
void GameRunningState::resume()
{
	mApp->getRenderSubsystem()->resumeRendering();
}

void GameRunningState::handleEvents()
{
	if (mApp->isPressedQuickExit() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedQuickExit IN");
		mApp->mExitRequested=true;
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER; //0.5s
	}
	else if (mApp->isPressedPause() && mApp->mKeyBuffer<0)
	{
		GameStatePtr nextState(new GamePausedState());
		// Notice how pushState is called instead of changeState.
		// The reason to use push this time is to prevent unnecessary cleanup and initialisation, since
		// after the pause the application flow will come back to "GameRunning"
		mApp->getGameStateManager()->pushState(nextState,mApp);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER; //0.5s
	}
	//TODO: REMOVE THIS STATEMENT when we can respond to a collision 
	//and simulate a gameOver event
	else if(mApp->isPressedAutoPoint() && mApp->mKeyBuffer<0)
	{
		mApp->getGameWorldManager()->setGameOver(true);
		mApp->getGameWorldManager()->setGameBeaten(true);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		mGUI->hideConsole();
	}
	else if (mApp->isPressedToggleDebugPerformance() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPerformance IN");
		if (mApp->getDebugMode()!=DEBUGMODE_PERFORMANCE)
		{
			mApp->setDebugMode(DEBUGMODE_PERFORMANCE);
			mApp->getRenderSubsystem()->hideVisualDebugger();
			mApp->getRenderSubsystem()->showOverlay(OVERLAY_DEBUG_PANEL);
		}
		else
		{
			mApp->setDebugMode(DEBUGMODE_NONE);
			mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
		}
		
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleDebugPhysics() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPhysics IN");
		if (mApp->getDebugMode()!=DEBUGMODE_PHYSICS)
		{
			mApp->setDebugMode(DEBUGMODE_PHYSICS);
			mApp->getRenderSubsystem()->showOverlay(OVERLAY_DEBUG_PANEL);
			mApp->getRenderSubsystem()->showVisualDebugger();
		}
		else 
		{
			mApp->setDebugMode(DEBUGMODE_NONE);
			mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
			mApp->getRenderSubsystem()->hideVisualDebugger();
		}

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeCamera() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->changeCamera();

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeCameraController() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->changeCameraController();

		if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIXED_FIRST_PERSON)
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityDreams()->setVisible(false);
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityNightmares()->setVisible(false);
		}
		else
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityDreams()->setVisible(true);
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityNightmares()->setVisible(true);

		}
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeWorld() && mApp->mKeyBuffer<0)
	{
		mApp->getGameWorldManager()->changeWorld();

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeLevel() && mApp->mKeyBuffer<0)
	{
		Ogre::LogManager::getSingleton().logMessage("isPressedToggleChangeLevel IN");
		if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_TEST)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_CLOCK);
		}
		else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_2)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_1);
		}
		else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_1)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_2);
		}
		else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_2)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_TEST);
		}
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}

	else if (mApp->isPressedRotateLeft() && mApp->mKeyBuffer<0)
	{
		spinRoulette(true);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedRotateRight() && mApp->mKeyBuffer<0)
	{
		spinRoulette(false);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}

	else if (mApp->isPressedToggleConsole() && mApp->mKeyBuffer<0)
	{
		if (mGUI->isVisible())
			mGUI->hideConsole();
		else
			mGUI->showConsole();
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}

		
	///////////////////////////////////////////////////////////
	// ONY (or first person camera): TYPE OF MOVEMENT
	int movementFlags = 0;
	if (mApp->isPressedGoForward())
	{
		movementFlags |= MOV_GO_FORWARD;	
	}

	if (mApp->isPressedGoBack())
	{
		movementFlags |= MOV_GO_BACK;
	}

	if (mApp->isPressedGoLeft())
	{
		movementFlags |= MOV_GO_LEFT;
	}

	if (mApp->isPressedGoRight())
	{
		movementFlags |= MOV_GO_RIGHT;
	}

	if (mApp->isPressedJump())
	{
		movementFlags |= MOV_JUMP;
	}

	if (mApp->isPressedWalk())
	{
		movementFlags |= MOV_WALK;
	}

	if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIRST_PERSON)
	{
		mApp->getRenderSubsystem()->getCameraManager()->processSimpleTranslation(movementFlags);
	}
	else if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()!=CAMERA_FIXED_FIRST_PERSON)
	{
		//Access to [0] because there's only one Ony, otherwise it should be a loop
		mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->setMovementFlags(movementFlags);
	}

	//[TODO: This will also have to be refactored somehow as soon as
	// a camera manager system has been implemented. 
	// The render subsystem shouldn't move cameras at this point: it will
	// all be managed internally from the body of a hypothetic CameraComponent
	// 
	// The main idea would be something like:
	// - Poll mouse/joystick right axis using the mApp methods inherited
	//   from ControlInputManager and retrieve the relative increments
	// - Then ask the gameWorldManager to update the current active camera accordingly,
	//	 or switch to the user-controlled camera mode and then update that one, whatever.
	//   The current active camera would be a GameObject using a CameraComponent.
	//]
	double xRel,yRel,zRel;	
	mApp->getMouseStateRelValues(&xRel,&yRel,&zRel);
	mApp->getRenderSubsystem()->moveCamera(xRel,yRel,zRel);
}

void GameRunningState::update(long elapsedTime)
{
	double elapsedSeconds=(double)elapsedTime * 0.000001f;

	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTimeDebug = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);

	//Ogre::LogManager::getSingleton().logMessage("Updating Game World Manager");
	mApp->getGameWorldManager()->update(elapsedSeconds);	

	//Ogre::LogManager::getSingleton().logMessage("Updating Physics Subsystem");
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);

	//Ogre::LogManager::getSingleton().logMessage("Updating Camera Params");
	mApp->getRenderSubsystem()->updateCameraParams(elapsedSeconds);
	
	//Ogre::LogManager::getSingleton().logMessage("Other stuff");
	mApp->mKeyBuffer-=elapsedTime;

	if (mApp.get() && mApp->getGameWorldManager().get() && mApp->getGameWorldManager()->isGameOver())
	{
		mApp->getRenderSubsystem()->captureScene(SAVED_RTT_FILENAME);
		GameStatePtr nextState(new GameOverState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}
	updateRoulette();
	mGUI->update(elapsedSeconds);
}

bool GameRunningState::render()
{
	RenderSubsystemPtr renderSubsystem=mApp->getRenderSubsystem();
	
	if (mApp->getDebugMode()!=DEBUGMODE_NONE)
	{
		renderSubsystem->updateStats();
		renderSubsystem->updateDebugInfo();
		renderSubsystem->showOverlay(OVERLAY_DEBUG_PANEL);
	}

	renderSubsystem->updateVisualDebugger();
	renderSubsystem->showOverlay(OVERLAY_INGAME_HUD);
	
	return renderSubsystem->render();
}

void GameRunningState::spinRoulette(bool forward)
{
	int increment=forward?1:-1;
	bool isColourRouletteState=mCurrentRouletteState==ROULETTE_COLOUR_BLUE || 
		mCurrentRouletteState==ROULETTE_COLOUR_RED || mCurrentRouletteState == ROULETTE_COLOUR_GREEN;
	if (isColourRouletteState)
	{	
		int next=(mCurrentRouletteState+increment)%NUM_ROULETTE_STATES;
		if (next<0) next+=NUM_ROULETTE_STATES;
		mCurrentRouletteState=static_cast<TRouletteState>(next);
		updateRouletteHUD();
	}	
}
void GameRunningState::updateRoulette()
{
	bool isLeftTransition = mCurrentRouletteState== ROULETTE_TRANSITION_REDGREEN ||
		mCurrentRouletteState == ROULETTE_TRANSITION_GREENBLUE || mCurrentRouletteState==ROULETTE_TRANSITION_BLUERED;
	bool isRightTransition = mCurrentRouletteState==ROULETTE_TRANSITION_REDBLUE ||
		mCurrentRouletteState == ROULETTE_TRANSITION_BLUEGREEN || mCurrentRouletteState==ROULETTE_TRANSITION_GREENRED;
	int increment=0;
	if (isLeftTransition)
		increment=-2;
	else if (isRightTransition)
		increment=2;
	//---
	if ((isLeftTransition || isRightTransition) && isRouletteAnimationFinished())
	{
		int next=(mCurrentRouletteState+increment)%NUM_ROULETTE_STATES;
		if (next<0) next+=NUM_ROULETTE_STATES;
		mCurrentRouletteState=static_cast<TRouletteState>(next);

		updateRouletteHUD();
	}
}
void GameRunningState::updateRouletteHUD()
{
	mApp->getRenderSubsystem()->setTextureData(MATERIAL_ROULETTE,mRouletteData[mCurrentRouletteState].textureName,
		mRouletteData[mCurrentRouletteState].isAnimated, mRouletteData[mCurrentRouletteState].numFrames,
		mRouletteData[mCurrentRouletteState].duration);
}
void GameRunningState::initRouletteData()
{
	mRouletteData.clear();
	mRouletteData[ROULETTE_COLOUR_RED].textureName=TEX_ROULETTE_COLOUR_RED;
	mRouletteData[ROULETTE_COLOUR_RED].isAnimated=false;
	mRouletteData[ROULETTE_COLOUR_BLUE].textureName=TEX_ROULETTE_COLOUR_BLUE;
	mRouletteData[ROULETTE_COLOUR_BLUE].isAnimated=false;
	mRouletteData[ROULETTE_COLOUR_GREEN].textureName=TEX_ROULETTE_COLOUR_GREEN;
	mRouletteData[ROULETTE_COLOUR_GREEN].isAnimated=false;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].textureName=TEX_ROULETTE_TRANSITION_BG;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].textureName=TEX_ROULETTE_TRANSITION_GB;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].textureName=TEX_ROULETTE_TRANSITION_RB;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].textureName=TEX_ROULETTE_TRANSITION_BR;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].textureName=TEX_ROULETTE_TRANSITION_RG;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].textureName=TEX_ROULETTE_TRANSITION_GR;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].duration=TRANSITION_DURATION;
}
bool GameRunningState::isRouletteAnimationFinished()
{
	if (mRouletteData[mCurrentRouletteState].isAnimated)
	{
		return mApp->getRenderSubsystem()->isAnimatedTextureFinished(MATERIAL_ROULETTE);
	}
	return false;
}
