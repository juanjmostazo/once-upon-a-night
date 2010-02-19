#include "GameObject.h"

using namespace OUAN;

GameObject::GameObject(const std::string& name, const std::string& id)
:mName(name)
,mId(id)
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

/// Return the concrete instance's unique identifier
/// @return id of the entity
const std::string& GameObject::getId() const
{
	return mId;
}
