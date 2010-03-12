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

		//camera relative rotation to X axe
		double rotX;
		//camera relative rotation to Y axe
		double rotY;

		//camera position speed
		double speed;
		//camera rotation speed
		double rotationSpeed;

		Vector3 newTranslation;
	};
}

#endif