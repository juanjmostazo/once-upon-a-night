#include "CameraControllerTrajectory.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../TrajectoryManager/Trajectory.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerTrajectory::CameraControllerTrajectory() : CameraController()
{
	//Set CameraControllerTrajectory Initial Parameters

}

CameraControllerTrajectory::~CameraControllerTrajectory()
{
}

TCameraControllerType CameraControllerTrajectory::getControllerType()
{
	return OUAN::CAMERA_TRAJECTORY;
}

void CameraControllerTrajectory::update(double elapsedTime)
{
	//update Trajectory
	mTrajectory->update(elapsedTime);

	//Set camera orientation
	mCamera->setOrientation(mTrajectory->getCurrentOrientation());

	//Set camera position
	mCamera->setPosition(mTrajectory->getCurrentPosition());
}

void CameraControllerTrajectory::setTrajectory(Trajectory * pTrajectory)
{
	mTrajectory=pTrajectory;
}