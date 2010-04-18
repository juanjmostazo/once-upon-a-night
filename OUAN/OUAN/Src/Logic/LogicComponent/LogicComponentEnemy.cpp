#include "LogicComponentEnemy.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"

using namespace OUAN;

LogicComponentEnemy::LogicComponentEnemy(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ENEMY)
{
	mHitRecoveryTime=-1;
}

LogicComponentEnemy::~LogicComponentEnemy()
{
}

void LogicComponentEnemy::processCollision(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0)
	{
		decreaseHP();
	}
}
void LogicComponentEnemy::increaseHP(int amount)
{
	if (getParent()->isEnabled())
	{
		if (getHealthPoints()+amount>getInitialHealthPoints())
			setHealthPoints(getInitialHealthPoints());
		else setHealthPoints(getHealthPoints()+amount);
	}
}
void LogicComponentEnemy::decreaseHP(int amount)
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
				//TODO CHANGESTATE DEAD
				//decreaseLives();				
			}
		}
	}
}

int LogicComponentEnemy::getNumLives() const
{
	return 0;
}
int LogicComponentEnemy::getHealthPoints() const
{
	return mHealthPoints;
}
void LogicComponentEnemy::setHealthPoints(int healthPoints)
{
	mHealthPoints=healthPoints;
}

int LogicComponentEnemy::getInitialHealthPoints() const
{
	return mInitialHealthPoints;
}
void LogicComponentEnemy::setInitialHealthPoints(int healthPoints)
{
	mInitialHealthPoints=healthPoints;
}

int LogicComponentEnemy::getLineOfSight() const
{
	return mLineOfSight;
}
void LogicComponentEnemy::setLineOfSight(int lineOfSight)
{
	mLineOfSight=lineOfSight;
}

int LogicComponentEnemy::getAttackRange() const
{
	return mAttackRange;
}
void LogicComponentEnemy::setAttackRange(int attackRange)
{
	mAttackRange=attackRange;
}

int LogicComponentEnemy::getAttackDamage() const
{
	return mAttackDamage;
}

void LogicComponentEnemy::setAttackDamage(int attackDamage)
{
	mAttackDamage=attackDamage;
}

int LogicComponentEnemy::getAttackDelay() const
{
	return mAttackDelay;
}

void LogicComponentEnemy::setAttackDelay(int attackDelay)
{
	mAttackDelay=attackDelay;
}

int LogicComponentEnemy::getColourSensitivityMask() const
{
	return mColourSensitivityMask;
}

void LogicComponentEnemy::setColourSensitivityMask(int colourSensitivityMask)
{
	mColourSensitivityMask=colourSensitivityMask;
}

TLogicComponentEnemyParameters::TLogicComponentEnemyParameters() : TLogicComponentParameters()
{
}

TLogicComponentEnemyParameters::~TLogicComponentEnemyParameters()
{
}
