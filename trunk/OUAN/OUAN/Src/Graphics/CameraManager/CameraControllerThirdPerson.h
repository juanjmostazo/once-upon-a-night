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
		void processRelativeMotion(double xRel,double yRel,double zRel);

		void setTarget(Ogre::SceneNode * target);

		TCameraControllerType getControllerType();
	private:
		Ogre::SceneNode * target;
		Ogre::Vector3 distance;

		//camera relative rotation to target's X axe
		double rotX;
		//camera relative rotation to target's Y axe
		double rotY;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//camera position speed
		double speed;

		//camera speed when it returns to initial position
		double returningspeed;

		//in order to determine if target has moved
		Ogre::Vector3 lastTargetPosition;

		//true if camera has been moved this frame
		bool cameraMoved;

		void returningToInitialPosition();


	};
}

#endif