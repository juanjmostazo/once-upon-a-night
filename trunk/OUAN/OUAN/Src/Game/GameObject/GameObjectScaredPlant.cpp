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

void GameObjectScaredPlant::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectScaredPlant::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectScaredPlant::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		getPhysicsComponentCharacter()->getNxOgreController()->move(
			Application::getInstance()->getPhysicsSubsystem()->mGravity * 
			Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
			GROUP_COLLIDABLE_MASK,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);
	}
}

void GameObjectScaredPlant::reset()
{
	GameObject::reset();
	
	changeWorld(DREAMS);

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
	}
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
	}
}

void GameObjectScaredPlant::changeWorld(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
		case DREAMS:
			if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
			{
				//mPhysicsComponentCharacter->create();
			}
			mRenderComponentEntityDreams->setVisible(true);
			break;
		case NIGHTMARES:
			if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
			{
				//mPhysicsComponentCharacter->destroy();
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
	return getPhysicsComponentCharacter();
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

//-------------------------------------------------------------------------------------------

TGameObjectScaredPlantParameters::TGameObjectScaredPlantParameters() : TGameObjectParameters()
{

}

TGameObjectScaredPlantParameters::~TGameObjectScaredPlantParameters()
{

}