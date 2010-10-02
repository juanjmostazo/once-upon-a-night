#include "OUAN_Precompiled.h"

#include "GameObjectTotem.h"
#include "GameObjectPortal.h"
#include "../GameWorldManager.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectTotem::GameObjectTotem(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TOTEM)
{

}

GameObjectTotem::~GameObjectTotem()
{

}

void GameObjectTotem::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTotem::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTotem::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTotem::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTotem::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTotem::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTotem::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectTotem::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectTotem::changeWorldFinished(int newWorld)
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
}

void GameObjectTotem::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	bool reachedLevel;
	reachedLevel=false;
	if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		if(mLevelTarget<mPhysicsComponentSimpleBox->getSceneNode()->getPosition().y)
		{
			Ogre::Vector3 newPosition=mPhysicsComponentSimpleBox->getSceneNode()->getPosition();
			newPosition.y=newPosition.y-elapsedSeconds*LEVEL_MOVEMENT_SPEED;
			if(newPosition.y<mLevelTarget)
			{
				newPosition.y=mLevelTarget;
				mAudioComponent->stopSound(TOTEM_SOUND_LEVEL_DOWN);
				reachedLevel=true;
			}

			Ogre::Vector3 positionDifference=newPosition-mPhysicsComponentSimpleBox->getSceneNode()->getPosition();
			mPhysicsComponentSimpleBox->setPosition(newPosition);

			GameObjectPtr obj = getGameWorldManager()->getObject(CHANGE_WORLD_ATTACHED);

			GameObjectPortalPtr portal= 
					BOOST_PTR_CAST(GameObjectPortal,obj);

			if(portal->getPhysicsComponentSimpleBox().get() && portal->getPhysicsComponentSimpleBox()->isInUse())
			{
				portal->getPhysicsComponentSimpleBox()->setPosition(
					portal->getPhysicsComponentSimpleBox()->getSceneNode()->getPosition()+positionDifference
					);
			}

			if(reachedLevel && mLevel==0)
			{
				if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				mRenderComponentEntity->setVisible(false);
				disable();
				if(getName().compare("totem#0")==0)
				{
					getGameWorldManager()->addExecutedLevelEvent(BOSS_PLATFORM_PUZZLE_END);
				}
			}
		}
	}

}

void GameObjectTotem::levelDown()
{
	mLevelTarget=mLevelTarget-LEVEL_DISTANCE;
	mAudioComponent->playSound(TOTEM_SOUND_LEVEL_DOWN);
	mLevel--;
}

void GameObjectTotem::changeWorldStarted(int newWorld)
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

void GameObjectTotem::changeToWorld(int newWorld, double perc)
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

void GameObjectTotem::reset()
{
	GameObject::reset();

	if(getName().compare("totem#0")!=0 || 
		!(getGameWorldManager()->hasExecutedLevelEvent(BOSS_PLATFORM_PUZZLE_END)))
	{
		if(mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->create();
		}
		mRenderComponentEntity->setVisible(true);

		mLevel=NUM_LEVELS;
		mPhysicsComponentSimpleBox->setPosition(mRenderComponentInitial->getPosition());
		mLevelTarget=mPhysicsComponentSimpleBox->getSceneNode()->getPosition().y;

	}
}

AudioComponentPtr GameObjectTotem::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectTotem::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

bool GameObjectTotem::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTotem::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectTotem::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTotem::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectTotem::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setChangeWorldFactor(factor);

}

bool GameObjectTotem::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTotem::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectTotem::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTotem::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectTotemParameters::TGameObjectTotemParameters() : TGameObjectParameters()
{

}

TGameObjectTotemParameters::~TGameObjectTotemParameters()
{

}