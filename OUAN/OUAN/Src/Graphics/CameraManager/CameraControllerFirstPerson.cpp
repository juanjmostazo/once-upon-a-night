#include "CameraControllerFirstPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;

CameraControllerFirstPerson::CameraControllerFirstPerson() : CameraController()
{
	//Set CameraControllerFirstPerson Initial Parameters

	rotX=0;
	rotY=0;

	speed=0.5;

	maxRotX=90;
	minRotX=-90;

	height=5;

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
	Quaternion newCameraOrientation;

	//Set camera position
	mCamera->setPosition(mCamera->getPosition()+newTranslation);

	mCamera->yaw(Ogre::Angle(rotY));
	//mCamera->pitch(Ogre::Angle(rotX));


}

void CameraControllerFirstPerson::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
	rotX=mCamera->getOrientation().getPitch().valueAngleUnits();
	rotY=mCamera->getOrientation().getYaw().valueAngleUnits();
}

void CameraControllerFirstPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{
	rotY=0;
	rotX=0;

	//process Relative Motion
	if(xRel==0 && yRel==0) 
	{
		return;
	}
	else
	{
		rotY-=xRel*speed;
		//rotX-=yRel*speed;
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

	//Ogre::LogManager::getSingleton().logMessage("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));

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
	//newTranslation = Quaternion(Ogre::Angle(rotX), Vector3::UNIT_X) * newTranslation;
	newTranslation = Quaternion(mCamera->getOrientation().getYaw(), Vector3::UNIT_Y) * newTranslation;


}