#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& type)
:Component(COMPONENT_TYPE_PHYSICS)
{
	mInUse=false;
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

Ogre::SceneNode* PhysicsComponent::getSceneNode(){
	return mSceneNode;
}

void PhysicsComponent::setSceneNode(Ogre::SceneNode* pSceneNode){
	mSceneNode = pSceneNode;
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}