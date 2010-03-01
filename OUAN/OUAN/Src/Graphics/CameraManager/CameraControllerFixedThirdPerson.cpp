#include "CameraControllerFixedThirdPerson.h"

using namespace OUAN;

CameraControllerFixedThirdPerson::CameraControllerFixedThirdPerson() : CameraController()
{
}

CameraControllerFixedThirdPerson::~CameraControllerFixedThirdPerson()
{
}

TCameraControllerType CameraControllerFixedThirdPerson::getControllerType()
{
	return OUAN::CAMERA_FIXED_THIRD_PERSON;
}

void CameraControllerFixedThirdPerson::update(long elapsedTime)
{
	mCamera->lookAt(target->getPosition());
}

void CameraControllerFixedThirdPerson::setTarget(Ogre::SceneNode * target)
{
	this->target=target;
}
