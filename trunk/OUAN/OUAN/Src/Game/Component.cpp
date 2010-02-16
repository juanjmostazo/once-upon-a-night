#include "Component.h"
using namespace OUAN;
Component::Component(const std::string& name,const std::string& family)
:mName(name)
{
	mFamily=family.empty()?name:family;
	mParent.reset();
}

Component::~Component()
{}


const std::string& Component::getName() const
{
	return mName;
}

/// set the name of the component
/// @param name name of the component
void Component::setName(const std::string& name)
{
	mName=name;
}

/// set the component's parent GameObject
/// @param parent the parent GameObject
void Component::setParent(GameObjectPtr parent)
{
	mParent=parent;
}