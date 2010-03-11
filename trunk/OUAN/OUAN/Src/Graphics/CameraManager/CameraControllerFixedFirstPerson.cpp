#include "CameraControllerFixedFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;

CameraControllerFixedFirstPerson::CameraControllerFixedFirstPerson() : CameraController()
{
	//Set CameraControllerFixedFirstPerson Initial Parameters

	rotX=0;
	rotY=0;

	speed=0.2;

	maxRotX=50;
	minRotX=-50;

	maxRotY=89;
	minRotY=-89;

	height=5;
}

CameraControllerFixedFirstPerson::~CameraControllerFixedFirstPerson()
{
}

TCameraControllerType CameraControllerFixedFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIXED_FIRST_PERSON;
}

void CameraControllerFixedFirstPerson::setTarget(RenderComponentPositional * target)
{
	this->target=target;
}


void CameraControllerFixedFirstPerson::update(long elapsedTime)
{
	Quaternion newCameraOrientation;

	//Set camera position
	mCamera->setPosition(target->getPosition());

	//Calculate Camera orientation in the world
	newCameraOrientation = target->getOrientation();
	//Set camera orientation
	mCamera->setOrientation(newCameraOrientation);

	mCamera->yaw(Ogre::Angle(rotY+180));
	mCamera->pitch(Ogre::Angle(rotX));



}

void CameraControllerFixedFirstPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{
	Ogre::Matrix3 next_rotation;

	//process Relative Motion
	if(xRel==0 && yRel==0) 
	{
		return;
	}
	else
	{
		rotY-=xRel*speed;
		rotX-=yRel*speed;
	}

	//check if rotation exceeds limits for X axis
	if(rotX>maxRotX)
	{
		rotX=maxRotX;
	}
	else if(rotX<minRotX)
	{
		rotX=minRotX;
	}

	//check if rotation exceeds limits for Y axis
	if(rotY>maxRotY)
	{
		rotY=maxRotY;
	}
	else if(rotY<minRotY)
	{
		rotY=minRotY;
	}
	//Ogre::LogManager::getSingleton().logMessage("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));

}