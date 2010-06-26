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

	mBalanceLastWasPositive = Ogre::Vector3(0,0,0);
	mBalanceLastWasCenter = Ogre::Vector3(1,1,1);
	mBalanceLastWasNegative = Ogre::Vector3(0,0,0);

	mBalanceDirection = Ogre::Vector3(
		mBalanceRadioX == 0 ? 0 : mBalanceRadioX > 0 ? 1 : -1,
		mBalanceRadioY == 0 ? 0 : mBalanceRadioY > 0 ? 1 : -1,
		mBalanceRadioZ == 0 ? 0 : mBalanceRadioZ > 0 ? 1 : -1); 

	mBalanceAccumulatedTime = 0;

	mLastPositionDifference = Ogre::Vector3(0,0,0);

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

void PhysicsComponentComplexConvex::update(double elapsedSeconds)
{
	PhysicsComponentComplex::update(elapsedSeconds);

	if (canUpdateBalancing(elapsedSeconds))
	{
		updateBalancing(elapsedSeconds);
	}
}

bool PhysicsComponentComplexConvex::canUpdateBalancing(double elapsedSeconds)
{
	return isInUse() 
		&& !getParent()->isFirstUpdate() 
		&& mBalanceRadioTime > 0 
		&& elapsedSeconds <= mBalanceRadioTime;
}

void PhysicsComponentComplexConvex::updateBalancing(double elapsedSeconds)
{
	double balanceOldAccumulatedTime = mBalanceAccumulatedTime;

	mBalanceAccumulatedTime += elapsedSeconds;
	mBalanceAccumulatedTime >= mBalanceRadioTime ? mBalanceRadioTime : mBalanceAccumulatedTime;

	double fixedElapsedTime = balanceOldAccumulatedTime - mBalanceAccumulatedTime;

	///////////////////////

	Ogre::Vector3 position = getPosition();
	Ogre::Vector3 newPosition = position;
	newPosition.x += mBalanceDirection.x * fabs(mBalanceRadioX) * fixedElapsedTime / mBalanceRadioTime;
	newPosition.y += mBalanceDirection.y * fabs(mBalanceRadioY) * fixedElapsedTime / mBalanceRadioTime;
	newPosition.z += mBalanceDirection.z * fabs(mBalanceRadioZ) * fixedElapsedTime / mBalanceRadioTime;
	setPosition(newPosition);
	mLastPositionDifference = newPosition - position;

	///////////////////////

	if (mBalanceAccumulatedTime >= mBalanceRadioTime)
	{
		mBalanceAccumulatedTime = 0;

		//X
		if (mBalanceLastWasCenter.x == 1)
		{
			if (mBalanceDirection.x > 0)
			{	
				mBalanceLastWasPositive.x = 1;
			}
			else
			{
				mBalanceLastWasNegative.x = 1;
			}

			mBalanceDirection.x = -mBalanceDirection.x;
			mBalanceLastWasCenter.x = 0;
		}
		else if (mBalanceLastWasNegative.x == 1)
		{
			mBalanceLastWasNegative.x = 0;
			mBalanceLastWasCenter.x = 1;
		}
		else if (mBalanceLastWasPositive.x == 1)
		{
			mBalanceLastWasPositive.x = 0;
			mBalanceLastWasCenter.x = 1;
		}

		//Y
		if (mBalanceLastWasCenter.y == 1)
		{
			if (mBalanceDirection.y > 0)
			{	
				mBalanceLastWasPositive.y = 1;
			}
			else
			{
				mBalanceLastWasNegative.y = 1;
			}

			mBalanceDirection.y = -mBalanceDirection.y;
			mBalanceLastWasCenter.y = 0;
		}
		else if (mBalanceLastWasNegative.y == 1)
		{
			mBalanceLastWasNegative.y = 0;
			mBalanceLastWasCenter.y = 1;
		}
		else if (mBalanceLastWasPositive.y == 1)
		{
			mBalanceLastWasPositive.y = 0;
			mBalanceLastWasCenter.y = 1;
		}

		//Z
		if (mBalanceLastWasCenter.z == 1)
		{
			if (mBalanceDirection.z > 0)
			{	
				mBalanceLastWasPositive.z = 1;
			}
			else
			{
				mBalanceLastWasNegative.z = 1;
			}

			mBalanceDirection.z = -mBalanceDirection.z;
			mBalanceLastWasCenter.z = 0;
		}
		else if (mBalanceLastWasNegative.z == 1)
		{
			mBalanceLastWasNegative.z = 0;
			mBalanceLastWasCenter.z = 1;
		}
		else if (mBalanceLastWasPositive.z == 1)
		{
			mBalanceLastWasPositive.z = 0;
			mBalanceLastWasCenter.z = 1;
		}
	}

	//Logger::getInstance()->log("@@@ AFTER " + getParent()->getName() + 
	//	" \n :: mBalanceLastWasBottom: " + Ogre::StringConverter::toString(mBalanceLastWasBottom) + 
	//	" \n :: mBalanceLastWasCenter: " + Ogre::StringConverter::toString(mBalanceLastWasCenter) + 
	//	" \n :: mBalanceLastWasTop: " + Ogre::StringConverter::toString(mBalanceLastWasTop) + 
	//	" \n :: mBalanceDirection: " + Ogre::StringConverter::toString(Ogre::Real(mBalanceDirection)) + 
	//	" \n :: mBalanceAccumulatedTime " + Ogre::StringConverter::toString(Ogre::Real(mBalanceAccumulatedTime)) + 
	//	" \n :: mBalanceRadioTime " + Ogre::StringConverter::toString(Ogre::Real(mBalanceRadioTime)) + 
	//	" \n :: elapsedTime " + Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)));
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

void PhysicsComponentComplexConvex::setBalancingParams(double balanceRadioX, double balanceRadioY, double balanceRadioZ, double balanceRadioTime)
{
	mBalanceRadioX = balanceRadioX;
	mBalanceRadioY = balanceRadioY;
	mBalanceRadioZ = balanceRadioZ;
	mBalanceRadioTime = balanceRadioTime;
}

Ogre::Vector3 PhysicsComponentComplexConvex::getLastPositionDifference()
{
	return mLastPositionDifference;
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
	balanceRadioX = 0;
	balanceRadioY = 0;
	balanceRadioZ = 0;
	balanceRadioTime = 0;
}

TPhysicsComponentComplexConvexParameters::~TPhysicsComponentComplexConvexParameters()
{

}