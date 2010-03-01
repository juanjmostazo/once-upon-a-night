#include "CameraControllerTrajectory.h"

using namespace OUAN;

CameraControllerTrajectory::CameraControllerTrajectory() : CameraController()
{
}

CameraControllerTrajectory::~CameraControllerTrajectory()
{
}

TCameraControllerType CameraControllerTrajectory::getControllerType()
{
	return OUAN::CAMERA_TRAJECTORY;
}
