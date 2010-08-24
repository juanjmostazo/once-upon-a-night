#include "OUAN_Precompiled.h"

#include "GameObjectPlataform.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../../Graphics/TrajectoryManager/Trajectory.h"

using namespace OUAN;

GameObjectPlataform::GameObjectPlataform(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PLATAFORM)
{

}

GameObjectPlataform::~GameObjectPlataform()
{

}

void GameObjectPlataform::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectPlataform::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectPlataform::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectPlataform::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectPlataform::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPlataform::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPlataform::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPlataform::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPlataform::setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent)
{
	mTrajectoryComponent=pTrajectoryComponent;
}

TrajectoryComponentPtr GameObjectPlataform::getTrajectoryComponent()
{
	return mTrajectoryComponent;
}

void GameObjectPlataform::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectPlataform::getPhysicsComponentComplexConvex() const
{
	return mPhysicsComponentComplexConvex;
}
void GameObjectPlataform::activateTrajectory()
{
	if(mTrajectoryComponent->predefinedTrajectoryExists(getName()))
	{
		mTrajectoryComponent->activateTrajectory(getName());
		mTrajectoryComponent->setLoopingTrajectory(true);
	}
}

void GameObjectPlataform::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->destroy();
			}
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->destroy();
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
			{
				mPhysicsComponentComplexConvex->create();
			}
		}	
		break;
	default:break;
	}
}

void GameObjectPlataform::changeWorldStarted(int newWorld)
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

void GameObjectPlataform::changeToWorld(int newWorld, double perc)
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

void GameObjectPlataform::reset()
{
	GameObject::reset();
	activateTrajectory();
}

bool GameObjectPlataform::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectPlataform::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectPlataform::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectPlataform::getPhysicsComponent() const
{
	return getPhysicsComponentComplexConvex();
}

/// Set logic component
void GameObjectPlataform::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectPlataform::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectPlataform::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectPlataform::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPlataform::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectPlataform::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectPlataform::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
void GameObjectPlataform::setVisible(bool visible)
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

void GameObjectPlataform::update(double elapsedSeconds)
{
	if(mTrajectoryComponent->predefinedTrajectoryExists(getName()))
	{
		mTrajectoryComponent->update(elapsedSeconds);
		Vector3 position=mTrajectoryComponent->getCurrentPosition();
		//Logger::getInstance()->log(Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)));
		//Logger::getInstance()->log("GameObjectPlataform::update " + getName() +" "+Ogre::StringConverter::toString(position));
		mRenderComponentPositional->setPosition(position);
		if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
		{
			mPhysicsComponentComplexConvex->setPosition(position);
		}
	}
}

bool GameObjectPlataform::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectPlataform::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------
TGameObjectPlataformParameters::TGameObjectPlataformParameters() : TGameObjectParameters()
{

}

TGameObjectPlataformParameters::~TGameObjectPlataformParameters()
{

}
