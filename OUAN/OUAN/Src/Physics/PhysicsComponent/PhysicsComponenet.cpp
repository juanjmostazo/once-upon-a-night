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
	return mSceneNode;
}

void PhysicsComponent::setSceneNode(Ogre::SceneNode* pSceneNode){
	mSceneNode = pSceneNode;
}

float PhysicsComponent::getMass()
{
	return mNxOgreMass;
}

void PhysicsComponent::setMass(float pNxOgreMass)
{
	mNxOgreMass=pNxOgreMass;
}

float PhysicsComponent::getDensity()
{
	return mNxOgreDensity;
}

void PhysicsComponent::setDensity(float pNxOgreDensity)
{
	mNxOgreDensity=pNxOgreDensity;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}