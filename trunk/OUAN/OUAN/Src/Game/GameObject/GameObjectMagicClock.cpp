#include "GameObjectMagicClock.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectMagicClock::GameObjectMagicClock(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_MAGICCLOCK)
{

}

GameObjectMagicClock::~GameObjectMagicClock()
{

}

/// Set logic component
void GameObjectMagicClock::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectMagicClock::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectMagicClock::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectMagicClock::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectMagicClock::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectMagicClock::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectMagicClockParameters::TGameObjectMagicClockParameters() : TGameObjectParameters()
{

}

TGameObjectMagicClockParameters::~TGameObjectMagicClockParameters()
{

}