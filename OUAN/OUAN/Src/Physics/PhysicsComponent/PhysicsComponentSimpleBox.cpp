#include "OUAN_Precompiled.h"

#include "PhysicsComponentSimpleBox.h"
using namespace OUAN;

PhysicsComponentSimpleBox::PhysicsComponentSimpleBox(const std::string& type)
:PhysicsComponentSimple(type)
,mInitialVelocity(NxOgre::Vec3::ZERO)
{

}

PhysicsComponentSimpleBox::~PhysicsComponentSimpleBox()
{

}

void PhysicsComponentSimpleBox::create()
{
	PhysicsComponentSimple::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());

	mBox = 
		new NxOgre::Box(	getNxOgreSize().x,
							getNxOgreSize().y,
							getNxOgreSize().z);

	mBox->setName(name);

	mBox->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);

	if (getMass() > 0)
	{
		setNxOgreKinematicBody(NULL);

		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();
		pDesc.mName = name;
		pDesc.mLinearVelocity=mInitialVelocity;

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				mBox,
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		getNxOgreBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));

		//Logger::getInstance()->log(getParent()->getName() + " OGRE3DBODY: " + Ogre::StringConverter::toString(
		//	getNxOgreBody()->getContactReportFlags()));
	}
	else
	{
		mBox->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
		setStatic(true);
		setNxOgreBody(NULL);

		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
				mBox,
				getSceneNode()->getPosition(),
				getSceneNode()));

		getNxOgreKinematicBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));

		//Logger::getInstance()->log(getParent()->getName() + " OGRE3DKINEMATICBODY: " + Ogre::StringConverter::toString(
		//	pBox->getFlag()));
	}

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			mBox,								
			NxOgre::Matrix44(	
				NxOgre::Vec3(getSceneNode()->getPosition()), 
				NxOgre::Quat(getSceneNode()->getOrientation())),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));	
}

void PhysicsComponentSimpleBox::destroy()
{
	PhysicsComponentSimple::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->destroyVolume(getNxOgreVolume());
}

NxOgre::Volume* PhysicsComponentSimpleBox::getNxOgreVolume()
{
	return mNxOgreVolume;
}

void PhysicsComponentSimpleBox::setNxOgreVolume(NxOgre::Volume* pNxOgreVolume)
{
	mNxOgreVolume=pNxOgreVolume;
}

NxOgre::Vec3 PhysicsComponentSimpleBox::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentSimpleBox::setNxOgreSize(NxOgre::Vec3 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
	mHeight=pNxOgreSize.y;
}

NxOgre::Vec3 PhysicsComponentSimpleBox::getInitialVelocity()
{
	return mInitialVelocity;
}
void PhysicsComponentSimpleBox::setInitialVelocity(NxOgre::Vec3 pInitVelocity)
{
	mInitialVelocity=pInitVelocity;
}

//void PhysicsComponentSimpleBox::setQueryFlags(QueryFlags queryFlags)
//{
//	mQueryFlags=queryFlags;
//}

TPhysicsComponentSimpleBoxParameters::TPhysicsComponentSimpleBoxParameters() : TPhysicsComponentSimpleParameters()
{

}

TPhysicsComponentSimpleBoxParameters::~TPhysicsComponentSimpleBoxParameters()
{

}