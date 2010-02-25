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

const std::string& GameObject::getName() const
{
	return mName;
}

TGameObjectParameters::TGameObjectParameters()
{
}
TGameObjectParameters::~TGameObjectParameters()
{
}