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

void GameObjectPortal::setRenderComponentParticleSystemChangeWorld(RenderComponentParticleSystemPtr pRenderComponentParticleSystemChangeWorld)
{
	mRenderComponentParticleSystemChangeWorld = pRenderComponentParticleSystemChangeWorld;
}

RenderComponentParticleSystemPtr GameObjectPortal::getRenderComponentParticleSystemChangeWorld() const
{
	return mRenderComponentParticleSystemChangeWorld;
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
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
	
	mRenderComponentGlowDreams->setVisible(mRenderComponentGlowNightmares->isVisible());
	mRenderComponentGlowNightmares->setVisible(false);
}

void GameObjectPortal::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();

	mRenderComponentGlowNightmares->setVisible(mRenderComponentGlowDreams->isVisible());
	mRenderComponentGlowDreams->setVisible(false);
}

void GameObjectPortal::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

void GameObjectPortal::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			mRenderComponentEntityDreams->changeAnimation(PORTAL_ANIMATION_IDLE);
			break;
		case NIGHTMARES:
			setNightmaresRender();
			mRenderComponentEntityNightmares->changeAnimation(PORTAL_ANIMATION_IDLE);
			break;
		default:
			break;
	}
}

void GameObjectPortal::changeWorldStarted(int newWorld)
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

void GameObjectPortal::changeToWorld(int newWorld, double perc)
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
void GameObjectPortal::setLogicComponentUsable(LogicComponentUsablePtr logicComponentUsable)
{
	mLogicComponentUsable=logicComponentUsable;
}

/// return logic component
LogicComponentUsablePtr GameObjectPortal::getLogicComponentUsable()
{
	return mLogicComponentUsable;
}

void GameObjectPortal::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentUsable.get())
	{
		mLogicComponentUsable->processCollision(pGameObject, pNormal);
	}
}

void GameObjectPortal::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentUsable.get())
	{
		mLogicComponentUsable->processEnterTrigger(pGameObject);
	}
}

void GameObjectPortal::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentUsable.get())
	{
		mLogicComponentUsable->processExitTrigger(pGameObject);
	}
}

void GameObjectPortal::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentUsable.get())
	{
		mLogicComponentUsable->update(elapsedSeconds);
	}
}

void GameObjectPortal::activate()
{
	if (mLogicComponentUsable.get())
	{
		mLogicComponentUsable->setCanBeActivated(false);
		mLogicComponentUsable->setIsActivated(true);
	}
}
bool GameObjectPortal::canBeActivated() const
{
	int activationState = mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(PORTAL_STATE_ONY_MAY_ACTIVATE);
	return mLogicComponentUsable.get() && mLogicComponentUsable->getState()==activationState && mLogicComponentUsable->canBeActivated();
}

void GameObjectPortal::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if (isEnabled())
	{
		RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
			?mRenderComponentEntityDreams
			:mRenderComponentEntityNightmares;

		RenderComponentGlowPtr glowToUpdate = (mWorld==DREAMS)
			?mRenderComponentGlowDreams
			:mRenderComponentGlowNightmares;

		if (isFirstUpdate())
		{
			entityToUpdate->changeAnimation("turn_Clip");
		}

		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();	

		int currentState=mLogicComponentUsable->getState();
		if (mPhysicsComponentSimpleBox.get() && entityToUpdate.get())
		{
			if (currentState==logicSS->getGlobalInt(PORTAL_STATE_IDLE))
			{
				if (mLogicComponentUsable->isStateChanged())
				{
					mLogicComponentUsable->setCanBeActivated(false);
					if (mAudioComponent->isPlaying("portal_close"))
					{
						mAudioComponent->stopSound("portal_close");
					}
					glowToUpdate->setVisible(false);
				}
			}
			else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_ONY_APPROACHING))
			{				
				if (mLogicComponentUsable->isStateChanged())
				{
					mLogicComponentUsable->setCanBeActivated(false);
					mAudioComponent->playSound("portal_close");
					displayText("ONY IS CLOSE");
					glowToUpdate->setVisible(true);
				}
			}
			else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_ONY_MAY_ACTIVATE))
			{
				if (mLogicComponentUsable->isStateChanged())
				{
					displayText("PRESS ACTION TO CHANGE WORLD");
					mLogicComponentUsable->setCanBeActivated(true);
					glowToUpdate->setVisible(true);
				}
			}
			else if (currentState==logicSS->getGlobalInt(PORTAL_STATE_CHANGING_WORLD))
			{
				if (mLogicComponentUsable->isStateChanged())
				{
					getGameWorldManager()->changeWorld();				
					mLogicComponentUsable->setIsActivated(false);
					mRenderComponentParticleSystemChangeWorld->start();
					glowToUpdate->setVisible(true);
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

//-------------------------------------------------------------------------------------------

TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{

}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{

}