#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name)
:mName(name)
{

}

GameObject::~GameObject()
{

}
void GameObject::update(long elapsedTime)
{
}

void GameObject::setToDreams()
{
	
}
void GameObject::setToNightmares()
{

}

const std::string& GameObject::getName() const
{
	return mName;
}

TGameObjectParameters::TGameObjectParameters()
{
	this->name="";
	this->dreamsName="";
	this->nightmaresName="";
}
TGameObjectParameters::~TGameObjectParameters()
{
}

