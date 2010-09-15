#include "OUAN_Precompiled.h"

#include "GameObjectSwitch.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;

GameObjectSwitch::GameObjectSwitch(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SWITCH)
{

}

GameObjectSwitch::~GameObjectSwitch()
{

}

void GameObjectSwitch::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSwitch::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectSwitch::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectSwitch::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSwitch::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSwitch::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSwitch::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectSwitch::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectSwitch::changeWorldFinished(int newWorld)
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

void GameObjectSwitch::changeWorldStarted(int newWorld)
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

void GameObjectSwitch::changeToWorld(int newWorld, double perc)
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

bool GameObjectSwitch::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectSwitch::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectSwitch::setLogicComponentProp(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectSwitch::getLogicComponentProp()
{
	return mLogicComponent;
}


void GameObjectSwitch::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectSwitch::reset()
{
	GameObject::reset();

	mRenderComponentEntity->setVisible(false);
	if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->destroy();
	}
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	mLogicComponent->setState(logicSS->getGlobalInt(SWITCH_STATE_OFF));

}

void GameObjectSwitch::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	int currentState=mLogicComponent->getState();
	int world = getGameWorldManager()->getWorld();

	if (mLogicComponent->isStateChanged())
	{
		if(currentState==logicSS->getGlobalInt(SWITCH_STATE_OFF))
		{
			reset();
		}
		else if(currentState==logicSS->getGlobalInt(SWITCH_STATE_PUSHABLE))
		{
		}
		else if(currentState==logicSS->getGlobalInt(SWITCH_STATE_PUSHED))
		{
			mPhysicsComponentSimpleBox->setPosition(mPhysicsComponentSimpleBox->getSceneNode()->getPosition()-SWITCH_PUSH_DISTANCE);
			mAudioComponent->playSound(SWITCH_SOUND_PUSHED);
		}
	}
}

AudioComponentPtr GameObjectSwitch::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectSwitch::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

void GameObjectSwitch::makePushable()
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	mLogicComponent->setState(logicSS->getGlobalInt(SWITCH_STATE_PUSHABLE));
	mLogicComponent->setStateChanged(true);
	if(mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->create();
	}
	mRenderComponentEntity->setVisible(true);
}

void GameObjectSwitch::setVisible(bool visible)
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	int currentState=mLogicComponent->getState();

	if (!isEnabled() || currentState==logicSS->getGlobalInt(SWITCH_STATE_OFF)) return;
	mRenderComponentEntity->setVisible(visible);
}

bool GameObjectSwitch::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectSwitch::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectSwitch::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectSwitch::getLogicComponentInstance() const
{
	return mLogicComponent;
}

void GameObjectSwitch::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectSwitch::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectSwitch::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

//-------------------------------------------------------------------------------------------

TGameObjectSwitchParameters::TGameObjectSwitchParameters() : TGameObjectParameters()
{

}

TGameObjectSwitchParameters::~TGameObjectSwitchParameters()
{

}