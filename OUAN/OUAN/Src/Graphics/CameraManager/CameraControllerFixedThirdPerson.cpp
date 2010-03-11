#include "CameraControllerFixedThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;

CameraControllerFixedThirdPerson::CameraControllerFixedThirdPerson() : CameraController()
{
	height=5;
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
	mCamera->lookAt(target->getPosition()+Vector3(0,height,0));
}

void CameraControllerFixedThirdPerson::setTarget(RenderComponentPositional * target)
{
	this->target=target;
}
