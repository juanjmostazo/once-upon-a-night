#include "OUAN_Precompiled.h"

#include "GameObjectTerrainTriangle.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

GameObjectTerrainTriangle::GameObjectTerrainTriangle(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TERRAINTRIANGLE)
{

}

GameObjectTerrainTriangle::~GameObjectTerrainTriangle()
{

}

void GameObjectTerrainTriangle::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainTriangle::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainTriangle::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTerrainTriangle::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTerrainTriangle::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTerrainTriangle::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTerrainTriangle::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTerrainTriangle::setRenderComponentParticleSystemChangeWorld(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorld)
{
	mRenderComponentParticleSystemChangeWorld = pRenderComponentParticleSystemChangeWorld;
}

RenderComponentParticleSystemPtr GameObjectTerrainTriangle::getRenderComponentParticleSystemChangeWorld() const
{
	return mRenderComponentParticleSystemChangeWorld;
}

void GameObjectTerrainTriangle::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectTerrainTriangle::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectTerrainTriangle::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectTerrainTriangle::setChangeWorldRender()
{
	if (!isEnabled()) return;
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
				mRenderComponentEntityNightmares->setVisible(false);
			}
			else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
				mRenderComponentEntityDreams->setVisible(false);
			}
			else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		default:break;
	}
}

void GameObjectTerrainTriangle::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentParticleSystemChangeWorld->stop();

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
}

void GameObjectTerrainTriangle::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentParticleSystemChangeWorld->start();

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

void GameObjectTerrainTriangle::changeToWorld(int newWorld, double perc)
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



void GameObjectTerrainTriangle::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->update(elapsedSeconds);
	}
	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->update(elapsedSeconds);
	}

	//mRenderComponentEntityDreams->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
	//mRenderComponentEntityNightmares->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
}

void GameObjectTerrainTriangle::reset()
{
	GameObject::reset();
}

bool GameObjectTerrainTriangle::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTerrainTriangle::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTerrainTriangle::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTerrainTriangle::getPhysicsComponent() const
{
	return getPhysicsComponentComplexTriangle();
}


/// Set logic component
void GameObjectTerrainTriangle::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTerrainTriangle::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTerrainTriangle::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectTerrainTriangle::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTerrainTriangle::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}
bool GameObjectTerrainTriangle::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTerrainTriangle::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
void GameObjectTerrainTriangle::setVisible(bool visible)
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
bool GameObjectTerrainTriangle::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTerrainTriangle::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------
TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
