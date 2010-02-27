#include "LogicComponentEvent.h"
using namespace OUAN;

LogicComponentEvent::LogicComponentEvent(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_EVENT)
{
}
LogicComponentEvent::~LogicComponentEvent()
{
	mEvent="";
}

std::string LogicComponentEvent::getEventType() const
{
	return mEvent;
}
void LogicComponentEvent::setEventType(std::string eventtype)
{
	mEvent=eventtype;
}

TLogicComponentEventParameters::TLogicComponentEventParameters() : TLogicComponentParameters()
{
}
TLogicComponentEventParameters::~TLogicComponentEventParameters()
{
}
