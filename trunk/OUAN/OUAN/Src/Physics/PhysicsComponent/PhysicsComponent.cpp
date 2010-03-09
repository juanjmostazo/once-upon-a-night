#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& type)
:Component(COMPONENT_TYPE_PHYSICS)
{
	mInUse=false;
	mStatic=false;
	mMass=0;
}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::create()
{
	mInUse=true;
}

void PhysicsComponent::destroy()
{
	mInUse=false;
}

void PhysicsComponent::update(long elapsedTime)
{

}

bool PhysicsComponent::isInUse()
{
	return mInUse;
}

void PhysicsComponent::setInUse(bool pInUse)
{
	mInUse=pInUse;
}

bool PhysicsComponent::isStatic()
{
	return mStatic;
}

void PhysicsComponent::setStatic(bool pStatic)
{
	mStatic=pStatic;
}

Ogre::SceneNode* PhysicsComponent::getSceneNode(){
	return mSceneNode;
}

void PhysicsComponent::setSceneNode(Ogre::SceneNode* pSceneNode){
	mSceneNode = pSceneNode;
}

double PhysicsComponent::getMass()
{
	return mMass;
}

void PhysicsComponent::setMass(double pMass)
{
	mMass=pMass;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}