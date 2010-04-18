#include "PhysicsComponentVolumeConvex.h"
using namespace OUAN;

PhysicsComponentVolumeConvex::PhysicsComponentVolumeConvex(const std::string& type)
:PhysicsComponentVolume(type)
{

}

PhysicsComponentVolumeConvex::~PhysicsComponentVolumeConvex()
{

}

void PhysicsComponentVolumeConvex::create()
{
	PhysicsComponentVolume::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	
	NxOgre::Convex* pConvex = new NxOgre::Convex(getNxOgreConvexMesh());

	pConvex->setName(name);

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			pConvex,
			NxOgre::Matrix44(	
			NxOgre::Vec3(Vector3::ZERO), 
			NxOgre::Quat(Quaternion::IDENTITY)),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));	
}

NxOgre::Mesh* PhysicsComponentVolumeConvex::getNxOgreConvexMesh()
{
	return mConvexMesh;
}

void PhysicsComponentVolumeConvex::setNxOgreConvexMesh(NxOgre::Mesh* pNxOgreConvexMesh)
{
	mConvexMesh=pNxOgreConvexMesh;
}

void PhysicsComponentVolumeConvex::destroy()
{
	PhysicsComponentVolume::destroy();
}

void PhysicsComponentVolumeConvex::setPosition(Vector3 position)
{
	if (isInUse())
	{
		mNxOgreVolume->setGlobalPosition(position);
	}
}

void PhysicsComponentVolumeConvex::setOrientation(Quaternion orientation)
{
	if (isInUse())
	{
		mNxOgreVolume->setGlobalOrientationQuat(orientation);
	}
}

//void PhysicsComponentVolumeConvex::setQueryFlags(QueryFlags queryFlags)
//{
//	//getNxOgreBody()->setQueryFlags((int)queryFlags);
//}

TPhysicsComponentVolumeConvexParameters::TPhysicsComponentVolumeConvexParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeConvexParameters::~TPhysicsComponentVolumeConvexParameters()
{

}

