#include "OUAN_Precompiled.h"

#include "LogicComponentUsable.h"

using namespace OUAN;
LogicComponentUsable::LogicComponentUsable(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_USABLE)
{
	mCanBeActivated=false;
	mIsActivated=false;
}
LogicComponentUsable::~LogicComponentUsable()
{

}

void LogicComponentUsable::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
}
	//void processActivate(ActivateEventPtr evt);
	//void processAnimationEnded(AnimationEndedEventPtr evt);
	//...

void LogicComponentUsable::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
}

double LogicComponentUsable::getApproachDistance() const
{
	return mApproachDistance;
}
void LogicComponentUsable::setApproachDistance(double approachDistance)
{
	mApproachDistance=approachDistance;
}
double LogicComponentUsable::getActivateDistance() const
{
	return mActivateDistance;
}
void LogicComponentUsable::setActivateDistance(double activateDistance)
{
	mActivateDistance=activateDistance;
}
bool LogicComponentUsable::isActivated() const
{
	return mIsActivated;
}
void LogicComponentUsable::setIsActivated(bool isActivated)
{
	mIsActivated=isActivated;
}

bool LogicComponentUsable::canBeActivated() const
{
	return mCanBeActivated;
}
void LogicComponentUsable::setCanBeActivated(bool canBeActivated)
{
	mCanBeActivated=canBeActivated;
}
TLogicComponentUsableParameters::TLogicComponentUsableParameters()
{
}
TLogicComponentUsableParameters::~TLogicComponentUsableParameters()
{

}