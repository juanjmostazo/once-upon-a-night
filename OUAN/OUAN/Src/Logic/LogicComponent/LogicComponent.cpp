#include "LogicComponent.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"


using namespace OUAN;

LogicComponent::LogicComponent(const std::string& type)
:Component(COMPONENT_TYPE_LOGIC)
{
//	mPatrolTrajectory.reset();
	mStateChanged=false;
}

LogicComponent::~LogicComponent()
{
}

void LogicComponent::update(long elapsedTime)
{
	if (!mScriptFunction.empty())
	{
		mStateChanged=false;
		LogicSubsystemPtr logicSS= mParent->getGameWorldManager()->getParent()->getLogicSubsystem();
		int newState=logicSS->invokeFunction(mScriptFunction,mState,mParent);
		if (newState!=mState)
		{
			setState(newState);
			mStateChanged=true;
		}
	}
}
void LogicComponent::initStateHistory()
{
	for (int i=0;i<GAMESTATE_HISTORY_SIZE;++i)
	{
		stateHistory[i]=-1;
	}
}

bool LogicComponent::existsInDreams() const
{
	return mExistsInDreams;
}
void LogicComponent::setExistsInDreams(bool existsInDreams)
{
	mExistsInDreams=existsInDreams;
}

bool LogicComponent::existsInNightmares() const
{
	return mExistsInNightmares;
}
void LogicComponent::setExistsInNightmares(bool existsInNightmares)
{
	mExistsInNightmares=existsInNightmares;
}

int LogicComponent::getState() const
{
	return mState;
}
int LogicComponent::getOldState(int index) const
{
	if (index>=0 && index<GAMESTATE_HISTORY_SIZE)
	{
		return stateHistory[index];
	}
	return -1;
}
void LogicComponent::setState(int state)
{
	int oldState=mState;
	mState=state;
	for (int i=GAMESTATE_HISTORY_SIZE-1;i>0;--i)
	{
		stateHistory[i]=stateHistory[i-1];
	}
	stateHistory[0]=oldState;
	
}

int LogicComponent::getHealthPoints() const
{
	return mHealthPoints;
}
void LogicComponent::setHealthPoints(int healthPoints)
{
	mHealthPoints=healthPoints;
}

int LogicComponent::getNumLives() const
{
	return mNumLives;
}
void LogicComponent::setNumLives(int numLives)
{
	mNumLives=numLives;
}

std::string LogicComponent::getScriptFilename() const
{
	return mScriptFilename;
}
void LogicComponent::setScriptFilename(const std::string& scriptFilename)
{
	mScriptFilename=scriptFilename;
}
std::string LogicComponent::getScriptFunction() const
{
	return mScriptFunction;
}
void LogicComponent::setScriptFunction(const std::string& scriptFunction)
{
	mScriptFunction=scriptFunction;
}
int LogicComponent::getInitialHealthPoints() const
{
	return mInitialHealthPoints;
}
void LogicComponent::setInitialHealthPoints(int healthPoints)
{
	mInitialHealthPoints=healthPoints;
}

int LogicComponent::getInitialNumLives() const
{
	return mInitialNumLives;
}
void LogicComponent::setInitialNumLives(int numLives)
{
	mInitialNumLives=numLives;
}
int LogicComponent::getLineOfSight() const
{
	return mLineOfSight;
}
void LogicComponent::setLineOfSight(int lineOfSight)
{
	mLineOfSight=lineOfSight;
}

bool LogicComponent::isStateChanged() const
{
	return mStateChanged;
}

void LogicComponent::setStateChanged(bool stateChanged)
{
	mStateChanged=stateChanged;
}

int LogicComponent::getAttackRange() const
{
	return mAttackRange;
}
void LogicComponent::setAttackRange(int attackRange)
{
	mAttackRange=attackRange;
}

int LogicComponent::getAttackDamage() const
{
	return mAttackDamage;
}

void LogicComponent::setAttackDamage(int attackDamage)
{
	mAttackDamage=attackDamage;
}

int LogicComponent::getAttackDelay() const
{
	return mAttackDelay;
}

void LogicComponent::setAttackDelay(int attackDelay)
{
	mAttackDelay=attackDelay;
}

int LogicComponent::getColourSensitivityMask() const
{
	return mColourSensitivityMask;
}

void LogicComponent::setColourSensitivityMask(int colourSensitivityMask)
{
	mColourSensitivityMask=colourSensitivityMask;
}

TLogicComponentParameters::TLogicComponentParameters() : TComponentParameters()
{
}

TLogicComponentParameters::~TLogicComponentParameters()
{
}
