#include "CameraControllerFixedThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;

CameraControllerFixedThirdPerson::CameraControllerFixedThirdPerson() : CameraController()
{
	height=5;

	rotY=0;
}

CameraControllerFixedThirdPerson::~CameraControllerFixedThirdPerson()
{
}

TCameraControllerType CameraControllerFixedThirdPerson::getControllerType()
{
	return OUAN::CAMERA_FIXED_THIRD_PERSON;
}

void CameraControllerFixedThirdPerson::update(double elapsedTime)
{
	mCamera->lookAt(target->getPosition()+Vector3(0,height,0));
}

void CameraControllerFixedThirdPerson::setTarget(RenderComponentPositionalPtr target)
{
	this->target=target;
	if(mCamera && target)
	{
		calculateRotY();
	}
}

void CameraControllerFixedThirdPerson::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
	if(mCamera && target)
	{		
		calculateRotY();
	}
}

void CameraControllerFixedThirdPerson::calculateRotY()
{
	rotY=180+mCamera->getOrientation().getYaw().valueDegrees();
	//Ogre::LogManager::getSingleton().logMessage("[rotY] "+Ogre::StringConverter::toString(Ogre::Real(rotY)));
}

Ogre::Vector3 CameraControllerFixedThirdPerson::rotateMovementVector(Ogre::Vector3 movement)
{
	return Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * movement;
}

