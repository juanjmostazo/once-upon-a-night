#include "OUAN_Precompiled.h"

#include "CameraController.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraController::CameraController()
{
	mCamera=0;
}
CameraController::~CameraController()
{
}

void CameraController::init(Ogre::SceneManager * pSceneManager)
{
}

void CameraController::setCamera(Camera * pCamera)
{
	mCamera=pCamera;
}

Camera * CameraController::getCamera()
{
	return mCamera;
}

void CameraController::update(double elapsedTime)
{

}

void CameraController::processCameraRotation(Ogre::Vector2 cameraRotation)
{

}

void CameraController::processSimpleTranslation(Ogre::Vector3 translation)
{

}

void CameraController::setTarget(RenderComponentPositionalPtr target)
{

}

void CameraController::reset()
{
}

Ogre::Vector3 CameraController::rotateMovementVector(Ogre::Vector3 movement)
{
	return movement;
}


TCameraControllerType CameraController::getControllerType()
{
	return OUAN::CAMERA_NONE;
}

