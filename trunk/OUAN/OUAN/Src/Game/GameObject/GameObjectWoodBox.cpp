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

void GameObjectWoodBox::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectWoodBox::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectWoodBox::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(mLogicComponentBreakable->existsInDreams()&& !mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(!mLogicComponentBreakable->existsInDreams()&& mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else if(mLogicComponentBreakable->existsInDreams()&& !mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
		}
		else if(!mLogicComponentBreakable->existsInDreams()&& mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}	
		break;
	default:break;
	}
}

void GameObjectWoodBox::changeWorldStarted(int world)
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

void GameObjectWoodBox::changeToWorld(int world, double perc)
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

void GameObjectWoodBox::reset()
{
	GameObject::reset();
	mLogicComponentBreakable->setState(STATE_BREAKABLE_NOT_BROKEN);
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
void GameObjectWoodBox::setLogicComponentBreakable(LogicComponentBreakablePtr logicComponentBreakable)
{
	mLogicComponentBreakable=logicComponentBreakable;
}

/// return logic component
LogicComponentBreakablePtr GameObjectWoodBox::getLogicComponentBreakable()
{
	return mLogicComponentBreakable;
}

void GameObjectWoodBox::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentBreakable.get())
	{
		mLogicComponentBreakable->processCollision(pGameObject);
	}
}

void GameObjectWoodBox::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentBreakable.get())
	{
		mLogicComponentBreakable->processEnterTrigger(pGameObject);
	}
}

void GameObjectWoodBox::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentBreakable.get())
	{
		mLogicComponentBreakable->processExitTrigger(pGameObject);
	}
}

void GameObjectWoodBox::updateLogic(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (mLogicComponentBreakable->isStateChanged())
	{
		if (mLogicComponentBreakable->getState()==STATE_BREAKABLE_BROKEN)
		{	
			if (mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
			
			if (mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}

			if (mLogicComponentBreakable->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(false);
			}
			
			if (mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
			}		
		}
	}

	mLogicComponentBreakable->update(elapsedSeconds);
}

bool GameObjectWoodBox::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectWoodBox::getEntityComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectWoodBoxParameters::TGameObjectWoodBoxParameters() : TGameObjectParameters()
{

}

TGameObjectWoodBoxParameters::~TGameObjectWoodBoxParameters()
{

}