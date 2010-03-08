#include "PhysicsComponentComplexConvex.h"
using namespace OUAN;

PhysicsComponentComplexConvex::PhysicsComponentComplexConvex(const std::string& type)
:PhysicsComponentComplex(COMPONENT_TYPE_PHYSICS_COMPLEX_MOVABLE)
{

}

PhysicsComponentComplexConvex::~PhysicsComponentComplexConvex()
{

}

void PhysicsComponentComplexConvex::create()
{
	PhysicsComponentComplex::create();
	
	if (getNxOgreRigidBodyDescription().mMass > 0)
	{
		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				getNxOgreConvex(),
				getSceneNode()->getPosition(),
				getSceneNode(),
				getNxOgreRigidBodyDescription()));
	}
	else
	{
		setNxOgreBody(NULL);

		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createSceneGeometry(
			getNxOgreConvex(),
			NxOgre::Matrix44(NxOgre::Vec3(getSceneNode()->getPosition())));

		setStatic(true);
	}
}

void PhysicsComponentComplexConvex::destroy()
{
	PhysicsComponentComplex::destroy();

	if (getNxOgreRigidBodyDescription().mMass > 0)
	{
		NxOgre::RigidBodyDescription tmpDesc = getNxOgreRigidBodyDescription();
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->destroyBody(getNxOgreBody());
		
		setNxOgreBody(NULL);
		setNxOgreRigidBodyDescription(tmpDesc);
	}
	else
	{
		//TODO: STATIC SCENE GEOMETRY CANNOT BE DELETED
		mInUse=true;
	}
}

NxOgre::Convex* PhysicsComponentComplexConvex::getNxOgreConvex()
{
	return mNxOgreConvex;
}

void PhysicsComponentComplexConvex::setNxOgreConvex(NxOgre::Convex* pNxOgreConvex)
{
	mNxOgreConvex=pNxOgreConvex;
}

OGRE3DBody* PhysicsComponentComplexConvex::getNxOgreBody()
{
	return mNxOgreBody;
}

void PhysicsComponentComplexConvex::setNxOgreBody(OGRE3DBody* pNxOgreBody)
{
	mNxOgreBody=pNxOgreBody;
}

NxOgre::RigidBodyDescription PhysicsComponentComplexConvex::getNxOgreRigidBodyDescription()
{
	return mNxOgreRigidBodyDescription;
}

void PhysicsComponentComplexConvex::setNxOgreRigidBodyDescription(NxOgre::RigidBodyDescription pNxOgreRigidBodyDescription)
{
	mNxOgreRigidBodyDescription=pNxOgreRigidBodyDescription;
}

TPhysicsComponentComplexConvexParameters::TPhysicsComponentComplexConvexParameters() : TPhysicsComponentComplexParameters()
{

}

TPhysicsComponentComplexConvexParameters::~TPhysicsComponentComplexConvexParameters()
{

}