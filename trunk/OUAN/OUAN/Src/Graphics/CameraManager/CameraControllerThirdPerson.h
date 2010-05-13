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

		void init(RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting);

		void update(double elapsedTime);
		void processCameraRotation(Ogre::Vector2 cameraRotation);

		void setTarget(RenderComponentPositionalPtr target);

		void resetPosition();

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

		TCameraControllerType getControllerType();
	private:
		Ogre::SceneManager * mSceneManager;
		RayCastingPtr mRayCasting;
		RenderComponentPositionalPtr target;

		Ogre::Vector3 initialDirection;
		double maxDistance;
		double currentDistance;
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

		double lastRotX;
		double lastRotY;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//camera position speed
		double speedX;
		double speedY;
		double collisionMoveSpeed;
		double collisionReturningSpeed;
		double autoRotXPositiveSpeed;
		double autoRotXNegativeSpeed;
		double autoRotXCenterSpeed;
		double minAutoRotX;
		double maxAutoRotX;
		double autoRotYSpeed;
		double maxYMovementPerFrame;
		double minCameraCenterRotX;
		double maxCameraCenterRotX;

		//transparent collision objects
		TransparentEntityManagerPtr mTransparentEntityManager;

		//camera speed when it returns to initial position
		double returningspeed;

		//in order to determine if target has moved
		Vector3 lastTargetPosition;
		Quaternion lastTargetOrientation;

		//true if camera has been moved this frame
		bool cameraMoved;

		//true if camera has been corrected last frame
		bool mCorrectingCameraPosition;

		double rotXDistanceAttenuationNegative;
		double rotXDistanceAttenuationPositive;

		void reset();
		bool loadConfig();

		Ogre::Vector3 calculateCameraPosition(double distance,bool y_correction=true);
		Ogre::Vector3 calculateCameraLookAt();


		bool calculateCameraCollisions(Ogre::Vector3 & cameraPosition, Ogre::Vector3 & cameraLookAt,Ogre::uint32 & collisionType);

		double calculateCameraMoveToTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime);
		double calculateCameraReturningFromTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime);

		void calculateCollisionRotXNegative(double elapsedTime);
		void calculateCollisionRotXPositive(double elapsedTime);

		void rotateX(double rotation);
		void rotateY(double rotation);

	};
}

#endif