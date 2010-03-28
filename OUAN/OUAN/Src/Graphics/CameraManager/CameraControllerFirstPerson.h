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

		void update(double elapsedTime);
		void processCameraRotation(Ogre::Vector2 cameraRotation);

		void processSimpleTranslation(Ogre::Vector3 nextMovement);
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