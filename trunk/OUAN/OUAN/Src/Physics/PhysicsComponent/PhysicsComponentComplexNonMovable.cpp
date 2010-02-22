#include "PhysicsComponentComplexNonMovable.h"
using namespace OUAN;

PhysicsComponentComplexNonMovable::PhysicsComponentComplexNonMovable(const std::string& name)
:PhysicsComponentComplex(COMPONENT_NAME_PHYSICS_COMPLEX_NON_MOVABLE)
{
}

PhysicsComponentComplexNonMovable::~PhysicsComponentComplexNonMovable()
{
}

NxOgre::TriangleGeometry* PhysicsComponentComplexNonMovable::getTriangleGeometry()
{
	return triangleGeometry;
}

void PhysicsComponentComplexNonMovable::setTriangleGeometry(NxOgre::TriangleGeometry* triangleGeometry)
{
	this->triangleGeometry = triangleGeometry;
}

TPhysicsComponentComplexNonMovableParameters::TPhysicsComponentComplexNonMovableParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexNonMovableParameters::~TPhysicsComponentComplexNonMovableParameters()
{
}