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

		void init(Ogre::SceneManager * pSceneManager);

		void update(double elapsedTime);
		void processCameraRotation(Ogre::Vector2 cameraRotation);

		void setTarget(RenderComponentPositional * target);

		Ogre::Vector3 calculateCameraCollisions(Ogre::Vector3 currentCameraPosition, Ogre::Vector3 currentCameraLookAt);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

		TCameraControllerType getControllerType();
	private:
		Ogre::SceneManager * mSceneManager;
		RayCasting * mRayCasting;
		RenderComponentPositional * target;
		Vector3 distance;
		Vector3 initialDistance;
		double height;

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
		Vector3 lastTargetPosition;
		Quaternion lastTargetOrientation;
		bool cameraIsReturning;

		//true if camera has been moved this frame
		bool cameraMoved;

		double rotXDistanceAttenuation;

		void returningToInitialPosition();
		

	};
}

#endif