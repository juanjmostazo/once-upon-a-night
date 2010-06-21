#include "OUAN_Precompiled.h"

#include "CameraControllerFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "CameraInput.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerFirstPerson::CameraControllerFirstPerson()
{

}
CameraControllerFirstPerson::~CameraControllerFirstPerson()
{
}

void CameraControllerFirstPerson::init(Ogre::SceneManager * pSceneManager)
{
	rotX=0;
	rotY=0;

	speed=1.5;
	rotationSpeed=0.2;
}

TCameraControllerType CameraControllerFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIRST_PERSON;
}

void CameraControllerFirstPerson::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{
	processCameraRotation(pCameraInput->mRotation);
	processSimpleTranslation(pCameraInput->mTranslation);

	//Set camera orientation
	Quaternion yaw(Radian(Degree(rotY)),Vector3::UNIT_Y);
	Quaternion pitch(Radian(Degree(rotX)),Vector3::UNIT_X);
	pCamera->setOrientation(yaw * pitch);

	//Set camera position
	pCamera->setPosition(pCamera->getPosition()+newTranslation);
}

void CameraControllerFirstPerson::loadInfo()
{
	CameraController::loadInfo();
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
		rotX+=cameraRotation.y*rotationSpeed;
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