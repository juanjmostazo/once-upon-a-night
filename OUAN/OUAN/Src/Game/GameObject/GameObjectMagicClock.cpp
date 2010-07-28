#include "OUAN_Precompiled.h"

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

void GameObjectMagicClock::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
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


void GameObjectMagicClock::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectMagicClock::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectMagicClock::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}
bool GameObjectMagicClock::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectMagicClock::getLogicComponentInstance() const
{
	return mLogicComponent;
}
TGameObjectMagicClockParameters::TGameObjectMagicClockParameters() : TGameObjectParameters()
{

}

TGameObjectMagicClockParameters::~TGameObjectMagicClockParameters()
{

}