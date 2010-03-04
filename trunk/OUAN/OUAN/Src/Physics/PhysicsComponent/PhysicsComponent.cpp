#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& type)
:Component(COMPONENT_TYPE_PHYSICS)
{

}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::create()
{

}

void PhysicsComponent::destroy()
{

}

void PhysicsComponent::update(long elapsedTime)
{

}

Ogre::SceneNode* PhysicsComponent::getSceneNode(){
	return mSceneNode;
}

void PhysicsComponent::setSceneNode(Ogre::SceneNode* pSceneNode){
	mSceneNode = pSceneNode;
}

double PhysicsComponent::getMass()
{
	return mNxOgreMass;
}

void PhysicsComponent::setMass(double pNxOgreMass)
{
	mNxOgreMass=pNxOgreMass;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}