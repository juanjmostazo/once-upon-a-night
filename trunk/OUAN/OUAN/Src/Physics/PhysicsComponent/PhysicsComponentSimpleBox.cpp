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

	NxOgre::Box* pBox = 
		new NxOgre::Box(	getNxOgreSize().x,
							getNxOgreSize().y,
							getNxOgreSize().z);

	if (getMass() > 0)
	{
		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				pBox,
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		setNxOgreKinematicBody(NULL);
	}
	else
	{
		pBox->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
		setStatic(true);
		setNxOgreBody(NULL);

		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
				pBox,
				getSceneNode()->getPosition(),
				getSceneNode()));
	}
}

void PhysicsComponentSimpleBox::destroy()
{
	PhysicsComponentSimple::destroy();
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