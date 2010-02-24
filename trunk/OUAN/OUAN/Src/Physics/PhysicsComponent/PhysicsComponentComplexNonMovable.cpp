#include "PhysicsComponentComplexNonMovable.h"
using namespace OUAN;

PhysicsComponentComplexNonMovable::PhysicsComponentComplexNonMovable(const std::string& name)
:PhysicsComponentComplex(COMPONENT_NAME_PHYSICS_COMPLEX_NON_MOVABLE)
{
}

PhysicsComponentComplexNonMovable::~PhysicsComponentComplexNonMovable()
{
}

NxOgre::TriangleGeometry* PhysicsComponentComplexNonMovable::getNxOgreTriangleGeometry()
{
	return mNxOgreTriangleGeometry;
}

void PhysicsComponentComplexNonMovable::setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleGeometry)
{
	mNxOgreTriangleGeometry = pNxOgreTriangleGeometry;
}

TPhysicsComponentComplexNonMovableParameters::TPhysicsComponentComplexNonMovableParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexNonMovableParameters::~TPhysicsComponentComplexNonMovableParameters()
{
}