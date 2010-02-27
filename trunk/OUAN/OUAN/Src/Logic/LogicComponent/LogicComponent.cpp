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

TLogicComponentParameters::TLogicComponentParameters() : TComponentParameters()
{
}

TLogicComponentParameters::~TLogicComponentParameters()
{
}