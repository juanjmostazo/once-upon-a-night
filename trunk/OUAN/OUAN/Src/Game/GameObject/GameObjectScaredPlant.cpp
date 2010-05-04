#include "GameObjectScaredPlant.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectScaredPlant::GameObjectScaredPlant(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SCAREDPLANT)
{

}

GameObjectScaredPlant::~GameObjectScaredPlant()
{

}

RenderComponentEntityPtr GameObjectScaredPlant::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectScaredPlant::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

void GameObjectScaredPlant::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectScaredPlant::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectScaredPlant::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectScaredPlant::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectScaredPlant::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectScaredPlant::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectScaredPlant::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectScaredPlant::reset()
{
	GameObject::reset();
	
	changeWorld(DREAMS);
}

void GameObjectScaredPlant::changeWorld(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
		case DREAMS:
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			mRenderComponentEntityDreams->setVisible(true);
			break;
		case NIGHTMARES:
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
			mRenderComponentEntityDreams->setVisible(false);
			break;
		default:break;
	}

}

bool GameObjectScaredPlant::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectScaredPlant::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectScaredPlant::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectScaredPlant::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}

/// Set logic component
void GameObjectScaredPlant::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectScaredPlant::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectScaredPlant::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectScaredPlant::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectScaredPlant::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectScaredPlant::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectScaredPlant::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectScaredPlant::getEntityComponent() const
{
	return  mRenderComponentEntityDreams;
}
//-------------------------------------------------------------------------------------------

TGameObjectScaredPlantParameters::TGameObjectScaredPlantParameters() : TGameObjectParameters()
{

}

TGameObjectScaredPlantParameters::~TGameObjectScaredPlantParameters()
{

}