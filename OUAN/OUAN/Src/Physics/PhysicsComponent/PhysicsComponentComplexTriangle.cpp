#include "PhysicsComponentComplexTriangle.h"
using namespace OUAN;

PhysicsComponentComplexTriangle::PhysicsComponentComplexTriangle(const std::string& name)
:PhysicsComponentComplex(COMPONENT_NAME_PHYSICS_COMPLEX_NON_MOVABLE)
{
}

PhysicsComponentComplexTriangle::~PhysicsComponentComplexTriangle()
{
}

NxOgre::TriangleGeometry* PhysicsComponentComplexTriangle::getNxOgreTriangleGeometry()
{
	return mNxOgreTriangleGeometry;
}

void PhysicsComponentComplexTriangle::setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleGeometry)
{
	mNxOgreTriangleGeometry = pNxOgreTriangleGeometry;
}

TPhysicsComponentComplexTriangleParameters::TPhysicsComponentComplexTriangleParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexTriangleParameters::~TPhysicsComponentComplexTriangleParameters()
{
}