#include "OUAN_Precompiled.h"

#include "PhysicsComponentSimple.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

PhysicsComponentSimple::PhysicsComponentSimple(const std::string& type)
:PhysicsComponent(type)
{

}

PhysicsComponentSimple::~PhysicsComponentSimple()
{

}

void PhysicsComponentSimple::create()
{
	PhysicsComponent::create();
}

void PhysicsComponentSimple::destroy()
{
	PhysicsComponent::destroy();

	if (getMass() > 0)
	{
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->destroyBody(getNxOgreBody());
		setNxOgreBody(NULL);
	}
	else
	{
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->destroyKinematicBody(getNxOgreKinematicBody());
		setNxOgreKinematicBody(NULL);
	}
}

void PhysicsComponentSimple::update(double elapsedSeconds)
{
	PhysicsComponent::update(elapsedSeconds);
	
	/***
	* setOnSurface() calculation using RayCasting
	*/
	if (getMass() > 0)
	{
		setOnSurface(false);

		Ogre::Vector3 position = getNxOgrePosition().as<Ogre::Vector3>();
		Ogre::Vector3 result(0,-10000,0);
		Ogre::uint32 collisionType;
		double distanceY = -1;

		if (Application::getInstance()->getRayCasting()->
			raycastPhysicsClosestGeometry(
				position,
				Ogre::Vector3(0, -1, 0),
				result,
				collisionType,
				50))
		{
			distanceY = fabs(position.y - result.y);
			setOnSurface(distanceY > 0 && distanceY < mHeight);
		}

		//Logger::getInstance()->log("##########");
		//Logger::getInstance()->log("PCS::" + getParent()->getName() + "::" + Ogre::StringConverter::toString(isOnSurface()) + ", " + Ogre::StringConverter::toString(Ogre::Real(distanceY)) + " :: " + Ogre::StringConverter::toString(Ogre::Real(mHeight)));
		//Logger::getInstance()->log("PCS::" + getParent()->getName() + "::" + Ogre::StringConverter::toString(Ogre::Real(position.x)) + " " + Ogre::StringConverter::toString(Ogre::Real(position.y)) + " " + Ogre::StringConverter::toString(Ogre::Real(position.z)));
		//Logger::getInstance()->log("PCS::" + getParent()->getName() + "::" + Ogre::StringConverter::toString(Ogre::Real(result.x)) + " " + Ogre::StringConverter::toString(Ogre::Real(result.y)) + " " + Ogre::StringConverter::toString(Ogre::Real(result.z)));
		//Logger::getInstance()->log("##########");
	}
}
	
OGRE3DBody* PhysicsComponentSimple::getNxOgreBody()
{
	return mNxOgreBody;
}

void PhysicsComponentSimple::setNxOgreBody(OGRE3DBody* pNxOgreBody)
{
	mNxOgreBody=pNxOgreBody;
}

OGRE3DKinematicBody* PhysicsComponentSimple::getNxOgreKinematicBody()
{
	return mNxOgreKinematicBody;
}

void PhysicsComponentSimple::setNxOgreKinematicBody(OGRE3DKinematicBody* pNxOgreKinematicBody)
{
	mNxOgreKinematicBody=pNxOgreKinematicBody;
}

NxOgre::Vec3 PhysicsComponentSimple::getNxOgrePosition()
{
	if (getMass() > 0)
	{
		return mNxOgreBody->getGlobalPosition();
	}
	else
	{
		return mNxOgreKinematicBody->getGlobalPosition();
	}
}

TPhysicsComponentSimpleParameters::TPhysicsComponentSimpleParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentSimpleParameters::~TPhysicsComponentSimpleParameters()
{

}