#ifndef CameraControllerFirstPersonH_H
#define CameraControllerFirstPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFirstPerson : public CameraController
	{
	public:
		CameraControllerFirstPerson();
		~CameraControllerFirstPerson();

		TCameraControllerType getControllerType();

		void update(long elapsedTime);
		void processRelativeMotion(double xRel,double yRel,double zRel);

		void processSimpleTranslation(int movementFlags);
		void setCamera(Ogre::Camera * pCamera);

	private:

		//camera relative rotation to target's X axe
		double rotX;
		//camera relative rotation to target's Y axe
		double rotY;

		//camera position speed
		double speed;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//minimum and maximum rotation to target's Y axe
		double minRotY;
		double maxRotY;

		//camera height in relation to target
		double height;

		Vector3 newTranslation;
	};
}

#endif