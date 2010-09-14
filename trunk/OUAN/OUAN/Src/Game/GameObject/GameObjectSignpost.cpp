#include "OUAN_Precompiled.h"

#include "GameObjectSignpost.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectSignpost::GameObjectSignpost(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SIGNPOST)
{

}

GameObjectSignpost::~GameObjectSignpost()
{

}

void GameObjectSignpost::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSignpost::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectSignpost::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

AudioComponentPtr GameObjectSignpost::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectSignpost::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


void GameObjectSignpost::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSignpost::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSignpost::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSignpost::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr physicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=physicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectSignpost::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectSignpost::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		if (mLogicComponent->existsInDreams())
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}

		break;
	case NIGHTMARES:		
		setNightmaresRender();
		if (mLogicComponent->existsInNightmares())
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}

		break;
	default:
		break;
	}
}

void GameObjectSignpost::changeWorldStarted(int newWorld)
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

void GameObjectSignpost::changeToWorld(int newWorld, double perc)
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

void GameObjectSignpost::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectSignpost::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectSignpost::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(SIGN_STATE_IDLE));
	mRenderComponentEntity->changeAnimation(SIGN_ANIM_IDLE);
	mRenderComponentEntity->setVisible((mWorld==DREAMS && mLogicComponent->existsInDreams()) ||
		(mWorld==NIGHTMARES && mLogicComponent->existsInNightmares()));

	mLogicComponent->setRecovered(true);
}

bool GameObjectSignpost::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSignpost::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectSignpost::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectSignpost::getPhysicsComponent() const
{
	return mPhysicsComponentSimpleBox;
}

/// Set logic component
void GameObjectSignpost::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectSignpost::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectSignpost::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectSignpost::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectSignpost::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectSignpost::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectSignpost::getEntityComponent() const
{
	return mRenderComponentEntity;
}

void GameObjectSignpost::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(SIGN_ANIM_HIT)==0)
	{
		mLogicComponent->setRecovered(true);
	}

}
void GameObjectSignpost::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{	
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		int currentState=mLogicComponent->getState();

		if (currentState==logicSS->getGlobalInt(SIGN_STATE_IDLE))
		{
			mRenderComponentEntity->changeAnimation(SIGN_ANIM_IDLE);
		}
		else if (currentState==logicSS->getGlobalInt(SIGN_STATE_HIT) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
		{	
			mRenderComponentEntity->changeAnimation(SIGN_ANIM_HIT);	
			//displayText(getTranslation(getSignpostMessage()));
			mMessageBox->setMessageBoxText();
			mMessageBox->show();
			if(mWorld==DREAMS)
			{
				mAudioComponent->playSound("signpost_d");
			}
			else if(mWorld==NIGHTMARES)
			{
				mAudioComponent->playSound("signpost_n");
			}

			mLogicComponent->setRecovered(false);
		}
		if (mRenderComponentEntity.get())
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
		mMessageBox->update(elapsedSeconds);
	}
}
void GameObjectSignpost::setDreamsRender()
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

void GameObjectSignpost::setNightmaresRender()
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

void GameObjectSignpost::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectSignpost::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

//const std::string& GameObjectSignpost::getSignpostMessage() const
//{
//	return mSignpostMessage;
//}
//void GameObjectSignpost::setSignpostMessage(const std::string& signpostMessage)
//{
//	mSignpostMessage=signpostMessage;
//}
void GameObjectSignpost::setVisible(bool visible)
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
RenderComponentMessageBoxPtr GameObjectSignpost::getRenderComponentMessageBox() const
{
	return mMessageBox;
}
void GameObjectSignpost::setRenderComponentMessageBox(RenderComponentMessageBoxPtr messageBox)
{
	mMessageBox=messageBox;
}

bool GameObjectSignpost::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectSignpost::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectSignpostParameters::TGameObjectSignpostParameters() : TGameObjectParameters()
{

}

TGameObjectSignpostParameters::~TGameObjectSignpostParameters()
{

}