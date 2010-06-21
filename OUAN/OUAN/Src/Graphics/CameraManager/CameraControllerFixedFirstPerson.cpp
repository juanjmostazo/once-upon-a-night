#include "OUAN_Precompiled.h"

#include "CameraControllerFixedFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerFixedFirstPerson::CameraControllerFixedFirstPerson()
{

}
CameraControllerFixedFirstPerson::~CameraControllerFixedFirstPerson()
{
}

void CameraControllerFixedFirstPerson::init(Ogre::SceneManager * pSceneManager)
{
}

TCameraControllerType CameraControllerFixedFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIRST_PERSON;
}

void CameraControllerFixedFirstPerson::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{

}

void CameraControllerFixedFirstPerson::loadInfo()
{
	CameraController::loadInfo();
}

//#include "OUAN_Precompiled.h"
//
//#include "CameraControllerFixedFirstPerson.h"
//#include "../RenderComponent/RenderComponentPositional.h"
//
//using namespace OUAN;
//
//CameraControllerFixedFirstPerson::CameraControllerFixedFirstPerson() : CameraController()
//{
//	//Set CameraControllerFixedFirstPerson Initial Parameters
//
//	rotX=0;
//	rotY=0;
//
//	speed=0.2;
//
//	maxRotX=50;
//	minRotX=-50;
//
//	maxRotY=89;
//	minRotY=-89;
//
//	height=5;
//}
//
//CameraControllerFixedFirstPerson::~CameraControllerFixedFirstPerson()
//{
//}
//
//TCameraControllerType CameraControllerFixedFirstPerson::getControllerType()
//{
//	return OUAN::CAMERA_FIXED_FIRST_PERSON;
//}
//
//void CameraControllerFixedFirstPerson::setTarget(RenderComponentPositionalPtr target)
//{
//	this->target=target;
//}
//
//
//void CameraControllerFixedFirstPerson::update(double elapsedTime)
//{
//	Quaternion newCameraOrientation;
//
//	//Set camera position
//	mCamera->setPosition(target->getPosition());
//
//	//Calculate Camera orientation in the world
//	newCameraOrientation = target->getOrientation();
//	//Set camera orientation
//	mCamera->setOrientation(newCameraOrientation);
//
//	mCamera->yaw(Ogre::Angle(rotY+180));
//	mCamera->pitch(Ogre::Angle(rotX));
//
//
//
//}
//
//void CameraControllerFixedFirstPerson::processCameraRotation(Ogre::Vector2 cameraRotation)
//{
//	Ogre::Matrix3 next_rotation;
//
//	//process Relative Motion
//	if(cameraRotation.x==0 && cameraRotation.y==0) 
//	{
//		return;
//	}
//	else
//	{
//		rotY-=cameraRotation.x*speed;
//		rotX+=cameraRotation.y*speed;
//	}
//
//	//check if rotation exceeds limits for X axis
//	if(rotX>maxRotX)
//	{
//		rotX=maxRotX;
//	}
//	else if(rotX<minRotX)
//	{
//		rotX=minRotX;
//	}
//
//	//check if rotation exceeds limits for Y axis
//	if(rotY>maxRotY)
//	{
//		rotY=maxRotY;
//	}
//	else if(rotY<minRotY)
//	{
//		rotY=minRotY;
//	}
//	//Logger::getInstance()->log("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));
//
//}