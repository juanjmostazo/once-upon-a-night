#include "OUAN_Precompiled.h"

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

void GameObjectWoodBox::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentBreakable->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponentBreakable->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectWoodBox::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentBreakable->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponentBreakable->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectWoodBox::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponentBreakable->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponentBreakable->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectWoodBox::setChangeWorldRender()
{
	if (!isEnabled()) return;
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
				mRenderComponentEntityNightmares->setVisible(false);
			}
			else if(!mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponentBreakable->existsInDreams() && !mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		case NIGHTMARES:
			if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
				mRenderComponentEntityDreams->setVisible(false);
			}
			else if(!mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponentBreakable->existsInDreams() && !mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		default:break;
	}
}

void GameObjectWoodBox::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			break;
		case NIGHTMARES:
			setNightmaresRender();
			break;
		default:break;
	}

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
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
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
			{
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}
			else if(mLogicComponentBreakable->existsInDreams()&& !mLogicComponentBreakable->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
			}
			else if(!mLogicComponentBreakable->existsInDreams()&& mLogicComponentBreakable->existsInNightmares())
			{
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectWoodBox::changeWorldStarted(int newWorld)
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

void GameObjectWoodBox::changeToWorld(int newWorld, double perc)
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

void GameObjectWoodBox::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectWoodBox::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentBreakable->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentBreakable->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentBreakable->existsInDreams() && mLogicComponentBreakable->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentBreakable->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentBreakable->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectWoodBox::reset()
{
	GameObject::reset();
	mLogicComponentBreakable->setState(STATE_BREAKABLE_NOT_BROKEN);

	if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentSimpleBox->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());	
	}

	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
	{
		mPhysicsComponentVolumeBox->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentVolumeBox->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());	
	}
	if (mRenderComponentEntityAdditional.get())
		mRenderComponentEntityAdditional->setVisible(false);

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
	return mPhysicsComponentSimpleBox;
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

void GameObjectWoodBox::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentBreakable.get())
	{
		mLogicComponentBreakable->processCollision(pGameObject, pNormal);
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

void GameObjectWoodBox::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (mPhysicsComponentVolumeBox->isInUse() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentVolumeBox->setPosition(mPhysicsComponentSimpleBox->getNxOgrePosition());
	}
	RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
		?mRenderComponentEntityDreams
		:mRenderComponentEntityNightmares;
	
	if (entityToUpdate.get())
	{
		entityToUpdate->update(elapsedSeconds);
	}
}

//TODO DO IT PROPERLY WHEN THERE ARE TWO RENDER COMPONENT ENTITIES
void GameObjectWoodBox::updateLogic(double elapsedSeconds)
{
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
			if (mLogicComponentBreakable->getIsBroken() && mLogicComponentBreakable->isStateChanged())
			{
				mRenderComponentEntityAdditional->setVisible(true);
				mRenderComponentEntityAdditional->changeAnimation("broken");
			}


			if (mLogicComponentBreakable->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(false);			
				mRenderComponentEntityNightmares->setVisible(false);
			}
			
			if (mLogicComponentBreakable->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
				mRenderComponentEntityDreams->setVisible(false);
			}		
		}
	}	
	GameObject::updateLogic(elapsedSeconds);
}

bool GameObjectWoodBox::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectWoodBox::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}

void GameObjectWoodBox::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
	mPhysicsComponentVolumeBox->update(elapsedSeconds);
}
RenderComponentEntityPtr GameObjectWoodBox::getRenderComponentEntityAdditional() const
{
	return mRenderComponentEntityAdditional;
}
void GameObjectWoodBox::setRenderComponentEntityAdditional(RenderComponentEntityPtr pRenderComponentEntityAdditional)
{
	mRenderComponentEntityAdditional=pRenderComponentEntityAdditional;
}

void GameObjectWoodBox::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponentBreakable->existsInDreams())
		{
			mRenderComponentEntityDreams->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentBreakable->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
bool GameObjectWoodBox::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectWoodBox::getLogicComponentInstance() const
{
	return mLogicComponentBreakable;
}
//-------------------------------------------------------------------------------------------

TGameObjectWoodBoxParameters::TGameObjectWoodBoxParameters() : TGameObjectParameters()
{

}

TGameObjectWoodBoxParameters::~TGameObjectWoodBoxParameters()
{

}