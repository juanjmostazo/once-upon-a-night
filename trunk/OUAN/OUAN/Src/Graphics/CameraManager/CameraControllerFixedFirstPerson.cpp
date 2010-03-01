#include "CameraControllerFixedFirstPerson.h"

using namespace OUAN;

CameraControllerFixedFirstPerson::CameraControllerFixedFirstPerson() : CameraController()
{
}

CameraControllerFixedFirstPerson::~CameraControllerFixedFirstPerson()
{
}

TCameraControllerType CameraControllerFixedFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIXED_FIRST_PERSON;
}