#include "OUAN_Precompiled.h"

#include "GameObjectCryKing.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectCryKing::GameObjectCryKing(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CRYKING)
{

}

GameObjectCryKing::~GameObjectCryKing()
{

}

void GameObjectCryKing::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectCryKing::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

AudioComponentPtr GameObjectCryKing::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectCryKing::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


RenderComponentPositionalPtr GameObjectCryKing::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectCryKing::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectCryKing::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectCryKing::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectCryKing::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectCryKing::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectCryKing::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectCryKing::reset()
{
	GameObject::reset();

	mPhysicsComponentSimpleBox->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentSimpleBox->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
}

void GameObjectCryKing::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		mRenderComponentEntityDreams->setVisible(true);
		if(mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->create();
		}
		break;
	case NIGHTMARES:
		mRenderComponentEntityDreams->setVisible(false);
		if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}
		break;
	default:
		break;
	}
}

void GameObjectCryKing::changeWorldStarted(int newWorld)
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

void GameObjectCryKing::changeToWorld(int newWorld, double perc)
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

bool GameObjectCryKing::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectCryKing::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectCryKing::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectCryKing::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}


/// Set logic component
void GameObjectCryKing::setLogicComponentProp(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectCryKing::getLogicComponentProp()
{
	return mLogicComponent;
}


void GameObjectCryKing::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectCryKing::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectCryKing::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectCryKing::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectCryKing::getEntityComponent() const
{
	return mRenderComponentEntityDreams;
}
bool GameObjectCryKing::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectCryKing::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------
TGameObjectCryKingParameters::TGameObjectCryKingParameters() : TGameObjectParameters()
{

}

TGameObjectCryKingParameters::~TGameObjectCryKingParameters()
{

}