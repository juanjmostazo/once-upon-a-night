#include "OUAN_Precompiled.h"

#include "PhysicsComponentVolumeTriangle.h"
using namespace OUAN;

PhysicsComponentVolumeTriangle::PhysicsComponentVolumeTriangle(const std::string& type)
:PhysicsComponentVolume(type)
{

}

PhysicsComponentVolumeTriangle::~PhysicsComponentVolumeTriangle()
{

}

void PhysicsComponentVolumeTriangle::create()
{
	PhysicsComponentVolume::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	
	NxOgre::TriangleGeometry * pTriangle = getNxOgreTriangleGeometry();

	pTriangle->setName(name);

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			pTriangle,
			NxOgre::Matrix44(	
			NxOgre::Vec3(getSceneNode()->getPosition()), 
			NxOgre::Quat(getSceneNode()->getOrientation())),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));

	setStatic(true);
}

NxOgre::TriangleGeometry* PhysicsComponentVolumeTriangle::getNxOgreTriangleGeometry()
{
	return mTriangleMesh;
}

void PhysicsComponentVolumeTriangle::setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleMesh)
{
	mTriangleMesh=pNxOgreTriangleMesh;
}

void PhysicsComponentVolumeTriangle::destroy()
{
	PhysicsComponent::destroy();

	// This object can not be destroyed
	mInUse=true; 
}

void PhysicsComponentVolumeTriangle::setPosition(Vector3 position)
{
	if (isInUse())
	{
		mNxOgreVolume->setGlobalPosition(position);
	}
}

void PhysicsComponentVolumeTriangle::setOrientation(Quaternion orientation)
{
	if (isInUse())
	{
		mNxOgreVolume->setGlobalOrientationQuat(orientation);
	}
}

//void PhysicsComponentVolumeTriangle::setQueryFlags(QueryFlags queryFlags)
//{
//	//getNxOgreBody()->setQueryFlags((int)queryFlags);
//}

TPhysicsComponentVolumeTriangleParameters::TPhysicsComponentVolumeTriangleParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeTriangleParameters::~TPhysicsComponentVolumeTriangleParameters()
{

}

