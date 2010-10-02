#include "OUAN_Precompiled.h"

#include "GameObjectPortal.h"
#include "../GameWorldManager.h"

#include "../../Logic/LogicSubsystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectPortal::GameObjectPortal(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PORTAL)
{

}

GameObjectPortal::~GameObjectPortal()
{

}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectPortal::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntityBroken() const
{
	return mRenderComponentEntityBroken;
}

void GameObjectPortal::setRenderComponentEntityBroken(RenderComponentEntityPtr pRenderComponentEntityBroken)
{
	mRenderComponentEntityBroken=pRenderComponentEntityBroken;
}

void GameObjectPortal::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPortal::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPortal::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPortal::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldIdleDreams(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldIdleDreams)
{
	mRenderComponentParticleSystemChangeWorldIdleDreams = pRenderComponentParticleSystemChangeWorldIdleDreams;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldIdleNightmares(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldIdleNightmares)
{
	mRenderComponentParticleSystemChangeWorldIdleNightmares = pRenderComponentParticleSystemChangeWorldIdleNightmares;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldChanging(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldChanging)
{
	mRenderComponentParticleSystemChangeWorldChanging = pRenderComponentParticleSystemChangeWorldChanging;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldSky(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldSky)
{
	mRenderComponentParticleSystemChangeWorldSky = pRenderComponentParticleSystemChangeWorldSky;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorldIdleDreams() const
{
	return mRenderComponentParticleSystemChangeWorldIdleDreams;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorldIdleNightmares() const
{
	return mRenderComponentParticleSystemChangeWorldIdleNightmares;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorldChanging() const
{
	return mRenderComponentParticleSystemChangeWorldChanging;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorldSky() const
{
	return mRenderComponentParticleSystemChangeWorldSky;
}

void GameObjectPortal::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectPortal::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectPortal::setDreamsRender()
{
	if (!isEnabled()) 
	{
		return;
	}

	mRenderComponentEntity->setDreamsMaterials();
	mRenderComponentEntityBroken->setDreamsMaterials();
}

void GameObjectPortal::setNightmaresRender()
{
	if (!isEnabled()) 
	{
		return;
	}

	mRenderComponentEntity->setNightmaresMaterials();
	mRenderComponentEntityBroken->setNightmaresMaterials();
}

void GameObjectPortal::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectPortal::setChangeWorldRender()
{
	if (!isEnabled())
	{
		return;
	}

	mRenderComponentEntity->setChangeWorldMaterials();
	mRenderComponentEntityBroken->setChangeWorldMaterials();
}

void GameObjectPortal::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) 
	{
		return;
	}

	switch(newWorld)
	{
		case DREAMS: mRenderComponentParticleSystemChangeWorldIdleDreams->start(); break;
		case NIGHTMARES: mRenderComponentParticleSystemChangeWorldIdleNightmares->start(); break;
	}
	
	mRenderComponentParticleSystemChangeWorldChanging->stop();
	mRenderComponentParticleSystemChangeWorldSky->stop();

	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntityBroken->setVisible(false);

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			break;
		case NIGHTMARES:
			setNightmaresRender();
			break;
		default:
			break;
	}
}

void GameObjectPortal::changeWorldStarted(int newWorld)
{
	if (!isEnabled())
	{
		return;
	}

	mRenderComponentParticleSystemChangeWorldIdleDreams->stop();
	mRenderComponentParticleSystemChangeWorldIdleNightmares->stop();
	mRenderComponentParticleSystemChangeWorldChanging->start();
	mRenderComponentParticleSystemChangeWorldSky->start();

	mRenderComponentEntity->setVisible(false);
	mRenderComponentEntityBroken->setVisible(true);
	mRenderComponentEntityBroken->changeAnimation(PORTAL_ANIMATION_CHANGING_WORLD);

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

void GameObjectPortal::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) 
	{
		return;
	}

	std::string currentAnimName=mRenderComponentEntityBroken->getCurrentAnimationName();
	double currentAnimLen=mRenderComponentEntityBroken->getCurrentAnimationLength();
	if(!mRenderComponentEntityBroken->getCurrentAnimation()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mWorld==DREAMS)
		{
			mRenderComponentEntityBroken->setAnimationPosition(currentAnimLen*(1-perc));
		}
		else if(mWorld==NIGHTMARES)
		{
			mRenderComponentEntityBroken->setAnimationPosition(currentAnimLen*(perc));
		}
		break;
	case NIGHTMARES:
		if(mWorld==DREAMS)
		{
			mRenderComponentEntityBroken->setAnimationPosition(currentAnimLen*(perc));
		}
		else if(mWorld==NIGHTMARES)
		{
			mRenderComponentEntityBroken->setAnimationPosition(currentAnimLen*(1-perc));
		}
		break;
	default:
		break;
	}
	
	//displayText("CHANGING WORLD "+Ogre::StringConverter::toString(Ogre::Real(perc))+" delay:"+Ogre::StringConverter::toString(Ogre::Real(mChangeWorldDelay)));
}

void GameObjectPortal::reset()
{
	GameObject::reset();

	if (mAudioComponent->isPlaying("portal_close"))
	{
		mAudioComponent->stopSound("portal_close");
	}

	mRotY=0;

	if(getName().compare("changeworld#platform_big")!=0 || 
		!(getGameWorldManager()->hasExecutedLevelEvent(BOSS_PLATFORM_PUZZLE_END)))
	{
		mPhysicsComponentSimpleBox->setPosition(mRenderComponentInitial->getPosition());
	}
}

bool GameObjectPortal::hasPositionalComponent() const
{
	return true;
}

void GameObjectPortal::updatePhysicsComponents(double elapsedSeconds)
{

}

RenderComponentPositionalPtr GameObjectPortal::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectPortal::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectPortal::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}

/// Set logic component
void GameObjectPortal::setLogicComponentProp(LogicComponentPropPtr logicComponentProp)
{
	mLogicComponent=logicComponentProp;
}

/// return logic component
LogicComponentPropPtr GameObjectPortal::getLogicComponentProp()
{
	return mLogicComponent;
}

void GameObjectPortal::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectPortal::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPortal::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectPortal::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{
		if (isFirstUpdate())
		{
			mRenderComponentEntityBroken->setVisible(false);
			mRotY=0;
		}

		mRotY+=PORTAL_ROTATION_SPEED*elapsedSeconds;
		if(mRotY>=360)
		{
			mRotY-=360;
		}
		Quaternion yaw(Ogre::Degree(mRotY),Vector3::UNIT_Y);

		mPhysicsComponentSimpleBox->setOrientation(yaw);
		//mRenderComponentPositional->getSceneNode()->yaw(Ogre::Degree(PORTAL_ROTATION_SPEED*elapsedSeconds));

		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();	

		int currentState=mLogicComponent->getState();

		if (currentState==logicSS->getGlobalInt(PORTAL_STATE_IDLE))
		{
			if (mLogicComponent->isStateChanged())
			{
				if (mAudioComponent->isPlaying(PORTAL_SOUND_CLOSE))
				{
					mAudioComponent->stopSound(PORTAL_SOUND_CLOSE);
				}
				//glowToUpdate->setVisible(false);
			}
		}
		else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_ONY_APPROACHING))
		{				
			if (mLogicComponent->isStateChanged())
			{
				//mAudioComponent->playSound(PORTAL_SOUND_CLOSE);
				//displayText("ONY IS CLOSE");
				//glowToUpdate->setVisible(true);
			}
		}
		else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_HIT))
		{				
			if (mLogicComponent->isStateChanged())
			{
				getGameWorldManager()->changeWorld();
			}
		}
		else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_CHANGING_WORLD))
		{
			if (mLogicComponent->isStateChanged())
			{
				mAudioComponent->playSound(PORTAL_SOUND_CHANGEWORLD);
			}
		}
		
		mRenderComponentEntity->update(elapsedSeconds);
		mRenderComponentEntityBroken->update(elapsedSeconds);
	}			
}

bool GameObjectPortal::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectPortal::getEntityComponent() const
{
	return mRenderComponentEntity;
}

bool GameObjectPortal::hasAudioComponent() const
{
	return true;
}

AudioComponentPtr GameObjectPortal::getAudioComponentInstance() const
{
	return mAudioComponent;
}

AudioComponentPtr GameObjectPortal::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectPortal::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

void GameObjectPortal::setVisible(bool visible)
{

	if(mIsChangingWorld)
	{
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntityBroken->setVisible(visible);
		}

		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityBroken->setVisible(visible);
		}
	}
	else
	{
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntity->setVisible(visible);
		}

		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(visible);
		}
	}

	//Commented this lines because some they give null pointers
	//
	mRenderComponentParticleSystemChangeWorldIdleDreams->setVisible(visible);
	mRenderComponentParticleSystemChangeWorldIdleNightmares->setVisible(visible);
	mRenderComponentParticleSystemChangeWorldChanging->setVisible(visible);
	mRenderComponentParticleSystemChangeWorldSky->setVisible(visible);
}

bool GameObjectPortal::hasLogicComponent() const
{
	return true;
}

LogicComponentPtr GameObjectPortal::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{

}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{

}