#include "LogicComponentOny.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Event/Event.h"

using namespace OUAN;

LogicComponentOny::LogicComponentOny(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ONY)
{
	mHitRecoveryTime=-1;
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
		if(mHitRecoveryTime<0)
		{
			decreaseHP();
			mHitRecoveryTime=1000;
		}
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

void LogicComponentOny::decreaseLives(int amount)
{
	setNumLives(getNumLives()-amount);
	if (getNumLives()<=0)
	{
		setNumLives(0);//safety assignment.
		gameOver();
	}
	else
	{
		loseLife();
	}
}


void LogicComponentOny::loseLife()
{
	setHealthPoints(getInitialHealthPoints());
	getParent()->disable();

	OnyDiesEventPtr evt=OnyDiesEventPtr(new OnyDiesEvent(getNumLives()));
	getParent()->getGameWorldManager()->addEvent(evt);
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
	LogicComponent::update(elapsedTime);

	if(mHitRecoveryTime>=0)
	{
		mHitRecoveryTime-=elapsedTime*1000;
	}
}

TLogicComponentOnyParameters::TLogicComponentOnyParameters() : TLogicComponentParameters()
{
}

TLogicComponentOnyParameters::~TLogicComponentOnyParameters()
{
}
