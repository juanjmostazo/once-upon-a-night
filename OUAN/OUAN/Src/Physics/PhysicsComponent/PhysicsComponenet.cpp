#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& name)
:Component(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::update(long elapsedTime)
{
}

NxOgre::Mesh* PhysicsComponent::getMesh(){
	return mesh;
}

void PhysicsComponent::setMesh(NxOgre::Mesh* mesh){
	this->mesh = mesh;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{
}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{
}