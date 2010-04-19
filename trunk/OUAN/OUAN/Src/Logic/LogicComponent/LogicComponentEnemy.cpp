#include "LogicComponentEnemy.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"

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
		GameObjectFlashLightPtr flashlight=boost::dynamic_pointer_cast<GameObjectFlashLight>(pGameObject);
		int flashlightColour=flashlight->getColour();
		std::string msg="Flashlight collision - Current colour: ";
		msg.append(getColourName(flashlightColour));
		msg.append("; This enemy will react to ");
		msg.append(getMaskString());
		Ogre::LogManager::getSingletonPtr()->logMessage(msg);
		if (getMaskValueFromColour(flashlightColour) & mColourSensitivityMask && mHitRecoveryTime<0)
		{
			decreaseHP();
			mHitRecoveryTime=1000;
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
std::string LogicComponentEnemy::getColourName(int colour)
{
	switch(colour)
	{
		case RED:
			return "RED";
		case GREEN:
			return "GREEN";
		case BLUE:
			return "BLUE";
		case WHITE:
			return "WHITE";
		default:
			return "";
	}
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
				//TODO: Create an "enemy died" event
					std::string msg="Enemy ";
					msg.append(getParent()->getName()).append(" died");
					Ogre::LogManager::getSingletonPtr()->logMessage(msg);
				getParent()->disable();
				//decreaseLives();				
			}
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
		mHitRecoveryTime-=elapsedTime*1000;
	}
}

TLogicComponentEnemyParameters::TLogicComponentEnemyParameters() : TLogicComponentParameters()
{
}

TLogicComponentEnemyParameters::~TLogicComponentEnemyParameters()
{
}
