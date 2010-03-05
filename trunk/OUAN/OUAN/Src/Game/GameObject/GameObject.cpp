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

void GameObject::setDreamsMode()
{

}

void GameObject::setNightmaresMode()
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

