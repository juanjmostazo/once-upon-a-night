#include "LogicComponent.h"
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
	mState=state;
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

TLogicComponentParameters::TLogicComponentParameters() : TComponentParameters()
{
}

TLogicComponentParameters::~TLogicComponentParameters()
{
}