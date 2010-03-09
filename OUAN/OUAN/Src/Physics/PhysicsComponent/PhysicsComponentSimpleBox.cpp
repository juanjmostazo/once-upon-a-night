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

	if (getMass() > 0)
	{
		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				new NxOgre::Box(getNxOgreSize().x,
								getNxOgreSize().y,
								getNxOgreSize().z),
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		setNxOgreKinematicBody(NULL);
	}
	else
	{
		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
				new NxOgre::Box(getNxOgreSize().x,
								getNxOgreSize().y,
								getNxOgreSize().z),
				getSceneNode()->getPosition(),
				getSceneNode()));

		setStatic(true);
		setNxOgreBody(NULL);
	}
}

void PhysicsComponentSimpleBox::destroy()
{
	PhysicsComponentSimple::destroy();

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