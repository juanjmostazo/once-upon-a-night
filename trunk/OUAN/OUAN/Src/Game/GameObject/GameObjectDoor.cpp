#include "OUAN_Precompiled.h"

#include "GameObjectDoor.h"
#include "../GameWorldManager.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectDoor::GameObjectDoor(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DOOR)
{

}

GameObjectDoor::~GameObjectDoor()
{

}

AudioComponentPtr GameObjectDoor::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectDoor::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


void GameObjectDoor::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDoor::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectDoor::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDoor::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDoor::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDoor::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDoor::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDoor::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDoor::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->destroy();
			}
			mRenderComponentEntity->changeAnimation(DOOR_ANIM_IDLE_OPEN);
			break;
		case NIGHTMARES:
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
			mRenderComponentEntity->changeAnimation(DOOR_ANIM_IDLE_CLOSE);
			break;
		default:
			break;
	}
}

void GameObjectDoor::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		mRenderComponentEntity->changeAnimation(DOOR_ANIM_OPEN);
		mAudioComponent->playSound(DOOR_SOUND_OPEN);
		break;
	case NIGHTMARES:
		mRenderComponentEntity->changeAnimation(DOOR_ANIM_CLOSE);
		mAudioComponent->playSound(DOOR_SOUND_CLOSE);
		break;
	default:
		break;
	}
}

void GameObjectDoor::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
	double currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();
	if(!mRenderComponentEntity->getCurrentAnimation()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(currentAnimName.compare(DOOR_ANIM_OPEN)!=0)
		{
			mRenderComponentEntity->changeAnimation(DOOR_ANIM_OPEN);
			mAudioComponent->playSound(DOOR_SOUND_OPEN);
		}
		break;
	case NIGHTMARES:
		if(currentAnimName.compare(DOOR_ANIM_CLOSE)!=0)
		{
			mRenderComponentEntity->changeAnimation(DOOR_ANIM_CLOSE);
			mAudioComponent->playSound(DOOR_SOUND_CLOSE);
		}
		break;
	default:
		break;
	}
}

void GameObjectDoor::reset()
{
	GameObject::reset();
}

bool GameObjectDoor::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDoor::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectDoor::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectDoor::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}

void GameObjectDoor::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	mRenderComponentEntity->update(elapsedSeconds);
}


/// Set logic component
void GameObjectDoor::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectDoor::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectDoor::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectDoor::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectDoor::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectDoor::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDoor::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectDoor::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectDoor::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectDoorParameters::TGameObjectDoorParameters() : TGameObjectParameters()
{

}

TGameObjectDoorParameters::~TGameObjectDoorParameters()
{

}