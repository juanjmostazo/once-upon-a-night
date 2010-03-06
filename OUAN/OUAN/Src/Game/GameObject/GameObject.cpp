#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name)
:mName(name)
{

}

GameObject::~GameObject()
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

void GameObject::registerHandlers()
{
}
void GameObject::unregisterHandlers()
{
}
GameWorldManagerPtr GameObject::getGameWorldManager()
{
	return mGameWorldManager;
}
void GameObject::setGameWorldManager(GameWorldManagerPtr gameWorldManager)
{
	mGameWorldManager=gameWorldManager;
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

