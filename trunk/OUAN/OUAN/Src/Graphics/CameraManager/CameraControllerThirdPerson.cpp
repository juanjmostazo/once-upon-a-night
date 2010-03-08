#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
	//Set CameraControllerThirdPerson Initial Parameters

	distance=Ogre::Vector3(0,10,-25);
	height=5;
	rotX=0;
	rotY=0;

	speed=0.2;
	returningspeed=2.5;

	maxRotX=50;
	minRotX=-50;

	cameraMoved=false;
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{
}

void CameraControllerThirdPerson::update(long elapsedTime)
{
	Ogre::Vector3 newCameraPosition;
	Ogre::Vector3 newTargetPosition;

	newTargetPosition=target->getPosition();

	//If target has moved we return the camera position to the back of the target
	if(newTargetPosition!=lastTargetPosition && !cameraMoved)
	{
		returningToInitialPosition();
	}

	//Calculate Camera position in relation to the target
	newCameraPosition = distance;
	newCameraPosition = Quaternion(Ogre::Degree(rotY+target->getYaw()), Vector3::UNIT_Y) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = target->getPosition()+newCameraPosition;

	//set camera position
	mCamera->setPosition(newCameraPosition);

	//set camera to look at target
	mCamera->lookAt(newTargetPosition+Vector3(0,height,0));

	lastTargetPosition=newTargetPosition;

}

void CameraControllerThirdPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{
	Ogre::Matrix3 next_rotation;

	//process Relative Motion
	if(xRel==0 && yRel==0) 
	{
		cameraMoved=false;
		return;
	}
	else
	{
		cameraMoved=true;
		rotY-=xRel*speed;
		rotX-=yRel*speed;
	}

	//check if rotation exceeds limits
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
void CameraControllerThirdPerson::setTarget(RenderComponentPositional * target)
{
	this->target=target;
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}

void CameraControllerThirdPerson::returningToInitialPosition()
{
	//If we reach the initial position we set rotation to 0 in order to avoid accumulated error
	if(Ogre::Math::Abs(rotX)<returningspeed)
	{
		rotX=0;
	}

	if(Ogre::Math::Abs(rotY)<=returningspeed)
	{
		rotY=0;
	}

	//Return camera to initial position
	if(rotX>0)
	{
		rotX-=returningspeed;
	}
	else if(rotX<0)
	{
		rotX+=returningspeed;
	}

	if(rotY>0)
	{
		rotY-=returningspeed;
	}
	else if(rotY<0)
	{
		rotY+=returningspeed;
	}


}
