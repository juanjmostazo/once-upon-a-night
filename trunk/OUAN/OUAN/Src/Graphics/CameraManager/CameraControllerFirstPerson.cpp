#include "CameraControllerFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerFirstPerson::CameraControllerFirstPerson() : CameraController()
{
	//Set CameraControllerFirstPerson Initial Parameters

	rotX=0;
	rotY=0;

	speed=1.5;
	rotationSpeed=0.2;
}

CameraControllerFirstPerson::~CameraControllerFirstPerson()
{
}

TCameraControllerType CameraControllerFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIRST_PERSON;
}

void CameraControllerFirstPerson::update(double elapsedTime)
{
	//Set camera orientation
	Quaternion yaw(Radian(Degree(rotY)),Vector3::UNIT_Y);
	Quaternion pitch(Radian(Degree(rotX)),Vector3::UNIT_X);
	mCamera->setOrientation(yaw * pitch);

	//Set camera position
	mCamera->setPosition(mCamera->getPosition()+newTranslation);
}

void CameraControllerFirstPerson::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
	rotX=mCamera->getOrientation().getPitch().valueDegrees();
	rotY=mCamera->getOrientation().getYaw().valueDegrees();
}

void CameraControllerFirstPerson::processCameraRotation(Ogre::Vector2 cameraRotation)
{

	//process Relative Motion
	if(cameraRotation.x==0 && cameraRotation.y==0) 
	{
		return;
	}
	else
	{
		rotY-=cameraRotation.x*rotationSpeed;
		rotX-=cameraRotation.y*rotationSpeed;
	}

}

void CameraControllerFirstPerson::processSimpleTranslation(Ogre::Vector3 translation)
{
	newTranslation=-translation;

	newTranslation*=speed;

	//Adapt to current Camera orientation
	newTranslation = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newTranslation;
	newTranslation = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newTranslation;
}