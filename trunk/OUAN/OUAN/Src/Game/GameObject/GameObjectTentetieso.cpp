#include "OUAN_Precompiled.h"

#include "GameObjectTentetieso.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTentetieso::GameObjectTentetieso(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TENTETIESO)
{

}

GameObjectTentetieso::~GameObjectTentetieso()
{

}

void GameObjectTentetieso::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

LogicComponentEnemyPtr GameObjectTentetieso::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}

void GameObjectTentetieso::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTentetieso::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTentetieso::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTentetieso::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTentetieso::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTentetieso::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTentetieso::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTentetieso::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTentetieso::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTentetieso::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectTentetieso::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
		?mRenderComponentEntityDreams
		:mRenderComponentEntityNightmares;

	if (isFirstUpdate())
	{
		entityToUpdate->changeAnimation("attack01_Clip");
	}

	entityToUpdate->update(elapsedSeconds/2);
}

void GameObjectTentetieso::setDreamsRender()
{
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
}

void GameObjectTentetieso::setNightmaresRender()
{
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();
}

void GameObjectTentetieso::setChangeWorldRender()
{
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}


void GameObjectTentetieso::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			mRenderComponentEntityDreams->changeAnimation("attack01_Clip");
			break;
		case NIGHTMARES:
			setNightmaresRender();
			mRenderComponentEntityNightmares->changeAnimation("attack01_Clip");
			break;
		default:break;
	}

}

void GameObjectTentetieso::changeWorldStarted(int newWorld)
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

void GameObjectTentetieso::changeToWorld(int newWorld, double perc)
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

void GameObjectTentetieso::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectTentetieso::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentEnemy->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentEnemy->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentEnemy->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentEnemy->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectTentetieso::reset()
{
	GameObject::reset();

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

bool GameObjectTentetieso::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTentetieso::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTentetieso::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTentetieso::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectTentetieso::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

void GameObjectTentetieso::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectTentetieso::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectTentetieso::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}
bool GameObjectTentetieso::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTentetieso::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}

bool GameObjectTentetieso::hasBeenHit() const
{
	return false;
}
bool GameObjectTentetieso::hasDied() const
{
	return false;
}
//-------------------------------------------------------------------------------------------
TGameObjectTentetiesoParameters::TGameObjectTentetiesoParameters() : TGameObjectParameters()
{

}

TGameObjectTentetiesoParameters::~TGameObjectTentetiesoParameters()
{

}