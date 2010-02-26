#include "PhysicsComponentSimple.h"
using namespace OUAN;

PhysicsComponentSimple::PhysicsComponentSimple(const std::string& type)
:PhysicsComponent(COMPONENT_TYPE_PHYSICS_SIMPLE)
{

}

PhysicsComponentSimple::~PhysicsComponentSimple()
{

}

OGRE3DBody* PhysicsComponentSimple::getNxOgreBody()
{
	return mNxOgreBody;
}

void PhysicsComponentSimple::setNxOgreBody(OGRE3DBody* pNxOgreBody)
{
	mNxOgreBody=pNxOgreBody;
}

TPhysicsComponentSimpleParameters::TPhysicsComponentSimpleParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentSimpleParameters::~TPhysicsComponentSimpleParameters()
{

}