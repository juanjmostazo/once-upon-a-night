#include "OUAN_Precompiled.h"

#include "GameObjectBridge.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectBridge::GameObjectBridge(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BRIDGE)
{

}

GameObjectBridge::~GameObjectBridge()
{

}

void GameObjectBridge::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectBridge::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}


void GameObjectBridge::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBridge::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBridge::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBridge::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBridge::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectBridge::getPhysicsComponentComplexConvex() const
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectBridge::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			mRenderComponentEntity->changeAnimation(BRIDGE_ANIM_ROLL_IDLE);
			break;
		case NIGHTMARES:
			mRenderComponentEntity->changeAnimation(BRIDGE_ANIM_IDLE);
			break;
		default:break;
	}
}

void GameObjectBridge::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;


	switch(newWorld)
	{
	case DREAMS:
		mRenderComponentEntity->changeAnimation(BRIDGE_ANIM_ROLL);
		break;
	case NIGHTMARES:
		mRenderComponentEntity->changeAnimation(BRIDGE_ANIM_UNROLL);
		break;
	default:
		break;
	}
}

void GameObjectBridge::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) 
	{
		return;
	}

	std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
	float currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();
	if(!mRenderComponentEntity->getCurrentAnimation()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mWorld==DREAMS)
		{
			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
		}
		else if(mWorld==NIGHTMARES)
		{
			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
		}
		break;
	case NIGHTMARES:
		if(mWorld==DREAMS)
		{
			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
		}
		else if(mWorld==NIGHTMARES)
		{
			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
		}
		break;
	default:
		break;
	}
}

void GameObjectBridge::reset()
{
	GameObject::reset();

}

bool GameObjectBridge::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBridge::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectBridge::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectBridge::getPhysicsComponent() const
{
	return getPhysicsComponentComplexConvex();
}

/// Set logic component
void GameObjectBridge::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectBridge::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectBridge::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectBridge::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectBridge::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectBridge::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectBridge::getEntityComponent() const
{
	return mRenderComponentEntity;
}
void GameObjectBridge::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	default:
		break;
	}
}

void GameObjectBridge::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

bool GameObjectBridge::isWorthUpdatingPhysicsComponents()
{
	return true;
}

bool GameObjectBridge::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectBridge::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------
TGameObjectBridgeParameters::TGameObjectBridgeParameters() : TGameObjectParameters()
{

}

TGameObjectBridgeParameters::~TGameObjectBridgeParameters()
{

}
