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

void GameObjectCryKing::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectCryKing::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectCryKing::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectCryKing::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectCryKing::setDreamsRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setDreamsMaterials();

}

void GameObjectCryKing::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setNightmaresMaterials();

}

void GameObjectCryKing::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectCryKing::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectCryKing::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	mRenderComponentEntity->update(elapsedSeconds);
}

void GameObjectCryKing::reset()
{
	GameObject::reset();

	mPhysicsComponentSimpleBox->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentSimpleBox->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());

	mRenderComponentEntity->changeAnimation(CRYKING_ANIMATION_IDLE_2);
}

void GameObjectCryKing::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		if(mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->create();
		}
		mRenderComponentEntity->changeAnimation(CRYKING_ANIMATION_IDLE_3);
		break;
	case NIGHTMARES:
		setNightmaresRender();
		if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}
		mRenderComponentEntity->changeAnimation(CRYKING_ANIMATION_CRY);
		break;
	default:
		break;
	}
}

void GameObjectCryKing::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;
	setChangeWorldRender();
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

void GameObjectCryKing::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(CRYKING_ANIMATION_IDLE_2)==0)
	{
		mRenderComponentEntity->changeAnimation(CRYKING_ANIMATION_IDLE_3);
	}
}

bool GameObjectCryKing::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectCryKing::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectCryKing::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectCryKing::getLogicComponent() const
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