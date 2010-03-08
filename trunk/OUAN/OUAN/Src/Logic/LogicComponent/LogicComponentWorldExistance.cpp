#include "LogicComponentWorldExistance.h"
using namespace OUAN;

LogicComponentWorldExistance::LogicComponentWorldExistance(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_WORLD_EXISTANCE)
{
}
LogicComponentWorldExistance::~LogicComponentWorldExistance()
{
	existsInDreams=true;
	existsInNightmares=true;
}

bool LogicComponentWorldExistance::getExistsInDreams() const
{
	return existsInDreams;
}

void LogicComponentWorldExistance::setExistsInDreams(bool existsInDreams)
{
	this->existsInDreams=existsInDreams;
}

bool LogicComponentWorldExistance::getExistsInNightmares() const
{
	return existsInNightmares;
}

void LogicComponentWorldExistance::setExistsInNightmares(bool existsInNightmares)
{
	this->existsInNightmares=existsInNightmares;
}

TLogicComponentWorldExistanceParameters::TLogicComponentWorldExistanceParameters() : TLogicComponentParameters()
{
}
TLogicComponentWorldExistanceParameters::~TLogicComponentWorldExistanceParameters()
{
}
