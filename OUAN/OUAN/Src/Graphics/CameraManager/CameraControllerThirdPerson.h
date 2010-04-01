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

		bool calculateCameraCollisions(Ogre::Vector3 & cameraPosition, Ogre::Vector3 & cameraLookAt);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

		TCameraControllerType getControllerType();
	private:
		Ogre::SceneManager * mSceneManager;
		RayCasting * mRayCasting;
		RenderComponentPositional * target;

		Ogre::Vector3 initialDirection;
		double initialDistance;
		double height;

		double collisionMargin;

		double currentCollisionTime;
		double minCollisionTime;

		double minDistance;

		double collisionDisplacementDistance;

		//camera relative rotation to target's X axe
		double rotX;
		//camera relative rotation to target's Y axe
		double rotY;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//camera position speed
		double speed;
		double collisionMoveSpeed;

		//camera speed when it returns to initial position
		double returningspeed;

		//in order to determine if target has moved
		Vector3 lastTargetPosition;
		Quaternion lastTargetOrientation;
		bool cameraIsReturning;

		//true if camera has been moved this frame
		bool cameraMoved;

		double rotXDistanceAttenuationNegative;
		double rotXDistanceAttenuationPositive;

		void returningToInitialPosition();

		double calculateNextMovementTo(Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,Ogre::Vector3 & newNextMovePosition,double elapsedTime);
		

	};
}

#endif