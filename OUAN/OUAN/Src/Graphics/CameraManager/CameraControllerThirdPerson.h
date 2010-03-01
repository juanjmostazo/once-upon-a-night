#ifndef CameraControllerThirdPersonH_H
#define CameraControllerThirdPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerThirdPerson : public CameraController
	{
	public:
		CameraControllerThirdPerson();
		~CameraControllerThirdPerson();

		void update(long elapsedTime);
		void processMouseInput(const OIS::MouseEvent &e);
		void processRelativeMotion(double xRel,double yRel,double zRel);

		void setTarget(Ogre::SceneNode * target);

		TCameraControllerType getControllerType();
	private:
		Ogre::SceneNode * target;

	};
}

#endif