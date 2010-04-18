#include "Component.h"
#include "../Game/GameObject/GameObject.h"
using namespace OUAN;
Component::Component(const std::string& type)
:mType(type)
{
	mParent.reset();
}

Component::~Component()
{}


const std::string& Component::getType() const
{
	return mType;
}

/// set the type of the component
/// @param type type of the component
void Component::setType(const std::string& type)
{
	mType=type;
}

/// set the component's parent GameObject
/// @param parent the parent GameObject
void Component::setParent(GameObjectPtr parent)
{
	mParent=parent;
}
GameObjectPtr Component::getParent()
{
	return mParent;
}

const std::string& Component::getParentName()
{
	return mParent->getName();
}

void Component::update(double elapsedSeconds)
{
}

TComponentParameters::TComponentParameters()
{
}
TComponentParameters::~TComponentParameters()
{
}
