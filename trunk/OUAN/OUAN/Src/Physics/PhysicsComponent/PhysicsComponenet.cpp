#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& name)
:Component(COMPONENT_NAME_PHYSICS)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::update(long elapsedTime)
{
}

Ogre::SceneNode* PhysicsComponent::getSceneNode(){
	return sceneNode;
}

void PhysicsComponent::setSceneNode(Ogre::SceneNode* sceneNode){
	this->sceneNode = sceneNode;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{
}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{
}