#include "CameraControllerTrajectory.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerTrajectory::CameraControllerTrajectory() : CameraController()
{
	//Set CameraControllerTrajectory Initial Parameters

	rotX=0;
	rotY=0;

	speed=0.5;
	rotationSpeed=0.2;
}

CameraControllerTrajectory::~CameraControllerTrajectory()
{
}

TCameraControllerType CameraControllerTrajectory::getControllerType()
{
	return OUAN::CAMERA_TRAJECTORY;
}

void CameraControllerTrajectory::update(long elapsedTime)
{
	//Set camera orientation
	Quaternion yaw(Radian(Degree(rotY)),Vector3::UNIT_Y);
	Quaternion pitch(Radian(Degree(rotX)),Vector3::UNIT_X);
	mCamera->setOrientation(yaw * pitch);

	//Set camera position
	mCamera->setPosition(mCamera->getPosition()+newTranslation);
}

void CameraControllerTrajectory::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
	rotX=mCamera->getOrientation().getPitch().valueDegrees();
	rotY=mCamera->getOrientation().getYaw().valueDegrees();
}
void CameraControllerTrajectory::setTrajectory(Trajectory * pTrajectory)
{
	mTrajectory=pTrajectory;
}