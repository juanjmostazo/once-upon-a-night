#include "CameraControllerFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerFirstPerson::CameraControllerFirstPerson() : CameraController()
{
	//Set CameraControllerFirstPerson Initial Parameters

	rotX=0;
	rotY=0;

	speed=0.5;
	rotationSpeed=0.2;
}

CameraControllerFirstPerson::~CameraControllerFirstPerson()
{
}

TCameraControllerType CameraControllerFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIRST_PERSON;
}

void CameraControllerFirstPerson::update(long elapsedTime)
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

void CameraControllerFirstPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{

	//process Relative Motion
	if(xRel==0 && yRel==0) 
	{
		return;
	}
	else
	{
		rotY-=xRel*rotationSpeed;
		rotX-=yRel*rotationSpeed;
	}

}

void CameraControllerFirstPerson::processSimpleTranslation(int movementFlags)
{
	newTranslation=Vector3(0,0,0);

	//Forwand / backwards
	if ((movementFlags & MOV_FORWARD_OR_BACK) > 0)
	{	
		double way = ((movementFlags & MOV_GO_FORWARD) > 0) ? 1.0f : -1.0f;
		newTranslation -= Ogre::Vector3::UNIT_Z * way;
	}

	//strafe left / right
	if ((movementFlags & MOV_LEFT_OR_RIGHT) > 0)
	{
		double way = ((movementFlags & MOV_GO_LEFT) > 0) ? 1.0f : -1.0f;
		newTranslation -= Ogre::Vector3::UNIT_X * way;
	}

	newTranslation*=speed;

	//Adapt to current Camera orientation
	newTranslation = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newTranslation;
	newTranslation = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newTranslation;
}