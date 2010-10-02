#include "OUAN_Precompiled.h"

#include "LogicComponentProp.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectDiamondTree.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"
#include "../../Game/GameObject/GameObjectBomb.h"
#include "../../Game/GameObject/GameObjectBreakableRock.h"
#include "../../Game/GameObject/GameObjectCryKing.h"
#include "../../Game/GameObject/GameObjectPlataform.h"
#include "../../Game/GameObject/GameObjectSwitch.h"
#include "../../Game/GameObject/GameObjectWater.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

LogicComponentProp::LogicComponentProp(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_PROP)
,mHasTakenHit(false)
,mRecovered(true)
{

}

LogicComponentProp::~LogicComponentProp()
{

}

void LogicComponentProp::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{

	//Logger::getInstance()->log(" LogicComponentProp::processCollision "+getParent()->getName()+" "+pGameObject->getName());

	GameWorldManagerPtr worldMgr = mParent->getGameWorldManager();
	ApplicationPtr app = worldMgr->getParent();

 	bool isParentDiamondTree = mParent->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	bool isWeaponCollision=pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 
		|| pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0;
	LogicSubsystemPtr logicSS = app->getLogicSubsystem();

	if(isParentDiamondTree && pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 && (getState()==logicSS->getGlobalInt(DT_STATE_IDLE) || getState()==logicSS->getGlobalInt(DT_STATE_MAY_HIT)))
	{		
		if (isRecovered())
		{
			//getParent()->displayText("THUD!");
			//TODO: LAUNCH PARTICLES!!
			mHasTakenHit=true;			

		}		
	}
	bool isParentSignpost = mParent->getType().compare(GAME_OBJECT_TYPE_SIGNPOST)==0;
	if (isParentSignpost && isWeaponCollision)
	{
		if(isRecovered())
		{
			mHasTakenHit=true;

			if (worldMgr->isFirstSignpostHit())
			{
				FirstSignpostHitEventPtr evt = FirstSignpostHitEventPtr(new FirstSignpostHitEvent());
				worldMgr->addEvent(evt);
			}
		}
	}
	bool isParentPortal = mParent->getType().compare(GAME_OBJECT_TYPE_PORTAL)==0;
	if (isParentPortal && isWeaponCollision)
	{
		if(mParent->getName().compare(FIRST_CHANGE_WORLD_GAME_OBJECT)==0 && !mParent->getGameWorldManager()->hasExecutedLevelEvent(EVENT_FIRST_CHANGE_WORLD_ACTIVATED))
		{
			mParent->getGameWorldManager()->addExecutedLevelEvent(EVENT_FIRST_CHANGE_WORLD_ACTIVATED);
		}
		else if(mParent->getName().compare(BOSS_STATUES_CHANGE_WORLD_GAME_OBJECT)==0 && !mParent->getGameWorldManager()->hasExecutedLevelEvent(CUTSCENE_8_BOSS_STATUES))
		{
			mParent->getGameWorldManager()->launchCutScene("cutscenes_level2.lua","cutScene8");
		}
		else
		{
			mHasTakenHit=true;
		}
	}
	bool isParentBomb = mParent->getType().compare(GAME_OBJECT_TYPE_BOMB)==0;
	if (isParentBomb && pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0)
	{
		GameObjectFlashLightPtr flashlight= 
			BOOST_PTR_CAST(GameObjectFlashLight,pGameObject);
		GameObjectBombPtr bomb= 
			BOOST_PTR_CAST(GameObjectBomb,getParent());
		if(flashlight->getColour()==RED)
		{
			mHasTakenHit=true;
			mTimeSpent=0;
		}
	}

	bool isParentCryKing = mParent->getType().compare(GAME_OBJECT_TYPE_CRYKING)==0;
	if (isParentCryKing && pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0)
	{
		if(mParent->getGameWorldManager()->getWorld()==DREAMS)
		{
			getParent()->getGameWorldManager()->restartBombPosition();
			GameObjectCryKingPtr cryking= 
				BOOST_PTR_CAST(GameObjectCryKing,getParent());
			cryking->getRenderComponentEntity()->changeAnimation(CRYKING_ANIMATION_IDLE_2);
		}
	}

	bool isParentBreakableRock = mParent->getType().compare(GAME_OBJECT_TYPE_BREAKABLE_ROCK)==0;
	if (isParentBreakableRock && pGameObject->getType().compare(GAME_OBJECT_TYPE_BOMB)==0)
	{
		GameObjectBreakableRockPtr rock= 
			BOOST_PTR_CAST(GameObjectBreakableRock,getParent());
		GameObjectBombPtr bomb= 
			BOOST_PTR_CAST(GameObjectBomb,pGameObject);

		LogicSubsystemPtr logicSS = mParent->getGameWorldManager()->getParent()->getLogicSubsystem();
		int bombState=bomb->getLogicComponentProp()->getState();

		if(bombState==logicSS->getGlobalInt(BOMB_STATE_EXPLOSION))
		{
			rock->breakRock();
		}
	}
	bool isParentSwitch = mParent->getType().compare(GAME_OBJECT_TYPE_SWITCH)==0;
	if (isParentSwitch && pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		mHasTakenHit=true;
	}

}

void LogicComponentProp::processEnterTrigger(GameObjectPtr pGameObject)
{
	bool isParentWater = mParent->getType().compare(GAME_OBJECT_TYPE_WATER)==0;
	if (isParentWater)
	{
		GameObjectWaterPtr water= 
			BOOST_PTR_CAST(GameObjectWater,getParent());

		water->gameObjectInsideWater(pGameObject);
		if(pGameObject->hasLogicComponent())
		{
			pGameObject->getLogicComponent()->setOnWater(true);
		}
	}
}

void LogicComponentProp::processExitTrigger(GameObjectPtr pGameObject)
{
	bool isParentWater = mParent->getType().compare(GAME_OBJECT_TYPE_WATER)==0;
	if (isParentWater)
	{
		GameObjectWaterPtr water= 
			BOOST_PTR_CAST(GameObjectWater,getParent());

		water->gameObjectOutsideWater(pGameObject);
		if(pGameObject->hasLogicComponent())
		{
			pGameObject->getLogicComponent()->setOnWater(false);
		}
	}
}
//void processActivate(ActivateEventPtr evt);
//void processAnimationEnded(AnimationEndedEventPtr evt);
//...

void LogicComponentProp::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
	mHasTakenHit=false;
}

double LogicComponentProp::getApproachDistance() const
{
	return mApproachDistance;
}
void LogicComponentProp::setApproachDistance(double approachDistance)
{
	mApproachDistance=approachDistance;
}

bool LogicComponentProp::isRecovered() const
{
	return mRecovered;
}
void LogicComponentProp::setRecovered(bool recovered)
{
	mRecovered=recovered;
}

double LogicComponentProp::getDelay() const
{
	return mDelay;
}
void LogicComponentProp::setDelay(double delay)
{
	mDelay=delay;
}
bool LogicComponentProp::hasTakenHit() const
{
	return mHasTakenHit;
}
void LogicComponentProp::setHasTakenHit(bool hasTakenHit)
{
	mHasTakenHit=hasTakenHit;
}
bool LogicComponentProp::isReload() const
{
	return mReload;
}
void LogicComponentProp::setReload(bool reload)
{
	mReload=reload;
}

TLogicComponentPropParameters::TLogicComponentPropParameters()
{
}
TLogicComponentPropParameters::~TLogicComponentPropParameters()
{

}