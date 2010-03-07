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
	
	/****/
	//NxOgre::RigidBodyDescription desc = getNxOgreRigidBodyDescription();
	//desc.mMass = 0;
	//desc.mDensity = 1;
	//setNxOgreRigidBodyDescription(desc);
	/****/

	setNxOgreBody(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
			new NxOgre::Box(getNxOgreSize().x,
							getNxOgreSize().y,
							getNxOgreSize().z),
			getSceneNode()->getPosition(),
			getSceneNode(),
			getNxOgreRigidBodyDescription()));
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