#include "OUAN_Precompiled.h"

#include "GameObjectBreakableRock.h"
#include "GameObjectInvisibleWall.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectBreakableRock::GameObjectBreakableRock(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BREAKABLE_ROCK)
{

}

GameObjectBreakableRock::~GameObjectBreakableRock()
{

}

void GameObjectBreakableRock::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectBreakableRock::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectBreakableRock::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectBreakableRock::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectBreakableRock::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBreakableRock::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBreakableRock::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBreakableRock::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBreakableRock::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectBreakableRock::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectBreakableRock::breakRock()
{
	if(!mBroken)
	{
		if(getName().compare("breakable-rock#rock_big")==0)
		{
			getGameWorldManager()->addExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK);

			GameObjectPtr obj=getGameWorldManager()->getObject("invisible-wall#BOMBS_PUZZLE");

			GameObjectInvisibleWallPtr wall= 
				BOOST_PTR_CAST(GameObjectInvisibleWall,obj);

			wall->desactivateWall();
			
		}
		mBroken=true;
		mRenderComponentEntityDreams->setVisible(false);
		mRenderComponentEntityNightmares->setVisible(false);
		if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}
	}
}

void GameObjectBreakableRock::changeWorldFinished(int newWorld)
{
	if (!isEnabled() || mBroken) return;

	switch(newWorld)
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
		default:
			break;
	}
}

void GameObjectBreakableRock::setVisible(bool visible)
{
	if(!mBroken)
	{
		switch(mWorld)
		{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(visible);
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(visible);
			}
			break;
		default:
			break;
		}
	}
}

void GameObjectBreakableRock::changeWorldStarted(int newWorld)
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

void GameObjectBreakableRock::changeToWorld(int newWorld, double perc)
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

void GameObjectBreakableRock::reset()
{
	GameObject::reset();
	if(getName().compare("breakable-rock#rock_big")==0 && !getGameWorldManager()->hasExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK))
	{
		mBroken=false;
	}
}

bool GameObjectBreakableRock::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBreakableRock::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectBreakableRock::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectBreakableRock::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}


/// Set logic component
void GameObjectBreakableRock::setLogicComponentProp(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectBreakableRock::getLogicComponentProp()
{
	return mLogicComponent;
}

void GameObjectBreakableRock::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectBreakableRock::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectBreakableRock::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectBreakableRock::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectBreakableRock::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
bool GameObjectBreakableRock::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectBreakableRock::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectBreakableRockParameters::TGameObjectBreakableRockParameters() : TGameObjectParameters()
{

}

TGameObjectBreakableRockParameters::~TGameObjectBreakableRockParameters()
{

}