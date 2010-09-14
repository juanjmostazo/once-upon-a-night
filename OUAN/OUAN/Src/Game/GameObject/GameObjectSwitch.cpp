#include "OUAN_Precompiled.h"

#include "GameObjectSwitch.h"
#include "../GameWorldManager.h"

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

	disable();
	setVisible(false);
	if(mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->destroy();
	}
	mPushable=false;
}

void GameObjectSwitch::makePushable()
{
	enable();
	setVisible(true);
	if(mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->create();
	}
	mPushable=true;
}

void GameObjectSwitch::setVisible(bool visible)
{
	if (!isEnabled() || !mPushable) return;
	mRenderComponentEntity->setVisible(visible);
}

void GameObjectSwitch::push()
{

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
//-------------------------------------------------------------------------------------------

TGameObjectSwitchParameters::TGameObjectSwitchParameters() : TGameObjectParameters()
{

}

TGameObjectSwitchParameters::~TGameObjectSwitchParameters()
{

}