#ifndef CameraControllerFixedThirdPersonH_H
#define CameraControllerFixedThirdPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFixedThirdPerson : public CameraController
	{
	public:
		CameraControllerFixedThirdPerson();
		~CameraControllerFixedThirdPerson();

		void update(double elapsedTime);
		void setTarget(RenderComponentPositional * target);
		void setCamera(Ogre::Camera * pCamera);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

		TCameraControllerType getControllerType();

		void calculateRotY();
	private:


		RenderComponentPositional * target;
		double rotY;
		double height;
	};
}

#endif