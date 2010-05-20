#include "LogicComponentProp.h"

using namespace OUAN;
LogicComponentProp::LogicComponentProp(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_PROP)
,mTimeSpent(0)
{
}
LogicComponentProp::~LogicComponentProp()
{

}

void LogicComponentProp::processCollision(GameObjectPtr pGameObject)
{
}
//void processActivate(ActivateEventPtr evt);
//void processAnimationEnded(AnimationEndedEventPtr evt);
//...

void LogicComponentProp::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
	if (mTimeSpent<mDelay)
		mTimeSpent+=elapsedTime;
}

double LogicComponentProp::getApproachDistance() const
{
	return mApproachDistance;
}
void LogicComponentProp::setApproachDistance(double approachDistance)
{
	mApproachDistance=approachDistance;
}
double LogicComponentProp::getTimeSpent() const
{
	return mTimeSpent;
}
void LogicComponentProp::setTimeSpent(double timeSpent)
{
	mTimeSpent=timeSpent;
}
double LogicComponentProp::getDelay() const
{
	return mDelay;
}
void LogicComponentProp::setDelay(double delay)
{
	mDelay=delay;
}
TLogicComponentPropParameters::TLogicComponentPropParameters()
{
}
TLogicComponentPropParameters::~TLogicComponentPropParameters()
{

}