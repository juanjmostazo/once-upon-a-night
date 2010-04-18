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
		void setTarget(RenderComponentPositionalPtr target);
		void setCamera(Ogre::Camera * pCamera);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

		TCameraControllerType getControllerType();

		void calculateRotY();
	private:


		RenderComponentPositionalPtr target;
		double rotY;
		double height;
	};
}

#endif