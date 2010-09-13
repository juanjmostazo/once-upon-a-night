#include "OUAN_Precompiled.h"

#include "GameObjectBomb.h"
#include "../GameWorldManager.h"

#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectBomb::GameObjectBomb(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BOMB)
{

}

GameObjectBomb::~GameObjectBomb()
{

}

AudioComponentPtr GameObjectBomb::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectBomb::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

void GameObjectBomb::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
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
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
		if(mLogicComponentProp->existsInDreams())
		{
			mRenderComponentEntity->setVisible(true);
			mRenderComponentEntity->setDreamsMaterials();
		}
		else
		{
			mRenderComponentEntity->setVisible(false);
		}
	}
}

void GameObjectBomb::setNightmaresRender()
{
	if (!isEnabled()) return;
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
		if(mLogicComponentProp->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(true);
		}	
		else
		{
			mRenderComponentEntity->setVisible(false);
		}
	}
}

void GameObjectBomb::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
		mRenderComponentEntity->setChangeWorldFactor(factor);
	}
}

void GameObjectBomb::setChangeWorldRender()
{
	if (!isEnabled()) return;

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setChangeWorldMaterials();
	}
}

void GameObjectBomb::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
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

	if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->destroy();
	}

	mRenderComponentEntity->setVisible(false);

	disable();
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

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	int currentState=mLogicComponentProp->getState();

	//Logger::getInstance()->log("BOMB STATE "+Ogre::StringConverter::toString(currentState));

	if (mLogicComponentProp->isStateChanged())
	{
		if(currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
		{
			disable();
		}
		else if(currentState==logicSS->getGlobalInt(BOMB_STATE_IDLE))
		{
			initBombPuzzle();
			mRenderComponentEntity->changeAnimation(BOMB_ANIMATION_IDLE);
		}
		else if(currentState==logicSS->getGlobalInt(BOMB_STATE_ACTIVATE))
		{
			mLogicComponentProp->setTimeSpent(0);

			mRenderComponentParticleSystemExplosion->start();

			mRenderComponentEntity->changeAnimation(BOMB_ANIMATION_EXPLODE);

			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}

			mPhysicsComponentWeapon->startAttack();
		}
		else if(currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION))
		{
			mRenderComponentEntity->setVisible(false);
			mLogicComponentProp->setTimeSpent(0);
			mAudioComponent->playSound("fart");
		}
	}

	mRenderComponentEntity->update(elapsedSeconds);
}

//TODO DO IT PROPERLY WHEN THERE ARE TWO RENDER COMPONENT ENTITIES
void GameObjectBomb::updateLogic(double elapsedSeconds)
{
	mElapsedTime+=elapsedSeconds;

	GameObject::updateLogic(elapsedSeconds);
}

void GameObjectBomb::initBombPuzzle()
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	mLogicComponentProp->setState(logicSS->getGlobalInt(BOMB_STATE_IDLE));

	if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->create();
	}

	if (mPhysicsComponentSimpleBox.get())
	{
		if(mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}

		mPhysicsComponentSimpleBox->create();
		mPhysicsComponentSimpleBox->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentSimpleBox->setOrientation(mRenderComponentInitial->getOrientation());	
		mRenderComponentPositional->setPosition(mRenderComponentInitial->getPosition());
		mRenderComponentPositional->setOrientation(mRenderComponentInitial->getOrientation());
	}

	if(mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->endAttack();
	}


	switch(mWorld)
	{
		case DREAMS:
			mRenderComponentEntity->setVisible(true);
			setDreamsRender();
			break;
		case NIGHTMARES:
			mRenderComponentEntity->setVisible(true);
			setNightmaresRender();
			break;
		default:break;
	}

	mLogicComponentProp->setDelay(100);

	enable();

}


void GameObjectBomb::restartToInitialPoint()
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	mLogicComponentProp->setState(logicSS->getGlobalInt(BOMB_STATE_EXPLOSION));
	mLogicComponentProp->setTimeSpent(0);
}

void GameObjectBomb::activateExplosion()
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	mLogicComponentProp->setState(logicSS->getGlobalInt(BOMB_STATE_ACTIVATE));
	mLogicComponentProp->setTimeSpent(0);
}

bool GameObjectBomb::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectBomb::getEntityComponent() const
{
	return mRenderComponentEntity;
}

void GameObjectBomb::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
	//Logger::getInstance()->log("UPDATE BOMB");
	if(mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->update(elapsedSeconds);
	}
}

void GameObjectBomb::setVisible(bool visible)
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentProp->getState();

	if(!currentState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION) && !currentState==logicSS->getGlobalInt(BOMB_STATE_OFF))
	{
		switch(mWorld)
		{
		case DREAMS:
			if(mLogicComponentProp->existsInDreams())
			{
				mRenderComponentEntity->setVisible(visible);
			}
			break;
		case NIGHTMARES:
			if(mLogicComponentProp->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(visible);
			}
			break;
		default:
			break;
		}
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