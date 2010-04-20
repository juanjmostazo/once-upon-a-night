#include "LogicComponentPortal.h"

using namespace OUAN;
LogicComponentPortal::LogicComponentPortal(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_PORTAL)
{
}
LogicComponentPortal::~LogicComponentPortal()
{

}

void LogicComponentPortal::processCollision(GameObjectPtr pGameObject)
{
}
	//void processActivate(ActivateEventPtr evt);
	//void processAnimationEnded(AnimationEndedEventPtr evt);
	//...

void LogicComponentPortal::update(double elapsedTime)
{

}

double LogicComponentPortal::getApproachDistance() const
{
	return mApproachDistance;
}
void LogicComponentPortal::setApproachDistance(double approachDistance)
{
	mApproachDistance=approachDistance;
}
double LogicComponentPortal::getActivateDistance() const
{
	return mActivateDistance;
}
void LogicComponentPortal::setActivateDistance(double activateDistance)
{
	mActivateDistance=activateDistance;
}
TLogicComponentPortalParameters::TLogicComponentPortalParameters()
{
}
TLogicComponentPortalParameters::~TLogicComponentPortalParameters()
{

}