#include "PhysicsComponentComplexTriangle.h"
using namespace OUAN;

PhysicsComponentComplexTriangle::PhysicsComponentComplexTriangle(const std::string& type)
:PhysicsComponentComplex(COMPONENT_TYPE_PHYSICS_COMPLEX_NON_MOVABLE)
{

}

PhysicsComponentComplexTriangle::~PhysicsComponentComplexTriangle()
{

}

void PhysicsComponentComplexTriangle::create()
{
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createSceneGeometry(
		getNxOgreTriangleGeometry(),
		NxOgre::Matrix44(NxOgre::Vec3(getSceneNode()->getPosition())));
}

void PhysicsComponentComplexTriangle::destroy()
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