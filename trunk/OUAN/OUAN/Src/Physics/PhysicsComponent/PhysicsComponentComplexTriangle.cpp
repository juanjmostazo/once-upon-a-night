#include "OUAN_Precompiled.h"

#include "PhysicsComponentComplexTriangle.h"
using namespace OUAN;

PhysicsComponentComplexTriangle::PhysicsComponentComplexTriangle(const std::string& type)
:PhysicsComponentComplex(type)
{

}

PhysicsComponentComplexTriangle::~PhysicsComponentComplexTriangle()
{

}

void PhysicsComponentComplexTriangle::create()
{
	PhysicsComponentComplex::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());

	NxOgre::TriangleGeometry * pTriangleGeometry = getNxOgreTriangleGeometry();

	pTriangleGeometry->setName(name);

	Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createSceneGeometry(
		pTriangleGeometry,
		NxOgre::Matrix44(
			NxOgre::Vec3(getSceneNode()->getPosition()), 
			NxOgre::Quat(getSceneNode()->getOrientation())));

	setStatic(true);
}

void PhysicsComponentComplexTriangle::destroy()
{
	PhysicsComponentComplex::destroy();

	// This object can not be destroyed
	mInUse=true; 
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