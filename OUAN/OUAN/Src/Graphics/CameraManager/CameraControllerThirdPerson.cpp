#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RenderSubsystem.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
	//Set CameraControllerThirdPerson Initial Parameters

	initialDistance=80;
	initialDirection=Ogre::Vector3(0,0.25,-1);


	collisionMargin=5;
	minDistance=30;
	height=20;
	rotX=0;
	rotY=0;

	speed=0.13;

	collisionMoveSpeed=300;
	collisionReturningSpeed=50;
	returningspeed=2.5;

	rotXDistanceAttenuationNegative=0.5;
	rotXDistanceAttenuationPositive=0.3;

	maxRotX=70;
	minRotX=-45;

	cameraMoved=false;
	cameraIsReturning=false;

	currentCollisionTime=0;
	minCollisionTime=0.3;
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{

}

void CameraControllerThirdPerson::init(RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting)
{
	mSceneManager = pRenderSubsystem->getSceneManager();

	mRayCasting = pRayCasting;

	CameraController::init(pRenderSubsystem->getSceneManager());
}

bool CameraControllerThirdPerson::calculateCameraCollisions(Ogre::Vector3 & cameraPosition, Ogre::Vector3 & cameraLookAt)
{
	Ogre::Vector3 direction;
	Ogre::Vector3 newCameraPosition;
	double currentDistance;

	currentDistance=cameraLookAt.distance(cameraPosition);

	direction=cameraPosition-cameraLookAt;
	direction.normalise();

	newCameraPosition=cameraPosition;

	mRayCasting->raycastRenderClosestGeometry(cameraLookAt,direction,newCameraPosition,currentDistance,QUERYFLAGS_CAMERA_COLLISION);

	if(cameraLookAt.distance(newCameraPosition)<currentDistance)
	{
		newCameraPosition=newCameraPosition-collisionMargin*direction;
		if( cameraLookAt.distance(newCameraPosition)<minDistance)
		{
			newCameraPosition=cameraLookAt+minDistance*direction;
		}
		cameraPosition=newCameraPosition;
		return true;
	}

	return false;
}

void CameraControllerThirdPerson::update(double elapsedTime)
{
	Vector3 newCameraPosition;
	Vector3 cameraCollisionPosition;
	Vector3 newTargetPosition;
	Vector3 cameraLookAt;
	Quaternion newTargetOrientation;

	newTargetPosition=target->getPosition();
	newTargetOrientation=target->getOrientation();

	newCameraPosition=initialDistance*initialDirection;

	//Calculate Camera position in relation to the target
	if(rotX<0)
	{
		newCameraPosition = newCameraPosition-rotXDistanceAttenuationNegative*newCameraPosition*rotX/double(minRotX);
	}
	else
	{
		newCameraPosition = newCameraPosition-rotXDistanceAttenuationPositive*newCameraPosition*rotX/double(maxRotX);
	}

	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = target->getPosition()+newCameraPosition;

	//Calculate Camera look at
	cameraLookAt=newTargetPosition+Vector3(0,height,0);

	cameraCollisionPosition=newCameraPosition;

	Ogre::Vector3 newNextMovePosition;

	//Calculate camera collisions
	if(calculateCameraCollisions(cameraCollisionPosition,cameraLookAt))
	{

		currentCollisionTime+=elapsedTime;
		if(currentCollisionTime>=minCollisionTime)
		{
			collisionDisplacementDistance+=calculateNextMovementTo(mCamera->getPosition(),cameraCollisionPosition,newNextMovePosition,elapsedTime);
			newCameraPosition=newNextMovePosition;
		}
		cameraIsReturning=false;
	}
	else
	{
		currentCollisionTime=0;
		if(collisionDisplacementDistance>0)
		{
			collisionDisplacementDistance-=calculateNextMovementTo(mCamera->getPosition(),newCameraPosition,newNextMovePosition,elapsedTime);
			newCameraPosition=newNextMovePosition;
		}
		//not else if since we take in account last calculateNextMovement
		if(collisionDisplacementDistance<0)
		{
			collisionDisplacementDistance=0;
		}
		cameraIsReturning=true;
	}
	//set camera position
	mCamera->setPosition(newCameraPosition);

	//set camera to look at target
	mCamera->lookAt(cameraLookAt);

	lastTargetPosition=newTargetPosition;
	lastTargetOrientation=newTargetOrientation;

	//Ogre::LogManager::getSingleton().logMessage("[rotX] before "+Ogre::StringConverter::toString(Ogre::Real(rotX)));
	//Ogre::LogManager::getSingleton().logMessage("[rotY] before "+Ogre::StringConverter::toString(Ogre::Real(rotY)));

	//		//BUG WITH ROTATIONS, THEY SHOULD BE UPDATED

	//Rotations correction
	//rotX=mCamera->getOrientation().getRoll().valueDegrees();
	//rotY=mCamera->getOrientation().getYaw().valueDegrees();

	//Ogre::LogManager::getSingleton().logMessage("[rotX] after "+Ogre::StringConverter::toString(Ogre::Real(rotX)));
	//Ogre::LogManager::getSingleton().logMessage("[rotY] after "+Ogre::StringConverter::toString(Ogre::Real(rotY)));
}

double CameraControllerThirdPerson::calculateNextMovementTo(Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,Ogre::Vector3 & newNextMovePosition,double elapsedTime)
{
	Ogre::Vector3 direction;

	double speed;
	if(cameraIsReturning)
	{
		speed=collisionReturningSpeed;
	}
	else
	{
		speed=collisionMoveSpeed;
	}

	if(cameraPosition.distance(newCameraPosition)<speed*elapsedTime)
	{
		newNextMovePosition=newCameraPosition;
		return cameraPosition.distance(newCameraPosition);
	}
	else
	{

		direction=newCameraPosition-cameraPosition;
		direction.normalise();

		newNextMovePosition=cameraPosition+direction*speed*elapsedTime;

		return speed*elapsedTime;
	}
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
void CameraControllerThirdPerson::setTarget(RenderComponentPositionalPtr target)
{
	this->target=target;
	rotY=target->getOrientation().getYaw().valueDegrees();
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}