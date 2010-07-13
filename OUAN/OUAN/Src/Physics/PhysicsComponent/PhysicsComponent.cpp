#include "OUAN_Precompiled.h"

#include "PhysicsComponent.h" 

using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& type)
:Component(type)
{
	mInUse=false;
	mStatic=false;
	mMass=0;
	mOnSurface=false;
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

void PhysicsComponent::update(double elapsedSeconds)
{
	
}

bool PhysicsComponent::isOnSurface() const
{
	return mOnSurface;
}

void PhysicsComponent::setOnSurface(bool pOnSurface)
{
	mOnSurface=pOnSurface;
}

bool PhysicsComponent::isInUse() const
{
	return mInUse;
}

void PhysicsComponent::setInUse(bool pInUse)
{
	mInUse=pInUse;
}

bool PhysicsComponent::isStatic() const
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

double PhysicsComponent::getMass() const
{
	return mMass;
}

void PhysicsComponent::setMass(double pMass)
{
	mMass=pMass;
}

void PhysicsComponent::setDisplayYaw(double displayYaw)
{

}

//void PhysicsComponent::setQueryFlags(QueryFlags queryFlags)
//{
//	
//}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{

}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{

}