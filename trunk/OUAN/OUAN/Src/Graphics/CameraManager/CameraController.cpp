#include "OUAN_Precompiled.h"

#include "CameraController.h"
#include "CameraInput.h"
#include "CameraParameters.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

using namespace OUAN;
using namespace Ogre;

CameraController::CameraController()
{
}
CameraController::~CameraController()
{
}

void CameraController::init(Ogre::SceneManager * pSceneManager)
{
}

void CameraController::clear()
{
}

TCameraControllerType CameraController::getControllerType()
{
	return OUAN::CAMERA_NONE;
}

void CameraController::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{

}

void CameraController::loadInfo()
{

}

Ogre::Vector3 CameraController::rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds)
{
	return movement;
}

double CameraController::calculateDistanceToTarget(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,bool twoDimensions)
{
	Ogre::Vector3 targetPosition=pCameraInput->mCameraParameters->getTarget()->getSceneNode()->getPosition();
	Ogre::Vector3 cameraPosition=pCamera->getPosition();

	if(twoDimensions)
	{
		cameraPosition.y=0.0f;
		targetPosition.y=0.0f;
	}

	return cameraPosition.distance(targetPosition);
}