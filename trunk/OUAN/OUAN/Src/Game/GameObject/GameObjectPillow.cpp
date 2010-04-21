#include "GameObjectPillow.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPillow::GameObjectPillow(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PILLOW)
{

}

GameObjectPillow::~GameObjectPillow()
{

}
/// Set logic component
void GameObjectPillow::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectPillow::getLogicComponent()
{
	return mLogicComponent;
}
RenderComponentEntityPtr GameObjectPillow::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPillow::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPillow::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPillow::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPillow::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectPillow::getPhysicsComponentSimpleCapsule() const
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectPillow::changeWorld(int world)
{
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
		{
			mPhysicsComponentSimpleCapsule->create();
		}

		mRenderComponentEntity->setVisible(true);
		return;
	}
	else
	{
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
}

void GameObjectPillow::reset()
{
	GameObject::reset();
}

bool GameObjectPillow::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectPillow::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectPillow::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectPillow::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleCapsule();
}

void GameObjectPillow::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectPillow::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPillow::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectPillow::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectPillowParameters::TGameObjectPillowParameters() : TGameObjectParameters()
{

}

TGameObjectPillowParameters::~TGameObjectPillowParameters()
{

}