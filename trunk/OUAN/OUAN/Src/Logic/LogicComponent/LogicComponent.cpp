#include "LogicComponent.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"


using namespace OUAN;

LogicComponent::LogicComponent(const std::string& type)
:Component(COMPONENT_TYPE_LOGIC)
{
}

LogicComponent::~LogicComponent()
{
}

void LogicComponent::update(long elapsedTime)
{
	if (!mScriptFunction.empty())
	{
		LogicSubsystemPtr logicSS= mParent->getGameWorldManager()->getParent()->getLogicSubsystem();
		int newState=logicSS->invokeFunction(mScriptFunction,mState,mParent);
		setState(newState);
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
TLogicComponentParameters::TLogicComponentParameters() : TComponentParameters()
{
}

TLogicComponentParameters::~TLogicComponentParameters()
{
}
