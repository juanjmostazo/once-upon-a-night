#include "OUAN_Precompiled.h"

#include "GameObjectBomb.h"
#include "../GameWorldManager.h"

#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

GameObjectBomb::GameObjectBomb(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BOMB)
{

}

GameObjectBomb::~GameObjectBomb()
{

}

RenderComponentEntityPtr GameObjectBomb::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectBomb::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectBomb::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectBomb::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

void GameObjectBomb::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBomb::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBomb::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBomb::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBomb::setRenderComponentParticleSystemExplosion(RenderComponentParticleSystemPtr pRenderComponentParticleSystemExplosion)
{
	mRenderComponentParticleSystemExplosion = pRenderComponentParticleSystemExplosion;
}

RenderComponentParticleSystemPtr GameObjectBomb::getRenderComponentParticleSystemExplosion() const
{
	return mRenderComponentParticleSystemExplosion;
}

void GameObjectBomb::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectBomb::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectBomb::setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon)
{
	mPhysicsComponentWeapon=pPhysicsComponentWeapon;
}

PhysicsComponentWeaponPtr GameObjectBomb::getPhysicsComponentWeapon() const
{
	return mPhysicsComponentWeapon;
}

void GameObjectBomb::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentProp->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponentProp->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectBomb::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentProp->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponentProp->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectBomb::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponentProp->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponentProp->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectBomb::setChangeWorldRender()
{
	if (!isEnabled()) return;
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
				mRenderComponentEntityNightmares->setVisible(false);
			}
			else if(!mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponentProp->existsInDreams() && !mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		case NIGHTMARES:
			if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
				mRenderComponentEntityDreams->setVisible(false);
			}
			else if(!mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponentProp->existsInDreams() && !mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			break;
		default:break;
	}
}

void GameObjectBomb::changeWorldFinished(int newWorld)
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
			if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponentProp->existsInDreams()&& !mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(!mLogicComponentProp->existsInDreams()&& mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponentProp->existsInDreams()&& !mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}
			else if(!mLogicComponentProp->existsInDreams()&& mLogicComponentProp->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectBomb::changeWorldStarted(int newWorld)
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

void GameObjectBomb::changeToWorld(int newWorld, double perc)
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

void GameObjectBomb::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectBomb::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentProp->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentProp->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentProp->existsInDreams() && mLogicComponentProp->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentProp->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentProp->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectBomb::reset()
{
	GameObject::reset();

	if (mPhysicsComponentSimpleBox.get())
	{
		if(!mPhysicsComponentSimpleBox->isInUse())
			mPhysicsComponentSimpleBox->create();
		mPhysicsComponentSimpleBox->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentSimpleBox->setOrientation(mRenderComponentInitial->getOrientation());	
		mRenderComponentPositional->setPosition(mRenderComponentInitial->getPosition());
		mRenderComponentPositional->setOrientation(mRenderComponentInitial->getOrientation());
	}
}

bool GameObjectBomb::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBomb::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectBomb::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectBomb::getPhysicsComponent() const
{
	return mPhysicsComponentSimpleBox;
}

/// Set logic component
void GameObjectBomb::setLogicComponentProp(LogicComponentPropPtr logicComponentProp)
{
	mLogicComponentProp=logicComponentProp;
}

/// return logic component
LogicComponentPropPtr GameObjectBomb::getLogicComponentProp()
{
	return mLogicComponentProp;
}

void GameObjectBomb::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentProp.get())
	{
		mLogicComponentProp->processCollision(pGameObject, pNormal);
	}
}

void GameObjectBomb::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentProp.get())
	{
		mLogicComponentProp->processEnterTrigger(pGameObject);
	}
}

void GameObjectBomb::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentProp.get())
	{
		mLogicComponentProp->processExitTrigger(pGameObject);
	}
}

void GameObjectBomb::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
		?mRenderComponentEntityDreams
		:mRenderComponentEntityNightmares;
	
	if (entityToUpdate.get())
	{
		entityToUpdate->update(elapsedSeconds);
	}
}

//TODO DO IT PROPERLY WHEN THERE ARE TWO RENDER COMPONENT ENTITIES
void GameObjectBomb::updateLogic(double elapsedSeconds)
{

	if (mLogicComponentProp->isStateChanged())
	{
		//if (mLogicComponentProp->getState()==STATE_Prop_BROKEN)
		//{	
		//	if (mPhysicsComponentSimpleBox->isInUse())
		//	{
		//		mPhysicsComponentSimpleBox->destroy();
		//	}

		//	if (mLogicComponentProp->existsInDreams())
		//	{
		//		mRenderComponentEntityDreams->setVisible(false);						if (mRenderComponentEntityNightmares.get())
		//			mRenderComponentEntityNightmares->setVisible(false);
		//	}
		//	
		//	if (mLogicComponentProp->existsInNightmares())
		//	{
		//		mRenderComponentEntityNightmares->setVisible(false);
		//		if (mRenderComponentEntityDreams.get())
		//			mRenderComponentEntityDreams->setVisible(false);
		//	}		
		//}
	}	
	GameObject::updateLogic(elapsedSeconds);
}

void GameObjectBomb::restartToInitialPoint()
{
	Logger::getInstance()->log("RESET BOMB");

	reset();
}

void GameObjectBomb::activateExplosion()
{
}

bool GameObjectBomb::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectBomb::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}

void GameObjectBomb::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
}

void GameObjectBomb::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponentProp->existsInDreams())
		{
			mRenderComponentEntityDreams->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentProp->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(visible);
		}
		break;
	default:
		break;
	}
}

bool GameObjectBomb::hasLogicComponent() const
{
	return true;
}

LogicComponentPtr GameObjectBomb::getLogicComponentInstance() const
{
	return mLogicComponentProp;
}
void GameObjectBomb::processAnimationEnded(const std::string& animationName)
{

}
//-------------------------------------------------------------------------------------------

TGameObjectBombParameters::TGameObjectBombParameters() : TGameObjectParameters()
{

}

TGameObjectBombParameters::~TGameObjectBombParameters()
{

}