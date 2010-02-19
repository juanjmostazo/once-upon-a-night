#include "RenderComponent.h"
using namespace OUAN;

RenderComponent::RenderComponent(const std::string& name)
:Component(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponent::~RenderComponent()
{
}


void RenderComponent::update(long elapsedTime)
{
}