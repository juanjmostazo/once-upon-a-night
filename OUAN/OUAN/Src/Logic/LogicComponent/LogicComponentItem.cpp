#include "OUAN_Precompiled.h"

#include "LogicComponentItem.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectDiamond.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

LogicComponentItem::LogicComponentItem(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ITEM)
{
	mIsTaken=false;
}

LogicComponentItem::~LogicComponentItem()
{

}

void LogicComponentItem::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0 && !mIsTaken)
	{
		setIsTaken(true);
		getParent()->startCollisionEffects();
		getParent()->disable();
	}
}

bool LogicComponentItem::getIsTaken() const
{
	return mIsTaken;
}

void LogicComponentItem::setIsTaken(bool isTaken)
{
	if(isTaken)
	{
		setState(STATE_ITEM_TAKEN);
	}
	else
	{
		setState(STATE_ITEM_NOT_TAKEN);
	}

	mIsTaken=isTaken;
}

TLogicComponentItemParameters::TLogicComponentItemParameters() : TLogicComponentParameters()
{

}

TLogicComponentItemParameters::~TLogicComponentItemParameters()
{

}
