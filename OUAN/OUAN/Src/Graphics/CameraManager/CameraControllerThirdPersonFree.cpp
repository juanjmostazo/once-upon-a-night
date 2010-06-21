#include "OUAN_Precompiled.h"

#include "CameraControllerThirdPersonFree.h"
#include "CameraInput.h"
#include "CameraParameters.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPersonFree::CameraControllerThirdPersonFree()
{
	rotX=0;
	rotY=0;
}
CameraControllerThirdPersonFree::~CameraControllerThirdPersonFree()
{
}

void CameraControllerThirdPersonFree::init(Ogre::SceneManager * pSceneManager)
{
	loadInfo();
}

TCameraControllerType CameraControllerThirdPersonFree::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON_FREE;
}

void CameraControllerThirdPersonFree::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{
	Vector3 cameraPosition;
	Vector3 cameraLookAt;

	processCameraRotation(pCameraInput);

	cameraPosition=calculateCameraPosition(pCamera,pCameraInput);
	cameraLookAt=calculateTargetPosition(pCameraInput);

	pCamera->setPosition(cameraPosition);

	//set camera to look at target
	pCamera->lookAt(cameraLookAt);
}

Ogre::Vector3 CameraControllerThirdPersonFree::calculateTargetPosition(CameraInputPtr pCameraInput)
{
	return pCameraInput->mTarget->getSceneNode()->getPosition()+pCameraInput->mTargetOffset;
}


void CameraControllerThirdPersonFree::processCameraRotation(CameraInputPtr pCameraInput)
{
	rotateY(-pCameraInput->mRotation.x*speedY);
	rotateX(-pCameraInput->mRotation.y*speedX);
}

void CameraControllerThirdPersonFree::rotateX(double rotation)
{
	rotX+=rotation;
	//check if rotation exceeds limits
	if(rotX>maxRotX)
	{
		rotX=maxRotX;
	}
	else if(rotX<minRotX)
	{
		rotX=minRotX;
	}
}

void CameraControllerThirdPersonFree::rotateY(double rotation)
{
	rotY+=rotation;
}


void CameraControllerThirdPersonFree::loadInfo()
{
	CameraController::loadInfo();

	Configuration config;
	std::string value;

	if (config.loadFromFile(CAMERA_CONTROLLER_THIRD_PERSON_FREE_CFG))
	{
		double initial_directionX, initial_directionY, initial_directionZ;

		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());

		initialDirection = Vector3(initial_directionX, initial_directionY, initial_directionZ);
		initialDirection.normalise();

		config.getOption("MIN_ROT_X", value); 
		minRotX = atof(value.c_str());

		config.getOption("MAX_ROT_X", value); 
		maxRotX = atof(value.c_str());

		config.getOption("SPEED_X", value); 
		speedX = atof(value.c_str());

		config.getOption("SPEED_Y", value); 
		speedY = atof(value.c_str());

		config.getOption("ROT_X_ATTENUATION_POSITIVE", value); 
		rotXDistanceAttenuationPositive = atof(value.c_str());

		config.getOption("ROT_X_ATTENUATION_NEGATIVE", value); 
		rotXDistanceAttenuationNegative = atof(value.c_str());

		config.getOption("DISTANCE", value); 
		distance = atof(value.c_str());
	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CONTROLLER_THIRD_PERSON_FREE_CFG + " COULD NOT BE LOADED!");
	}
}

Ogre::Vector3 CameraControllerThirdPersonFree::rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds)
{
	movement = Ogre::Quaternion(Ogre::Degree(pCamera->getOrientation().getYaw().valueDegrees()-180),Ogre::Vector3::UNIT_Y) * movement;

	return movement;
}

void CameraControllerThirdPersonFree::setCameraParameters(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	Vector3 cameraPosition;
	Vector3 cameraLookAt;
	cameraPosition=calculateCameraPosition(pCamera,pCameraInput);
	cameraLookAt=calculateTargetPosition(pCameraInput);

	pCamera->setPosition(cameraPosition);

	//set camera to look at target
	pCamera->lookAt(cameraLookAt);
}

Ogre::Vector3 CameraControllerThirdPersonFree::calculateCameraPosition(Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Ogre::Vector3 newCameraPosition;
	Ogre::Vector3 targetPosition;
	
	targetPosition=pCameraInput->mTarget->getSceneNode()->getPosition();

	newCameraPosition=distance*initialDirection;

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
	newCameraPosition = targetPosition+newCameraPosition;

	return newCameraPosition;
}
	