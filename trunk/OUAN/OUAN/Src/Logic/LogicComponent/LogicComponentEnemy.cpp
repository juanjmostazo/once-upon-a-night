#include "OUAN_Precompiled.h"

#include "LogicComponentEnemy.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"
#include "../../Game/GameObject/GameObjectPillow.h"

using namespace OUAN;

LogicComponentEnemy::LogicComponentEnemy(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ENEMY)
{
	mHitRecoveryTime=-1;
	mHasDied=false;
	mHasBeenHit=false;
	mHasHeardCall=false;
	mCallWasHeard=false;
	mAlertFinished=true;
	mCallToArmsFinished=true;
	mFalseAlarmFinished=true;
	mSurpriseFinished=true;
	mAttackFinished=true;
	mTiredFinished=true;	
	mIdle1Finished=true;
	mStatueEnabled=false;
	mPillowHitFinished=false;
	mFlashlightHitFinished=false;
}

LogicComponentEnemy::~LogicComponentEnemy()
{
}

void LogicComponentEnemy::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0)
	{
		GameObjectFlashLightPtr flashlight=BOOST_PTR_CAST(GameObjectFlashLight,pGameObject);
		int flashlightColour=flashlight->getColour();		
		if ( mHitRecoveryTime<0 && !mHasBeenHit && !mHasDied)
		{
			std::stringstream msg;
					if (getMaskValueFromColour(flashlightColour) & mColourSensitivityMask)
			{
				getParent()->displayText("FWOOOOSHH!!!!");			
				mHasBeenHit=true;
				decreaseHP(flashlight->getAttackDamage());
				std::stringstream msg("");
				msg<<getParentName()<<" remaining HP: "<<mHealthPoints;
				Logger::getInstance()->log(msg.str());
				mHitRecoveryTime=1;//TODO: use animation instead of hit time
			}		
			else
			{
				msg.str("");
				msg<<"TRY "<<getMaskString();
				getParent()->displayText(msg.str());
			}
		}
	}
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 && !mHasBeenHit && !mHasDied)
	{
		GameObjectPillowPtr pillow=BOOST_PTR_CAST(GameObjectPillow,
			pGameObject);
		if (mHitRecoveryTime<0)
		{
			getParent()->displayText("ZASCA!");
			mHasBeenHit=true;
			decreaseHP(pillow->getAttackDamage());
			std::stringstream msg("");
			msg<<getParentName()<<" remaining HP: "<<mHealthPoints;
			Logger::getInstance()->log(msg.str());

			mHitRecoveryTime=1;
		}		
	}
}
int LogicComponentEnemy::getMaskValueFromColour(int colour)
{
	int retVal=0;
	switch(colour)
	{
	case RED:
		retVal=COLOUR_FLAG_RED;
		break;
	case GREEN:
		retVal=COLOUR_FLAG_GREEN;
		break;
	case BLUE:
		retVal=COLOUR_FLAG_BLUE;
		break;
	default:break;		
	}
	return retVal;
}
std::string LogicComponentEnemy::getMaskString()
{
	std::string strValue="WHITE";
	if (mColourSensitivityMask&COLOUR_FLAG_RED)
		strValue.append(", RED");
	if (mColourSensitivityMask&COLOUR_FLAG_GREEN)
		strValue.append(", GREEN");
	if (mColourSensitivityMask&COLOUR_FLAG_BLUE)
		strValue.append(", BLUE");
	return strValue;
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
				mHasBeenHit=false;
				mHasDied=true;
			}
		}
		else
		{
			mHasBeenHit=false;
			mHasDied=true;
		}
	}
}

EnemyType LogicComponentEnemy::getEnemyType() const
{
	return mEnemyType;
}

int LogicComponentEnemy::getEnemyTypeLUA() const
{
	return int(mEnemyType);
}

void LogicComponentEnemy::setEnemyType(EnemyType enemyType)
{
	mEnemyType=enemyType;
}
bool LogicComponentEnemy::isFlying() const
{
	return mEnemyType==ENEMY_TYPE_FLYING;
}
int LogicComponentEnemy::getNumLives() const
{
	return 1;
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

int LogicComponentEnemy::getColourSensitivityMask() const
{
	return mColourSensitivityMask;
}

void LogicComponentEnemy::setColourSensitivityMask(int colourSensitivityMask)
{
	mColourSensitivityMask=colourSensitivityMask;
}
void LogicComponentEnemy::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
	if(mHitRecoveryTime>=0)
	{
		mHitRecoveryTime-=elapsedTime;
	}
}

bool LogicComponentEnemy::hasBeenHit() const
{
	return mHasBeenHit;
}
void LogicComponentEnemy::setHasBeenHit(bool hasBeenHit)
{
	mHasBeenHit=hasBeenHit;
}
bool LogicComponentEnemy::hasDied() const
{
	return mHasDied;
}
void LogicComponentEnemy::setHasDied(bool hasDied)
{
	mHasDied=hasDied;
}

bool LogicComponentEnemy::isAlertFinished() const
{
	return mAlertFinished;
}
void LogicComponentEnemy::setAlertFinished(bool alert)
{
	mAlertFinished=alert;
}
bool LogicComponentEnemy::isSurpriseFinished() const
{
	return mSurpriseFinished;
}
void LogicComponentEnemy::setSurpriseFinished(bool surprise)
{
	mSurpriseFinished=surprise;
}
bool LogicComponentEnemy::isFalseAlarmFinished() const
{
	return mFalseAlarmFinished;
}
void LogicComponentEnemy::setFalseAlarmFinished(bool falseAlarm)
{
	mFalseAlarmFinished=falseAlarm;
}
bool LogicComponentEnemy::isCallToArmsFinished() const
{
	return mCallToArmsFinished;
}
void LogicComponentEnemy::setCallToArmsFinished(bool callToArms)
{
	mCallToArmsFinished=callToArms;
}
bool LogicComponentEnemy::isTiredFinished() const
{
	return mTiredFinished;
}
void LogicComponentEnemy::setTiredFinished(bool tired)
{
	mTiredFinished=tired;
}
bool LogicComponentEnemy::isIdle1Finished() const
{
	return mIdle1Finished;
}
void LogicComponentEnemy::setIdle1Finished(bool idle1)
{
	mIdle1Finished=idle1;
}
bool LogicComponentEnemy::isFlashLightHitFinished() const
{
	return mFlashlightHitFinished;
}
void LogicComponentEnemy::setFlashLightHitFinished(bool flashlightHitFinished)
{
	mFlashlightHitFinished=flashlightHitFinished;
}
bool LogicComponentEnemy::isPillowHitFinished() const
{
	return mPillowHitFinished;
}
void LogicComponentEnemy::setPillowHitFinished(bool pillowHitFinished)
{
	mPillowHitFinished=pillowHitFinished;
}
int LogicComponentEnemy::getPreviousState() const
{
	return getOldState();
}

double LogicComponentEnemy::getMeleeRange() const
{
	return mParent->getMeleeRange();
}

bool LogicComponentEnemy::isAttackFinished() const
{
	return mAttackFinished;
}
void LogicComponentEnemy::setAttackFinished(bool attackFinished)
{
	mAttackFinished=attackFinished;
}

int LogicComponentEnemy::getNeighboursInRange(double range) const
{
	return mParent->getNeighboursInRange(range);
}

bool LogicComponentEnemy::callWasHeard() const
{
	return mCallWasHeard;
}
void LogicComponentEnemy::setCallWasHeard(bool callWasHeard)
{
	mCallWasHeard=callWasHeard;
}

bool LogicComponentEnemy::hasHeardCall() const
{
	return mHasHeardCall;
}

void LogicComponentEnemy::setHasHeardCall(bool hasHeardCall)
{
	mHasHeardCall=hasHeardCall;
}

bool LogicComponentEnemy::isStatueEnabled() const
{
	return mStatueEnabled;
}

void LogicComponentEnemy::setStatueEnabled(bool statueEnabled)
{
	mStatueEnabled=statueEnabled;
}

bool LogicComponentEnemy::isFlyingEnabled() const
{
	return mFlyingEnabled;
}

void LogicComponentEnemy::setFlyingEnabled(bool flyingEnabled)
{
	mFlyingEnabled=flyingEnabled;
}

void LogicComponentEnemy::setState(int state)
{
	int oldState=mState;
	mState=state;
	if (oldState!=mState)
	{
		for (int i=GAMESTATE_HISTORY_SIZE-1;i>0;--i)
		{
			stateHistory[i]=stateHistory[i-1];
		}

		stateHistory[0]=oldState;
	}

	setStateChanged(oldState!=mState);
}

bool LogicComponentEnemy::hasPatrolTrajectory() const
{
	return mParent->hasPatrolTrajectory();
}

TLogicComponentEnemyParameters::TLogicComponentEnemyParameters() : TLogicComponentParameters()
{
}

TLogicComponentEnemyParameters::~TLogicComponentEnemyParameters()
{
}
