
#include "OUAN_Precompiled.h"

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

	//mBalanceLastWasPositive = Ogre::Vector3(0,0,0);
	//mBalanceLastWasCenter = Ogre::Vector3(1,1,1);
	//mBalanceLastWasNegative = Ogre::Vector3(0,0,0);

	//mBalanceDirection = Ogre::Vector3(
	//	mBalanceRadiumX == 0 ? 0 : mBalanceRadiumX > 0 ? 1 : -1,
	//	mBalanceRadiumY == 0 ? 0 : mBalanceRadiumY > 0 ? 1 : -1,
	//	mBalanceRadiumZ == 0 ? 0 : mBalanceRadiumZ > 0 ? 1 : -1); 

	//mBalanceAccumulatedTime = 0;

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

	Logger::getInstance()->log("CREATE");
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

void PhysicsComponentComplexConvex::setNxOgreConvex(NxOgre::Convex* pConvexMesh)
{
	mNxOgreConvex=pConvexMesh;
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

void PhysicsComponentComplexConvex::setBalancingParams(double balanceRadiumX, double balanceRadiumY, double balanceRadiumZ, double balanceRadiumTime)
{
	//mBalanceRadiumX = balanceRadiumX;
	//mBalanceRadiumY = balanceRadiumY;
	//mBalanceRadiumZ = balanceRadiumZ;
	//mBalanceRadiumTime = balanceRadiumTime;
}

Ogre::Vector3 PhysicsComponentComplexConvex::getPosition()
{
	if (getMass() > 0)
	{
		return getNxOgreBody()->getGlobalPosition().as<Ogre::Vector3>();
	}
	else
	{
		return getNxOgreKinematicBody()->getGlobalPosition().as<Ogre::Vector3>();
	}
}

void PhysicsComponentComplexConvex::setPosition(Ogre::Vector3 position)
{
	if (getMass() > 0)
	{
		getNxOgreBody()->setGlobalPosition(NxOgre::Vec3(position));
	}
	else
	{
		getNxOgreKinematicBody()->setGlobalPosition(NxOgre::Vec3(position));
	}
}

TPhysicsComponentComplexConvexParameters::TPhysicsComponentComplexConvexParameters() : TPhysicsComponentComplexParameters()
{
	balanceRadiumX = 0;
	balanceRadiumY = 0;
	balanceRadiumZ = 0;
	balanceRadiumTime = 0;
}

TPhysicsComponentComplexConvexParameters::~TPhysicsComponentComplexConvexParameters()
{

}