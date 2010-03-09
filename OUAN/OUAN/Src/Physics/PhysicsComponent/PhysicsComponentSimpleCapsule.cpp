#include "PhysicsComponentSimpleCapsule.h"
using namespace OUAN;

PhysicsComponentSimpleCapsule::PhysicsComponentSimpleCapsule(const std::string& type)
:PhysicsComponentSimple(COMPONENT_TYPE_PHYSICS_SIMPLE_CAPSULE)
{

}

PhysicsComponentSimpleCapsule::~PhysicsComponentSimpleCapsule()
{

}

void PhysicsComponentSimpleCapsule::create()
{
	PhysicsComponentSimple::create();
	
	if (getMass() > 0)
	{
		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				new NxOgre::Capsule(getNxOgreSize().x,
									getNxOgreSize().y),
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));
	}
	else
	{
		setNxOgreBody(NULL);

		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createSceneGeometry(
			new NxOgre::Capsule(getNxOgreSize().x,
								getNxOgreSize().y),
			NxOgre::Matrix44(NxOgre::Vec3(getSceneNode()->getPosition())));

		setStatic(true);
	}
}

void PhysicsComponentSimpleCapsule::destroy()
{
	PhysicsComponentSimple::destroy();

	if (getMass() > 0)
	{
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->destroyBody(getNxOgreBody());
		setNxOgreBody(NULL);
	}
	else
	{
		//TODO: STATIC SCENE GEOMETRY CANNOT BE DELETED
		mInUse=true;
	}
}

NxOgre::Vec2 PhysicsComponentSimpleCapsule::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentSimpleCapsule::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
}

TPhysicsComponentSimpleCapsuleParameters::TPhysicsComponentSimpleCapsuleParameters() : TPhysicsComponentSimpleParameters()
{

}

TPhysicsComponentSimpleCapsuleParameters::~TPhysicsComponentSimpleCapsuleParameters()
{

}