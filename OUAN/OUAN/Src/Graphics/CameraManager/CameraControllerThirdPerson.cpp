#include "CameraControllerThirdPerson.h"

using namespace OUAN;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{
}

void CameraControllerThirdPerson::update(long elapsedTime)
{
	mCamera->lookAt(target->getPosition());
}
void CameraControllerThirdPerson::processMouseInput(const OIS::MouseEvent &e)
{
	
}
void CameraControllerThirdPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{

}
void CameraControllerThirdPerson::setTarget(Ogre::SceneNode * target)
{
	this->target=target;
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}
