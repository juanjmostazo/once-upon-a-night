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
		mTrajectoryComponent->activateTrajectory(getName(),false);
		mTrajectoryComponent->setLoopingTrajectory(true);
	}
}

void GameObjectPlataform::activate()
{
	mActivated=true;
}
bool GameObjectPlataform::isActivated()
{
	return mActivated;
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
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
				mRenderComponentEntityDreams->setVisible(true);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
				mRenderComponentEntityNightmares->setVisible(false);
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityNightmares->setVisible(true);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
				mRenderComponentEntityDreams->setVisible(false);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
				mRenderComponentEntityNightmares->setVisible(true);
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
	mLastPosition=getRenderComponentPositional()->getPosition();
	mLastPositionDifference=Vector3::ZERO;
	mElapsedTimeSinceLastCollision=0;
	mHit=false;
	mLastFrameHit=false;
	mOnyOntoPlatform=false;


	if((getName().compare("plataform#tower3_1")==0 ||
		getName().compare("plataform#tower3_2")==0 ||
		getName().compare("plataform#tower3_3")==0 ||
		getName().compare("plataform#tower3_4")==0 ||
		getName().compare("plataform#tower3_5")==0 ||
		getName().compare("plataform#tower3_6")==0) &&
		!getGameWorldManager()->hasExecutedLevelEvent(CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS))
	{
		mActivated=false;
	}
	else if((getName().compare("plataform#tower2_1")==0 ||
		getName().compare("plataform#tower2_2")==0) &&
		!getGameWorldManager()->hasExecutedLevelEvent(CUTSCENE_8_0_TRIPOLLO_STATUES_END))
	{
		mActivated=false;
	}
	else
	{
		mActivated=true;
	}

	mTrajectoryComponent->reset();
	mRenderComponentPositional->setPosition(mTrajectoryComponent->getCurrentPosition());
	if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
	{
		mPhysicsComponentComplexConvex->setPosition(mTrajectoryComponent->getCurrentPosition());
	}
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
void GameObjectPlataform::setLogicComponentProp(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectPlataform::getLogicComponentProp()
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

void GameObjectPlataform::activateHit()
{
	mOnyOntoPlatform=!mOnyOntoPlatform;
	
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->changeAnimation(PLATFORM_ANIM_JUMP);

		if(mRenderComponentEntityDreams->getEntity()->getMesh()->getName().compare(FLOWER_JUMPABLE_MESH)==0)
		{
			if(mOnyOntoPlatform)
			{
				mRenderComponentEntityDreams->setNewMaterial(PLATFORM_MATERIAL_1_JUMP_DREAMS,
					mLogicComponent->existsInDreams(),
					mLogicComponent->existsInNightmares());
			}
			else
			{
				mRenderComponentEntityDreams->setNewMaterial(PLATFORM_MATERIAL_1_NORMAL_DREAMS,
					mLogicComponent->existsInDreams(),
					mLogicComponent->existsInNightmares());
			}
			mRenderComponentEntityDreams->setDreamsMaterials();
		}
	}
	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->changeAnimation(PLATFORM_ANIM_JUMP);

		if(mRenderComponentEntityNightmares->getEntity()->getMesh()->getName().compare(FLOWER_JUMPABLE_MESH)==0)
		{
			if(mOnyOntoPlatform)
			{
				mRenderComponentEntityNightmares->setNewMaterial(PLATFORM_MATERIAL_1_JUMP_NIGHTMARES,
					mLogicComponent->existsInDreams(),
					mLogicComponent->existsInNightmares());
			}
			else
			{
				mRenderComponentEntityNightmares->setNewMaterial(PLATFORM_MATERIAL_1_NORMAL_NIGHTMARES,
					mLogicComponent->existsInDreams(),
					mLogicComponent->existsInNightmares());
			}
			mRenderComponentEntityNightmares->setNightmaresMaterials();
		}
	}

}

Ogre::Vector3 GameObjectPlataform::getLastPositionDifference()
{
	return mLastPositionDifference;
}

void GameObjectPlataform::resetElapsedTimeSinceLastCollision()
{
	mElapsedTimeSinceLastCollision=0;
}

void GameObjectPlataform::resetLastPositionDifference()
{
	mLastPositionDifference=Vector3::ZERO;
}

void GameObjectPlataform::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectPlataform::updatePhysicsComponents(double elapsedSeconds)
{
	//if(mHit && !mLastFrameHit)
	//{
	//	if(mLogicComponent->existsInDreams())
	//	{
	//		mRenderComponentEntityDreams->changeAnimation(PLATFORM_ANIM_JUMP);
	//	}
	//	if(mLogicComponent->existsInNightmares())
	//	{
	//		mRenderComponentEntityNightmares->changeAnimation(PLATFORM_ANIM_JUMP);
	//	}
	//}
	//else
	//{
	//	if(mLogicComponent->existsInDreams())
	//	{
	//		mRenderComponentEntityDreams->changeAnimation(PLATFORM_ANIM_IDLE);
	//	}
	//	if(mLogicComponent->existsInNightmares())
	//	{
	//		mRenderComponentEntityNightmares->changeAnimation(PLATFORM_ANIM_IDLE);
	//	}
	//}

	if(mActivated && mTrajectoryComponent->predefinedTrajectoryExists(getName()))
	{
		mTrajectoryComponent->update(elapsedSeconds);
		Vector3 position=mTrajectoryComponent->getNextMovement()+mRenderComponentPositional->getPosition();
		//Logger::getInstance()->log(Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)));
		//Logger::getInstance()->log("GameObjectPlataform::update " + getName() +" "+Ogre::StringConverter::toString(position));

		if(mElapsedTimeSinceLastCollision<PLATAFORM_COLLISION_TIME_MARGIN)
		{
			mElapsedTimeSinceLastCollision+=elapsedSeconds;
			mLastPositionDifference+=(position-mLastPosition);
		}
		else
		{
			mLastPositionDifference=position-mLastPosition;
		}
		mLastPosition=position;

		mRenderComponentPositional->setPosition(position);

		if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
		{
			mPhysicsComponentComplexConvex->setPosition(position);
		}
	}
	GameObject::updatePhysicsComponents(elapsedSeconds);


	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->update(elapsedSeconds);
	}
	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->update(elapsedSeconds);
	}
	mLastFrameHit=mHit;
	mHit=false;
}


bool GameObjectPlataform::isWorthUpdatingPhysicsComponents()
{
	return true;
}

bool GameObjectPlataform::hasLogicComponent() const
{
	return true;
}

void GameObjectPlataform::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(PLATFORM_ANIM_JUMP)==0)
	{
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntityDreams->changeAnimation(PLATFORM_ANIM_IDLE);
		}
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->changeAnimation(PLATFORM_ANIM_IDLE);
		}
	}

}

LogicComponentPtr GameObjectPlataform::getLogicComponent() const
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
