#include "GameObjectDiamondTree.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;

GameObjectDiamondTree::GameObjectDiamondTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMONDTREE)
{

}

GameObjectDiamondTree::~GameObjectDiamondTree()
{

}

void GameObjectDiamondTree::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDiamondTree::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectDiamondTree::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDiamondTree::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDiamondTree::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDiamondTree::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDiamondTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDiamondTree::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDiamondTree::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr physicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=physicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectDiamondTree::getPhysicsComponentVolumeBox() const{
	return mPhysicsComponentVolumeBox;
}

void GameObjectDiamondTree::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
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
				mRenderComponentEntityDreams->changeAnimation(TREE_ANIM_IDLE_UP);
			}
			else
			{
				mRenderComponentEntityDreams->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
				mRenderComponentEntityDreams->changeAnimation(TREE_ANIM_IDLE_UP);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
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
				mRenderComponentEntityNightmares->changeAnimation(TREE_ANIM_IDLE_UP);
			}
			else
			{
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
				mRenderComponentEntityNightmares->changeAnimation(TREE_ANIM_IDLE_UP);
			}
			break;
		default:
			break;
	}
}

void GameObjectDiamondTree::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntityDreams->changeAnimation(TREE_ANIM_UP);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->changeAnimation(TREE_ANIM_DOWN);
		}
		break;
	default:
		break;
	}
}

void GameObjectDiamondTree::changeToWorld(int newWorld, double perc)
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

void GameObjectDiamondTree::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectDiamondTree::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectDiamondTree::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(DT_STATE_IDLE));

	if (mLogicComponent->existsInNightmares())
		mRenderComponentEntityNightmares->changeAnimation(DT_ANIM_IDLE);
	else if (mLogicComponent->existsInDreams())
		mRenderComponentEntityDreams->changeAnimation(DT_ANIM_IDLE);
}

bool GameObjectDiamondTree::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDiamondTree::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectDiamondTree::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectDiamondTree::getPhysicsComponent() const
{
	return mPhysicsComponentSimpleBox;
}

/// Set logic component
void GameObjectDiamondTree::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectDiamondTree::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectDiamondTree::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectDiamondTree::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectDiamondTree::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectDiamondTree::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectDiamondTree::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDiamondTree::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}

TGameObjectDiamondContainer* GameObjectDiamondTree::getDiamonds()
{
	return &mDiamonds;
}
void GameObjectDiamondTree::setDiamonds(const TGameObjectDiamondContainer& diamonds)
{
	mDiamonds=diamonds;
}
void GameObjectDiamondTree::addDiamond(GameObjectDiamondPtr diamond)
{
	mDiamonds.push_back(diamond);
}
void GameObjectDiamondTree::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(DT_ANIM_HIT)==0)
	{
		mLogicComponent->setHasTakenHit(false);
		mLogicComponent->setReload(true);
	}
}
void GameObjectDiamondTree::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{	
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
			?mRenderComponentEntityDreams
			:mRenderComponentEntityNightmares;

		int currentState=mLogicComponent->getState();
		
		if (currentState==logicSS->getGlobalInt(DT_STATE_IDLE))
		{
			if (entityToUpdate.get() && mLogicComponent->isStateChanged())
			{
				displayText("Now loaded");
				mLogicComponent->setHasTakenHit(false);
				mLogicComponent->setReload(false);
				entityToUpdate->changeAnimation(DT_ANIM_IDLE);					
			}
		}
		else if (currentState==logicSS->getGlobalInt(DT_STATE_HIT) && entityToUpdate.get() && mLogicComponent->isStateChanged())
		{				
			entityToUpdate->changeAnimation(DT_STATE_HIT);			
			//play sound
			//enable children diamonds!
		}
		else if (currentState==logicSS->getGlobalInt(DT_STATE_RELOAD) && entityToUpdate.get() && mLogicComponent->isStateChanged())
		{				
			//play some particles to show the reloading state
			std::stringstream msg;
			msg<<"Reload started: "<<std::setprecision(2)<<mLogicComponent->getTimeSpent()<<")";
			displayText(msg.str());
			entityToUpdate->changeAnimation(DT_STATE_IDLE);
			mLogicComponent->setTimeSpent(0);
		}
		if (entityToUpdate.get())
		{
			entityToUpdate->update(elapsedSeconds);
		}

		//if (mPhysicsComponent.get() && mPhysicsComponent->isInUse())
		//{
		//	mPhysicsComponent->setNextMovement(NxOgre::Vec3::ZERO);
		//}
	}
}

void GameObjectDiamondTree::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
	mPhysicsComponentVolumeBox->update(elapsedSeconds);
}
//-------------------------------------------------------------------------------------------

TGameObjectDiamondTreeParameters::TGameObjectDiamondTreeParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondTreeParameters::~TGameObjectDiamondTreeParameters()
{

}