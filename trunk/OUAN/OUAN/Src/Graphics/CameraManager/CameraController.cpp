#include "CameraController.h"
#include "../RenderComponent/RenderComponentPositional.h"

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
	processRelativeMotion(e.state.X.rel,e.state.Y.rel,e.state.Z.rel);
}

void CameraController::processRelativeMotion(double xRel,double yRel,double zRel)
{

}

void CameraController::processSimpleTranslation(int movementFlags)
{

}

void CameraController::setTarget(RenderComponentPositional * target)
{

}
TCameraControllerType CameraController::getControllerType()
{
	return OUAN::CAMERA_NONE;
}