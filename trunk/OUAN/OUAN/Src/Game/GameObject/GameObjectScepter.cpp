#include "GameObjectScepter.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectScepter::GameObjectScepter(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SCEPTER)
{

}

GameObjectScepter::~GameObjectScepter()
{

}

RenderComponentEntityPtr GameObjectScepter::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectScepter::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectScepter::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectScepter::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectScepter::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectScepter::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectScepter::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectScepter::getPhysicsComponentSimpleCapsule() const
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectScepter::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}
			break;
		default:
			break;
	}
}

void GameObjectScepter::changeWorldStarted(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScepter::changeToWorld(int world, double perc)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScepter::reset()
{
	GameObject::reset();
}

bool GameObjectScepter::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectScepter::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectScepter::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectScepter::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleCapsule();
}

/// Set logic component
void GameObjectScepter::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectScepter::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectScepter::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectScepter::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectScepter::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectScepter::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectScepter::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectScepter::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectScepterParameters::TGameObjectScepterParameters() : TGameObjectParameters()
{

}

TGameObjectScepterParameters::~TGameObjectScepterParameters()
{

}