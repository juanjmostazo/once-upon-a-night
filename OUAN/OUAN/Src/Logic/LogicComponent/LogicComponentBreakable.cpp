#include "LogicComponentBreakable.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"

using namespace OUAN;

LogicComponentBreakable::LogicComponentBreakable(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_BREAKABLE)
{
	mIsBroken=false;
}

LogicComponentBreakable::~LogicComponentBreakable()
{

}

void LogicComponentBreakable::processCollision(GameObjectPtr pGameObject)
{
	/*
	//TODO CHECK WHY NEVER GOES HERE WHEN GAME OBJECT SHOULD BE ONY
	Ogre::LogManager::getSingleton().logMessage("[PROCESS COLLISION] breakable FROM " + pGameObject->getName());

	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0 && !mIsBroken)
	{
		Ogre::LogManager::getSingleton().logMessage("[PROCESS COLLISION] breakable FROM ONY");
		
		GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(getParent());
		if (CHECK_BIT(ony->getLogicComponentOny()->getState(), ONY_STATE_BIT_FIELD_ATTACK))
		{	
			Ogre::LogManager::getSingleton().logMessage("[PROCESS COLLISION] breakable FROM ONY, ATTACK STATE");

			setIsBroken(true);
			getParent()->disable();
		}
	}
	*/
}

bool LogicComponentBreakable::getIsBroken() const
{
	return mIsBroken;
}

void LogicComponentBreakable::setIsBroken(bool isBroken)
{
	if(isBroken)
	{
		setState(STATE_BREAKABLE_BROKEN);
	}
	else
	{
		setState(STATE_BREAKABLE_NOT_BROKEN);
	}

	mIsBroken=isBroken;
}

void LogicComponentBreakable::update(double elapsedTime)
{
	if (isStateChanged() && mIsBroken)
	{
		// SET BREAK ANIMATION
	}
}

TLogicComponentBreakableParameters::TLogicComponentBreakableParameters() : TLogicComponentParameters()
{

}

TLogicComponentBreakableParameters::~TLogicComponentBreakableParameters()
{

}
