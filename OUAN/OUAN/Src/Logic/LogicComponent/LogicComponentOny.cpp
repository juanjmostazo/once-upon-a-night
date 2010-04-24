#include "LogicComponentOny.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Event/Event.h"

using namespace OUAN;

LogicComponentOny::LogicComponentOny(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ONY)
{
	mHitRecoveryTime=-1;
	mEventInducedStateChange=true;
}

LogicComponentOny::~LogicComponentOny()
{
}

void LogicComponentOny::processCollision(GameObjectPtr pGameObject)
{
	if (!pGameObject->isEnabled() || !getParent()->isEnabled()) 
	{
		return;
	}

	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP)==0)
	{
		increaseLives();
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP)==0)
	{
		setHealthPoints(getInitialHealthPoints());
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_HEART)==0)
	{
		increaseHP();
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_DIAMOND)==0)
	{
		//TODO
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_CLOCKPIECE)==0)
	{
		//TODO
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_STORYBOOK)==0)
	{
		//TODO
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_TRIPOLLO)==0)
	{
		if(mHitRecoveryTime<0 && !CHECK_BIT(mState,ONY_STATE_BIT_FIELD_DIE))
		{
			int oldLives=getNumLives();
			decreaseHP();
			mHitRecoveryTime=2;
			if (getNumLives()==oldLives)
			{
				OnyTakesHitEventPtr evt = OnyTakesHitEventPtr(new OnyTakesHitEvent());
				getParent()->getGameWorldManager()->addEvent(evt);
			}			
		}
	}
}
void LogicComponentOny::processAnimationEnded(const std::string& animationName)
{
	int tempState=getState();
	if (animationName.compare(ONY_ANIM_HIT01)==0)
	{
		//if (mHitRecoveryTime<0)
		//{								
			setState(CLEAR_BIT(tempState,ONY_STATE_BIT_FIELD_HIT));
			mEventInducedStateChange=true;
		//}
	}
	else if (animationName.compare(ONY_ANIM_DIE01)==0)
	{
		setState(CLEAR_BIT(tempState,ONY_STATE_BIT_FIELD_DIE));
		mEventInducedStateChange=true;
		mParent->getGameWorldManager()->onyDied();
	}
}

void LogicComponentOny::increaseHP(int amount)
{
	if (getParent()->isEnabled())
	{
		if (getHealthPoints()+amount>getInitialHealthPoints())
			setHealthPoints(getInitialHealthPoints());
		else setHealthPoints(getHealthPoints()+amount);
	}
}
void LogicComponentOny::decreaseHP(int amount)
{	
	if (getParent()->isEnabled())
	{
		if (getHealthPoints()>0 && getNumLives()>0)
		{
			setHealthPoints(getHealthPoints()-amount<0
				?0
				:getHealthPoints()-amount);
			if (getHealthPoints()==0)
			{
				decreaseLives();				
			}
		}
	}
}
void LogicComponentOny::increaseLives(int amount)
{
	setNumLives(getNumLives()+amount);
}

void LogicComponentOny::decreaseLives(int amount,bool fallDown)
{
	setNumLives(getNumLives()-amount);
	if (getNumLives()<=0)
	{
		setNumLives(0);//safety assignment.
		gameOver();
	}
	else
	{
		loseLife(fallDown);
	}
}


void LogicComponentOny::loseLife(bool fallDown)
{
	if(!getParent()->getGameWorldManager()->getGodMode())
	{
		if (fallDown)
			setHealthPoints(getInitialHealthPoints());
		//getParent()->disable();

		OnyDiesEventPtr evt=OnyDiesEventPtr(new OnyDiesEvent(getNumLives(),fallDown));
		getParent()->getGameWorldManager()->addEvent(evt);
	}
}

void LogicComponentOny::gameOver()
{
	//TODO: ADDITIONAL STUFF (Or redefine in subclass for type-specific behaviour)
	getParent()->disable();

	GameOverEventPtr evt=GameOverEventPtr(new GameOverEvent(false));
	getParent()->getGameWorldManager()->addEvent(evt);
}

int LogicComponentOny::getAttackDamage() const
{
	return mAttackDamage;
}

void LogicComponentOny::setAttackDamage(int attackDamage)
{
	mAttackDamage=attackDamage;
}

int LogicComponentOny::getHealthPoints() const
{
	return mHealthPoints;
}
void LogicComponentOny::setHealthPoints(int healthPoints)
{
	mHealthPoints=healthPoints;
}

int LogicComponentOny::getNumLives() const
{
	return mNumLives;
}
void LogicComponentOny::setNumLives(int numLives)
{
	mNumLives=numLives;
}

int LogicComponentOny::getInitialHealthPoints() const
{
	return mInitialHealthPoints;
}
void LogicComponentOny::setInitialHealthPoints(int healthPoints)
{
	mInitialHealthPoints=healthPoints;
}

int LogicComponentOny::getInitialNumLives() const
{
	return mInitialNumLives;
}
void LogicComponentOny::setInitialNumLives(int numLives)
{
	mInitialNumLives=numLives;
}

void LogicComponentOny::update(double elapsedTime)
{
	GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(getParent());
	if (CHECK_BIT(getState(), ONY_STATE_BIT_FIELD_JUMP) && !ony->getPhysicsComponentCharacter()->isJumping())
	{
		setState(CLEAR_BIT(getState(),ONY_STATE_BIT_FIELD_JUMP));
	}
	else if (!mEventInducedStateChange)
			setStateChanged(false);

	if(mHitRecoveryTime>=0)
	{
		mHitRecoveryTime-=elapsedTime;
	}
	// mEventInducedStateChange=false;
}
void LogicComponentOny::setEventInducedStateChange(bool eventInducedStateChange)
{
	mEventInducedStateChange=eventInducedStateChange;
}
bool LogicComponentOny::isEventInducedStateChange() const
{
	return mEventInducedStateChange;
}

TLogicComponentOnyParameters::TLogicComponentOnyParameters() : TLogicComponentParameters()
{
}

TLogicComponentOnyParameters::~TLogicComponentOnyParameters()
{
}
