#include "PhysicsComponentSimpleBox.h"
using namespace OUAN;

PhysicsComponentSimpleBox::PhysicsComponentSimpleBox(const std::string& type)
:PhysicsComponentSimple(COMPONENT_TYPE_PHYSICS_SIMPLE_BOX)
{

}

PhysicsComponentSimpleBox::~PhysicsComponentSimpleBox()
{

}

void PhysicsComponentSimpleBox::create()
{
	PhysicsComponentSimple::create();

	if (getNxOgreRigidBodyDescription().mMass > 0)
	{
		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				new NxOgre::Box(getNxOgreSize().x,
								getNxOgreSize().y,
								getNxOgreSize().z),
				getSceneNode()->getPosition(),
				getSceneNode(),
				getNxOgreRigidBodyDescription()));
	}
	else
	{
		setNxOgreBody(NULL);

		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createSceneGeometry(
			new NxOgre::Box(	getNxOgreSize().x,
								getNxOgreSize().y,
								getNxOgreSize().z),
			NxOgre::Matrix44(NxOgre::Vec3(getSceneNode()->getPosition())));

		setStatic(true);
	}
}

void PhysicsComponentSimpleBox::destroy()
{
	PhysicsComponentSimple::destroy();

	if (getNxOgreRigidBodyDescription().mMass > 0)
	{
		NxOgre::RigidBodyDescription tmpDesc = NxOgre::RigidBodyDescription();
		tmpDesc.mMass = getNxOgreRigidBodyDescription().mMass;

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

NxOgre::Vec3 PhysicsComponentSimpleBox::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentSimpleBox::setNxOgreSize(NxOgre::Vec3 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
}

TPhysicsComponentSimpleBoxParameters::TPhysicsComponentSimpleBoxParameters() : TPhysicsComponentSimpleParameters()
{

}

TPhysicsComponentSimpleBoxParameters::~TPhysicsComponentSimpleBoxParameters()
{

}