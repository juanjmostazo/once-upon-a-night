#include "OUAN_Precompiled.h"

#include "../OUAN.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"
#include "GameState.h"

using namespace OUAN;

GameState::GameState(){}
GameState::~GameState(){}

void GameState::changeState(GameStatePtr nextState)
{
	mApp->getGameStateManager()->changeState(nextState,mApp);
}

bool GameState::render()
{
	return mApp->getRenderSubsystem()->render();
}

bool GameState::keyPressed( const OIS::KeyEvent& e )
{
	return true;
}
bool GameState::keyReleased(const OIS::KeyEvent& e)
{
	return true;
}
bool GameState::mouseMoved(const OIS::MouseEvent &e)
{
	return true;
}
bool GameState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}
bool GameState::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}
bool GameState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}
bool GameState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}
ApplicationPtr GameState::getApp() const
{
	return mApp;
}