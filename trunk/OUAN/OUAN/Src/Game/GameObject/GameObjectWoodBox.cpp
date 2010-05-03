#include "GameObjectWoodBox.h"
#include "../GameWorldManager.h"

#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;

GameObjectWoodBox::GameObjectWoodBox(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_WOODBOX)
{

}

GameObjectWoodBox::~GameObjectWoodBox()
{

}

RenderComponentEntityPtr GameObjectWoodBox::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectWoodBox::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectWoodBox::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectWoodBox::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

void GameObjectWoodBox::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectWoodBox::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectWoodBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectWoodBox::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectWoodBox::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectWoodBox::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectWoodBox::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
		}	
		break;
	default:break;
	}
}

void GameObjectWoodBox::reset()
{
	GameObject::reset();
}

bool GameObjectWoodBox::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectWoodBox::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectWoodBox::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectWoodBox::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}

/// Set logic component
void GameObjectWoodBox::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectWoodBox::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectWoodBox::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectWoodBox::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectWoodBox::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectWoodBox::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

bool GameObjectWoodBox::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectWoodBox::getEntityComponent() const
{
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectWoodBoxParameters::TGameObjectWoodBoxParameters() : TGameObjectParameters()
{

}

TGameObjectWoodBoxParameters::~TGameObjectWoodBoxParameters()
{

}