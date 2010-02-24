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

double PhysicsComponent::getMass()
{
	return mNxOgreMass;
}

void PhysicsComponent::setMass(double pNxOgreMass)
{
	mNxOgreMass=pNxOgreMass;
}

double PhysicsComponent::getDensity()
{
	return mNxOgreDensity;
}

void PhysicsComponent::setDensity(double pNxOgreDensity)
{
	mNxOgreDensity=pNxOgreDensity;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}