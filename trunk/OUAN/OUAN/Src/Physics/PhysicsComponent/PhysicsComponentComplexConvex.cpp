#include "PhysicsComponentComplexConvex.h"
using namespace OUAN;

PhysicsComponentComplexConvex::PhysicsComponentComplexConvex(const std::string& type)
:PhysicsComponentComplex(type)
{

}

PhysicsComponentComplexConvex::~PhysicsComponentComplexConvex()
{

}

void PhysicsComponentComplexConvex::create()
{
	PhysicsComponentComplex::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	NxOgre::Convex * pConvex = getNxOgreConvex();

	pConvex->setName(name);

	
	if (getMass() > 0)
	{
		setNxOgreKinematicBody(NULL);

		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();
		pDesc.mName = name;

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				pConvex,
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		getNxOgreBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));


	}
	else
	{
		getNxOgreConvex()->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
		setStatic(true);
		setNxOgreBody(NULL);

		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
			pConvex,
			getSceneNode()->getPosition(),
			getSceneNode()));

		getNxOgreKinematicBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));
	}
}

void PhysicsComponentComplexConvex::destroy()
{
	PhysicsComponentComplex::destroy();

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

OGRE3DKinematicBody* PhysicsComponentComplexConvex::getNxOgreKinematicBody()
{
	return mNxOgreKinematicBody;
}

void PhysicsComponentComplexConvex::setNxOgreKinematicBody(OGRE3DKinematicBody* pNxOgreKinematicBody)
{
	mNxOgreKinematicBody=pNxOgreKinematicBody;
}

TPhysicsComponentComplexConvexParameters::TPhysicsComponentComplexConvexParameters() : TPhysicsComponentComplexParameters()
{

}

TPhysicsComponentComplexConvexParameters::~TPhysicsComponentComplexConvexParameters()
{

}