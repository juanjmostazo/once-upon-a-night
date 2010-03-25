#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name,const std::string& type)
{
	mName=name;
	mType=type;
	mEnabled=true;
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

void GameObject::disable()
{
	Ogre::LogManager::getSingleton().logMessage("Disabling Game Object '" + mName + "'");
	mEnabled = false;
}

bool GameObject::isEnabled()
{
	return mEnabled;
}

GameWorldManagerPtr GameObject::getGameWorldManager()
{
	return mGameWorldManager;
}
void GameObject::setGameWorldManager(GameWorldManagerPtr gameWorldManager)
{
	mGameWorldManager=gameWorldManager;
}

/// Set logic component
void GameObject::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObject::getLogicComponent()
{
	return mLogicComponent;
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

