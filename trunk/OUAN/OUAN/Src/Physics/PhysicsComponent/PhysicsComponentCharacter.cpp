#include "PhysicsComponentCharacter.h"
using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(COMPONENT_TYPE_PHYSICS_CHARACTER)
{

}

PhysicsComponentCharacter::~PhysicsComponentCharacter()
{

}

void PhysicsComponentCharacter::create()
{
	PhysicsComponent::create();

	setNxOgreController(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->
				createPointRenderable(getSceneNode())));
}

void PhysicsComponentCharacter::destroy()
{
	PhysicsComponent::destroy();
}

double PhysicsComponentCharacter::getMass()
{
	return mNxOgreMass;
}

void PhysicsComponentCharacter::setMass(double pNxOgreMass)
{
	mNxOgreMass=pNxOgreMass;
}

void PhysicsComponentCharacter::setNxOgreController(NxOgre::Controller* pNxOgreController)
{
	mNxOgreController = pNxOgreController;
}

NxOgre::Controller* PhysicsComponentCharacter::getNxOgreController()
{
	return mNxOgreController;
}

void PhysicsComponentCharacter::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize = pNxOgreSize;
}

NxOgre::Vec2 PhysicsComponentCharacter::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentCharacter::setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription)
{
	mNxOgreControllerDescription = pNxOgreControllerDescription;
}

NxOgre::ControllerDescription PhysicsComponentCharacter::getNxOgreControllerDescription()
{
	return mNxOgreControllerDescription;
}

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{

}