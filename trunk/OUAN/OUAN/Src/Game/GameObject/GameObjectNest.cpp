#include "OUAN_Precompiled.h"

#include "GameObjectNest.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectNest::GameObjectNest(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_NEST)
{

}

GameObjectNest::~GameObjectNest()
{

}

void GameObjectNest::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectNest::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectNest::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectNest::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectNest::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectNest::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectNest::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr physicsComponentCharacter)
{
	mPhysicsComponentCharacter=physicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectNest::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectNest::changeWorldFinished(int newWorld)
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

void GameObjectNest::changeWorldStarted(int newWorld)
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

void GameObjectNest::changeToWorld(int newWorld, double perc)
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

void GameObjectNest::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectNest::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectNest::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(NEST_STATE_IDLE));
	mRenderComponentEntity->changeAnimation(NEST_ANIM_IDLE);
	mRenderComponentEntity->setVisible((mWorld==DREAMS && mLogicComponent->existsInDreams()) ||
		(mWorld==NIGHTMARES && mLogicComponent->existsInNightmares()));
}

bool GameObjectNest::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectNest::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectNest::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectNest::getPhysicsComponent() const
{
	return mPhysicsComponentCharacter;
}

/// Set logic component
void GameObjectNest::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectNest::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectNest::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectNest::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectNest::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectNest::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectNest::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectNest::getEntityComponent() const
{
	return mRenderComponentEntity;
}

void GameObjectNest::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(NEST_ANIM_HATCH)==0)
	{
		spawnChild();
		disable();
	}
}
void GameObjectNest::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		mPhysicsComponentCharacter->destroy();

}
void GameObjectNest::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{	
		if (isFirstUpdate())
		{
			for (std::vector<GameObjectPtr>::iterator it=mChildren.begin();it!=mChildren.end();++it)
			{
				(*it)->disable();
			}
		}
		else
		{
			LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

			int currentState=mLogicComponent->getState();

			if (currentState==logicSS->getGlobalInt(NEST_STATE_IDLE))
			{
				if (mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
				{
					mLogicComponent->setStateChanged(false);
					mRenderComponentEntity->changeAnimation(NEST_ANIM_IDLE);					
					for (std::vector<GameObjectPtr>::iterator it=mChildren.begin();it!=mChildren.end();++it)
					{
						GameObjectPtr obj=*it;
						if (!obj->isEnabled())
						{
							obj->reset();
							obj->disable();
						}
					}

				}
			}
			else if (currentState==logicSS->getGlobalInt(NEST_STATE_SHAKING) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{	
				mRenderComponentEntity->changeAnimation(NEST_ANIM_SHAKE);	
			}
			else if (currentState==logicSS->getGlobalInt(NEST_STATE_HATCHING) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{	
				mRenderComponentEntity->changeAnimation(NEST_ANIM_HATCH);	
			}
			if (mRenderComponentEntity.get())
			{
				mRenderComponentEntity->update(elapsedSeconds);
			}

		}
	}
}
void GameObjectNest::setDreamsRender()
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

void GameObjectNest::setNightmaresRender()
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

void GameObjectNest::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

std::vector<GameObjectPtr>* GameObjectNest::getChildren()
{
	return &mChildren;
}
void GameObjectNest::setChildren(const std::vector<GameObjectPtr>& children)
{
	mChildren=children;
}
void GameObjectNest::addChild(GameObjectPtr child)
{
	mChildren.push_back(child);
}
void GameObjectNest::spawnChild()
{
	//decide which child to enable
	double dice=Utils::Random::getInstance()->getRandomDouble();
	double accumulated=dice;
	for (std::vector<GameObjectPtr>::iterator it=mChildren.begin();it!=mChildren.end();++it)
	{
		if (accumulated>(*it)->getSpawnProbability())
		{
			(*it)->enable();
			break;
		}
		else if (it+1!=mChildren.end())
		{
			accumulated+=(*(it+1))->getSpawnProbability();
		}
	}
}
void GameObjectNest::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------------------------

TGameObjectNestParameters::TGameObjectNestParameters() : TGameObjectParameters()
{

}

TGameObjectNestParameters::~TGameObjectNestParameters()
{

}