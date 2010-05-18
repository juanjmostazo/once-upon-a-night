#include "PhysicsComponentSimple.h"
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