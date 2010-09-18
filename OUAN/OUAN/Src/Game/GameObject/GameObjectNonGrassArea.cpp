#include "OUAN_Precompiled.h"

#include "GameObjectNonGrassArea.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectNonGrassArea::GameObjectNonGrassArea(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_NON_GRASS_AREA)
{

}

GameObjectNonGrassArea::~GameObjectNonGrassArea()
{

}

void GameObjectNonGrassArea::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectNonGrassArea::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectNonGrassArea::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectNonGrassArea::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectNonGrassArea::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectNonGrassArea::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectNonGrassArea::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
		}
		else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}		
		break;
	default:
		break;
	}
}

void GameObjectNonGrassArea::changeWorldStarted(int newWorld)
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

void GameObjectNonGrassArea::changeToWorld(int newWorld, double perc)
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

void GameObjectNonGrassArea::reset()
{
	GameObject::reset();
}

bool GameObjectNonGrassArea::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectNonGrassArea::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectNonGrassArea::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectNonGrassArea::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


/// Set logic component
void GameObjectNonGrassArea::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectNonGrassArea::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectNonGrassArea::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectNonGrassArea::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}

	Logger::getInstance()->log("ENTERING NONGRASS " + pGameObject->getName());
}

void GameObjectNonGrassArea::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}

	Logger::getInstance()->log("EXITING NONGRASS " + pGameObject->getName());
}

bool GameObjectNonGrassArea::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectNonGrassArea::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectNonGrassAreaParameters::TGameObjectNonGrassAreaParameters() : TGameObjectParameters()
{

}

TGameObjectNonGrassAreaParameters::~TGameObjectNonGrassAreaParameters()
{

}