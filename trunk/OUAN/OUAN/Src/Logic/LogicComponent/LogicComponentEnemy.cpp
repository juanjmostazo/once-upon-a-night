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

TLogicComponentEnemyParameters::TLogicComponentEnemyParameters() : TLogicComponentParameters()
{
}

TLogicComponentEnemyParameters::~TLogicComponentEnemyParameters()
{
}
