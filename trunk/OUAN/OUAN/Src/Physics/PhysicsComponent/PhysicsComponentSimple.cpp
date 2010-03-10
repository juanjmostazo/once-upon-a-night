#include "PhysicsComponentSimple.h"
using namespace OUAN;

PhysicsComponentSimple::PhysicsComponentSimple(const std::string& type)
:PhysicsComponent(COMPONENT_TYPE_PHYSICS_SIMPLE)
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

TPhysicsComponentSimpleParameters::TPhysicsComponentSimpleParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentSimpleParameters::~TPhysicsComponentSimpleParameters()
{

}