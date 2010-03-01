#include "CameraController.h"

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

void CameraController::setCamera(Camera * pCamera)
{
	mCamera=pCamera;
}

Camera * CameraController::getCamera()
{
	return mCamera;
}

void CameraController::update(long elapsedTime)
{

}

void CameraController::processMouseInput(const OIS::MouseEvent &e)
{

}

void CameraController::processRelativeMotion(double xRel,double yRel,double zRel)
{

}

void CameraController::processSimpleTranslation(Ogre::Vector3 translationVector)
{

}

void CameraController::setTarget(Ogre::SceneNode * target)
{

}
TCameraControllerType CameraController::getControllerType()
{
	return OUAN::CAMERA_NONE;
}