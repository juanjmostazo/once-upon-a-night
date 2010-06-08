#include "OUAN_Precompiled.h"

#include "WorldNameConverter.h"
using namespace OUAN;

WorldNameConverter::WorldNameConverter()
{

}

WorldNameConverter::~WorldNameConverter()
{

}

std::string WorldNameConverter::getBaseName(std::string name)
{
	if(name.substr(name.size()-SUFFIX_DREAMS.size(),SUFFIX_DREAMS.size()).compare(SUFFIX_DREAMS)==0)
	{
		return name.substr(0,name.size()-SUFFIX_DREAMS.size());
	}
	else if(name.substr(name.size()-SUFFIX_NIGHTMARES.size(),SUFFIX_NIGHTMARES.size()).compare(SUFFIX_NIGHTMARES)==0)
	{
		return name.substr(0,name.size()-SUFFIX_NIGHTMARES.size());
	}
	else if(name.substr(name.size()-SUFFIX_CHANGEWORLD.size(),SUFFIX_CHANGEWORLD.size()).compare(SUFFIX_CHANGEWORLD)==0)
	{
		return name.substr(0,name.size()-SUFFIX_CHANGEWORLD.size());
	}
	return name;
}

std::string WorldNameConverter::getDreamsName(std::string name)
{
	return WorldNameConverter::getBaseName(name)+SUFFIX_DREAMS;
}

std::string WorldNameConverter::getNightmaresName(std::string name)
{
	return WorldNameConverter::getBaseName(name)+SUFFIX_NIGHTMARES;
}

std::string WorldNameConverter::getChangeWorldName(std::string name)
{
	return WorldNameConverter::getBaseName(name)+SUFFIX_CHANGEWORLD;
}