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
	mCamera=pSceneManager->createCamera(OUAN::MAIN_CAMERA_NAME);
}

//void CameraController::setCamera(Camera * pCamera)
//{
//	mCamera=pCamera;
//}
Camera * CameraController::getCamera()
{
	return mCamera;
}
void CameraController::update(long elapsedTime)
{

}

//TODO: change keyboard to FullInputManager
void CameraController::processInput(OIS::Keyboard *keyboard,long elapsedTime)
{

}