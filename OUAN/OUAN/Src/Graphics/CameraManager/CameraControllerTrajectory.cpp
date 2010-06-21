#include "OUAN_Precompiled.h"

#include "CameraControllerTrajectory.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerTrajectory::CameraControllerTrajectory()
{

}
CameraControllerTrajectory::~CameraControllerTrajectory()
{
}

void CameraControllerTrajectory::init(Ogre::SceneManager * pSceneManager)
{
}

TCameraControllerType CameraControllerTrajectory::getControllerType()
{
	return OUAN::CAMERA_TRAJECTORY;
}

void CameraControllerTrajectory::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{

}

void CameraControllerTrajectory::loadInfo()
{
	CameraController::loadInfo();
}

//#include "OUAN_Precompiled.h"
//
//#include "CameraControllerTrajectory.h"
//#include "../RenderComponent/RenderComponentPositional.h"
//#include "../TrajectoryManager/Trajectory.h"
//
//using namespace OUAN;
//using namespace Ogre;
//
//CameraControllerTrajectory::CameraControllerTrajectory() : CameraController()
//{
//	//Set CameraControllerTrajectory Initial Parameters
//	mSceneNode=NULL;
//	mSceneManager=NULL;
//}
//
//CameraControllerTrajectory::~CameraControllerTrajectory()
//{
//}
//
//TCameraControllerType CameraControllerTrajectory::getControllerType()
//{
//	return OUAN::CAMERA_TRAJECTORY;
//}
//
//void CameraControllerTrajectory::init(Ogre::SceneManager * pSceneManager)
//{
//	mSceneManager=pSceneManager;
//}
//
//void CameraControllerTrajectory::resetTrajectory()
//{
//	mTrajectory->reset();
//
//	if(mSceneNode)
//	{
//		//Set camera orientation
//		mSceneNode->setOrientation(mTrajectory->getCurrentOrientation());
//		//Set camera position
//		mSceneNode->setPosition(mTrajectory->getCurrentPosition());
//	}
//}
//
//void CameraControllerTrajectory::detachCamera()
//{
//	if(mSceneNode)
//	{
//		mSceneNode->detachAllObjects();
//	}
//}
//
//void CameraControllerTrajectory::update(double elapsedTime)
//{
//	//update Trajectory
//	mTrajectory->update(elapsedTime);
//
//	//Set camera orientation
//	mSceneNode->setOrientation(mTrajectory->getCurrentOrientation());
//
//	//Set camera position
//	mSceneNode->setPosition(mTrajectory->getCurrentPosition());
//}
//
//void CameraControllerTrajectory::setTrajectory(Trajectory * pTrajectory)
//{
//	mTrajectory=pTrajectory;
//}
//
//Trajectory * CameraControllerTrajectory::getTrajectory() const
//{
//	return mTrajectory;
//}