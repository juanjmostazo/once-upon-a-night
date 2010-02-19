#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name, const std::string& id)
:mName(name)
,mId(id)
{
	mComponents.clear();
}

GameObject::~GameObject()
{
	mComponents.clear();
}
void GameObject::onUpdate(long elapsedTime)
{
}

void GameObject::addComponent(const std::string& name, ComponentPtr component)
{
	mComponents[name]=component;
}

bool GameObject::hasComponent(const std::string& name)
{
	return (!mComponents.empty()&& mComponents.count(name)>0);
}

ComponentPtr GameObject::getComponent(const std::string& name)
{
	if (hasComponent(name))
	{
		return mComponents[name];
	}
	return ComponentPtr();
}

const std::string& GameObject::getName() const
{
	return mName;
}
/// Return the concrete instance's unique identifier
/// @return id of the entity
const std::string& GameObject::getId() const
{
	return mId;
}
