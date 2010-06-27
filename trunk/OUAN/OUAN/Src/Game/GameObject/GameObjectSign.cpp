#include "OUAN_Precompiled.h"

#include "GameObjectSign.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;

GameObjectSign::GameObjectSign(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SIGN)
{

}

GameObjectSign::~GameObjectSign()
{

}

void GameObjectSign::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSign::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectSign::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectSign::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSign::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSign::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSign::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr physicsComponentCharacter)
{
	mPhysicsComponentCharacter=physicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectSign::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectSign::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		if (mLogicComponent->existsInDreams())
			if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
			{
				mPhysicsComponentCharacter->create();
			}

		break;
	case NIGHTMARES:		
		setNightmaresRender();
		if (mLogicComponent->existsInNightmares())
			if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
			{
				mPhysicsComponentCharacter->destroy();
			}

		break;
	default:
		break;
	}
}

void GameObjectSign::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if (mLogicComponent->existsInDreams())
			mRenderComponentEntity->setVisible(true);
		break;
	case NIGHTMARES:
		if (mLogicComponent->existsInNightmares())
			mRenderComponentEntity->setVisible(true);
		break;
	default:
		break;
	}
}

void GameObjectSign::changeToWorld(int newWorld, double perc)
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

void GameObjectSign::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectSign::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectSign::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(SIGN_STATE_IDLE));
	mRenderComponentEntity->changeAnimation(SIGN_ANIM_IDLE);
	mRenderComponentEntity->setVisible((mWorld==DREAMS && mLogicComponent->existsInDreams()) ||
		(mWorld==NIGHTMARES && mLogicComponent->existsInNightmares()));
}

bool GameObjectSign::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSign::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectSign::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectSign::getPhysicsComponent() const
{
	return mPhysicsComponentCharacter;
}

/// Set logic component
void GameObjectSign::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectSign::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectSign::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectSign::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectSign::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectSign::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectSign::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectSign::getEntityComponent() const
{
	return mRenderComponentEntity;
}

void GameObjectSign::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(SIGN_ANIM_HIT)==0)
	{
		mLogicComponent->setHasTakenHit(false);
	}
}
void GameObjectSign::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{	
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		int currentState=mLogicComponent->getState();

		if (currentState==logicSS->getGlobalInt(SIGN_STATE_IDLE))
		{
			if (mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{
				mLogicComponent->setStateChanged(false);
				mLogicComponent->setHasTakenHit(false);
				mRenderComponentEntity->changeAnimation(SIGN_STATE_IDLE);					
			}
		}
		else if (currentState==logicSS->getGlobalInt(SIGN_STATE_HIT) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
		{	
			mRenderComponentEntity->changeAnimation(SIGN_STATE_HIT);			
		}
		if (mRenderComponentEntity.get())
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}
void GameObjectSign::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setDreamsMaterials();
	}
	else
	{
		mRenderComponentEntity->setVisible(false);
	}
}

void GameObjectSign::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntity->setVisible(false);
	}
	else
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setNightmaresMaterials();
	}
}

void GameObjectSign::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

//-------------------------------------------------------------------------------------------

TGameObjectSignParameters::TGameObjectSignParameters() : TGameObjectParameters()
{

}

TGameObjectSignParameters::~TGameObjectSignParameters()
{

}