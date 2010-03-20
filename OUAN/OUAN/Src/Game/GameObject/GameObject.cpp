#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name,const std::string& type)
{
	mName=name;
	mType=type;
}

GameObject::~GameObject()
{

}

void GameObject::destroy()
{
	
}

void GameObject::update(double elapsedSeconds)
{

}

void GameObject::changeWorld(int world)
{

}

const std::string& GameObject::getName() const
{
	return mName;
}

const std::string& GameObject::getType() const
{
	return mType;
}

GameWorldManagerPtr GameObject::getGameWorldManager()
{
	return mGameWorldManager;
}
void GameObject::setGameWorldManager(GameWorldManagerPtr gameWorldManager)
{
	mGameWorldManager=gameWorldManager;
}

void GameObject::setLogicComponentWorldExistance(LogicComponentWorldExistancePtr pLogicComponentWorldExistance)
{
	mLogicComponentWorldExistance=pLogicComponentWorldExistance;
}

LogicComponentWorldExistancePtr GameObject::getLogicComponentWorldExistance()
{
	return mLogicComponentWorldExistance;
}

void GameObject::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

//-------------------------------------------------------

TGameObjectParameters::TGameObjectParameters()
{
	this->name="";
	this->dreamsName="";
	this->nightmaresName="";
}

TGameObjectParameters::~TGameObjectParameters()
{

}

