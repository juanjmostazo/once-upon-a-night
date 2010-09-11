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

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectPortal::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectPortal::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

void GameObjectPortal::setRenderComponentGlowDreams(RenderComponentGlowPtr pRenderComponentGlow)
{
	mRenderComponentGlowDreams=pRenderComponentGlow;
}

void GameObjectPortal::setRenderComponentGlowNightmares(RenderComponentGlowPtr pRenderComponentGlow)
{
	mRenderComponentGlowNightmares=pRenderComponentGlow;
}

RenderComponentGlowPtr GameObjectPortal::getRenderComponentGlowDreams() const
{
	return mRenderComponentGlowDreams;
}

RenderComponentGlowPtr GameObjectPortal::getRenderComponentGlowNightmares() const
{
	return mRenderComponentGlowNightmares;
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

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldIdle(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldIdle)
{
	mRenderComponentParticleSystemChangeWorldIdle = pRenderComponentParticleSystemChangeWorldIdle;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldChanging(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldChanging)
{
	mRenderComponentParticleSystemChangeWorldChanging = pRenderComponentParticleSystemChangeWorldChanging;
}

void GameObjectPortal::setRenderComponentParticleSystemChangeWorldSky(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorldSky)
{
	mRenderComponentParticleSystemChangeWorldSky = pRenderComponentParticleSystemChangeWorldSky;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorldIdle() const
{
	return mRenderComponentParticleSystemChangeWorldIdle;
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

	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
	
	//mRenderComponentGlowDreams->setVisible(mRenderComponentGlowNightmares->isVisible());
	mRenderComponentGlowDreams->setVisible(false);
	mRenderComponentGlowNightmares->setVisible(false);
}

void GameObjectPortal::setNightmaresRender()
{
	if (!isEnabled()) 
	{
		return;
	}

	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();

	//mRenderComponentGlowNightmares->setVisible(mRenderComponentGlowDreams->isVisible());
	mRenderComponentGlowNightmares->setVisible(false);
	mRenderComponentGlowDreams->setVisible(false);
}

void GameObjectPortal::setChangeWorldFactor(double factor)
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

void GameObjectPortal::setChangeWorldRender()
{
	if (!isEnabled())
	{
		return;
	}

	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

void GameObjectPortal::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) 
	{
		return;
	}

	mRenderComponentParticleSystemChangeWorldIdle->start();
	mRenderComponentParticleSystemChangeWorldChanging->stop();
	//mRenderComponentParticleSystemChangeWorldSky->stop();

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			mRenderComponentEntityDreams->changeAnimation(PORTAL_ANIMATION_IDLE);
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			break;
		case NIGHTMARES:
			setNightmaresRender();
			mRenderComponentEntityNightmares->changeAnimation(PORTAL_ANIMATION_IDLE);
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
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

	mRenderComponentParticleSystemChangeWorldIdle->stop();
	mRenderComponentParticleSystemChangeWorldChanging->start();
	mRenderComponentParticleSystemChangeWorldSky->start();

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

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
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
}

bool GameObjectPortal::hasPositionalComponent() const
{
	return true;
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
		RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
			?mRenderComponentEntityDreams
			:mRenderComponentEntityNightmares;

		//RenderComponentGlowPtr glowToUpdate = (mWorld==DREAMS)
		//	?mRenderComponentGlowDreams
		//	:mRenderComponentGlowNightmares;

		if (isFirstUpdate())
		{
			mRenderComponentParticleSystemChangeWorldIdle->start();
			entityToUpdate->changeAnimation(PORTAL_ANIMATION_IDLE);
		}

		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();	

		int currentState=mLogicComponent->getState();
		if (mPhysicsComponentSimpleBox.get() && entityToUpdate.get())
		{
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
					displayText("ONY IS CLOSE");
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
			entityToUpdate->update(elapsedSeconds);
			if (mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->update(elapsedSeconds);
			}
		}
	}			
}

bool GameObjectPortal::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectPortal::getEntityComponent() const
{
	return (mWorld==DREAMS) ? mRenderComponentEntityDreams : mRenderComponentEntityNightmares;
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

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(visible);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(visible);
	}

	//Commented this lines because some they give null pointers
	//
	//mRenderComponentParticleSystemChangeWorldIdle->setVisible(visible);
	//mRenderComponentParticleSystemChangeWorldChanging->setVisible(visible);
	//mRenderComponentParticleSystemChangeWorldSky->setVisible(visible);
}
void GameObjectPortal::setCurrentWorldVisibility(bool visibility)
{	
	RenderComponentEntityPtr currentWorldEntity = (mGameWorldManager->getWorld()==DREAMS)
		? mRenderComponentEntityDreams
		: mRenderComponentEntityNightmares;

	currentWorldEntity->setVisible(visibility);
}
bool GameObjectPortal::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectPortal::getLogicComponentInstance() const
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