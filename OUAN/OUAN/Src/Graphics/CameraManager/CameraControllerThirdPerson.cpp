#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RayCasting/RayCasting.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
	//Set CameraControllerThirdPerson Initial Parameters

	distance=Ogre::Vector3(0,15,-45);
	initialDistance=distance;
	height=5;
	rotX=0;
	rotY=0;

	speed=0.2;
	returningspeed=2.5;

	maxRotX=25;
	minRotX=-35;

	cameraMoved=false;
	cameraIsReturning=false;
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{

}

void CameraControllerThirdPerson::init(Ogre::SceneManager * pSceneManager)
{
	mSceneManager = pSceneManager;

	mRayCasting = new RayCasting();
	mRayCasting->init(pSceneManager);

	CameraController::init(pSceneManager);
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraCollisions(Ogre::Vector3 currentCameraPosition, Ogre::Vector3 currentCameraLookAt)
{
	Ogre::Vector3 direction;
	Ogre::Vector3 newCameraPosition;

	direction=currentCameraPosition-currentCameraLookAt;
	direction.normalise();

	mRayCasting->raycastFromPoint(currentCameraLookAt,direction,newCameraPosition,QUERYFLAGS_CAMERA_COLLISION);

	if(currentCameraLookAt.distance(newCameraPosition)<currentCameraLookAt.distance(currentCameraPosition))
	{
		return newCameraPosition;
	}

	return currentCameraPosition;
}

void CameraControllerThirdPerson::update(double elapsedTime)
{
	Vector3 newCameraPosition;
	Vector3 newTargetPosition;
	Vector3 cameraLookAt;
	Quaternion newTargetOrientation;

	newTargetPosition=target->getPosition();
	newTargetOrientation=target->getOrientation();

	//if(cameraMoved)
	//{
	//	cameraIsReturning=false;
	//}

	////If target has moved we return the camera position to the back of the target
	//if((newTargetPosition!=lastTargetPosition || newTargetOrientation!=lastTargetOrientation) || cameraIsReturning)
	//{
	//	returningToInitialPosition();
	//	cameraIsReturning=true;
	//}
	//else
	//{
	//	cameraIsReturning=false;
	//}


	//Calculate Camera position in relation to the target
	newCameraPosition = initialDistance;
	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = target->getPosition()+newCameraPosition;

	//Calculate Camera look at
	cameraLookAt=newTargetPosition+Vector3(0,height,0);

	//Calculate camera collisions
	newCameraPosition=calculateCameraCollisions(newCameraPosition,newTargetPosition);

	//set camera position
	mCamera->setPosition(newCameraPosition);

	//set camera to look at target
	mCamera->lookAt(cameraLookAt);

	lastTargetPosition=newTargetPosition;
	lastTargetOrientation=newTargetOrientation;
}

Ogre::Vector3 CameraControllerThirdPerson::rotateMovementVector(Ogre::Vector3 movement)
{
	return Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * movement;
}

void CameraControllerThirdPerson::processCameraRotation(Ogre::Vector2 cameraRotation)
{

	//process Relative Motion
	if(cameraRotation.x==0 && cameraRotation.y==0) 
	{
		cameraMoved=false;
		return;
	}
	else
	{
		cameraMoved=true;
		rotY-=cameraRotation.x*speed;
		rotX-=cameraRotation.y*speed;
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
		cameraIsReturning=false;
	}

	if(Ogre::Math::Abs(rotY)<=returningspeed)
	{
		rotY=0;
		cameraIsReturning=false;
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
