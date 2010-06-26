#ifndef CameraControllerThirdPersonH_H
#define CameraControllerThirdPersonH_H
#include "CameraController.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Physics/PhysicsSubsystem.h"
#include "../RenderSubsystem.h"

namespace OUAN
{
	class CameraControllerThirdPerson : public CameraController
	{
	public:

		CameraControllerThirdPerson();
		~CameraControllerThirdPerson();

		void init(CameraInputPtr pCameraInput,Ogre::SceneManager * pSceneManager,RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,TrajectoryManagerPtr pTrajectoryManager,GameWorldManagerPtr pGameWorldManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds);
		void centerToTargetBack(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,bool transition);

		void setCameraTrajectory(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,std::string trajectory,bool lookAtTarget,bool transition);
		void setCameraFree(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,bool transition);
		void setCameraTracking(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,bool transition);
		void setCameraAutoRotation(double rotX,double rotY,bool transition);

		bool isTrajectoryFinished(const std::string& trajectoryName);

		CameraState getCameraState();

		void clear();
		void cleanUp();

		bool cameraTrajectoryEnded();

		void setRotationYToTargetBack(std::string cameraTarget);

	protected:
		Ogre::Vector3 calculateCameraPosition(Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		Ogre::Vector3 calculateTargetPosition(CameraInputPtr pCameraInput);
		Ogre::Vector3 calculateCameraPositionAtDistance(double distance,CameraInputPtr pCameraInput);

		void processCameraRotation(CameraInputPtr pCameraInput);
		Ogre::Vector3 resolveCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		Ogre::Vector3 processMoveCameraCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void processTransparentCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		
		Ogre::Vector3 calculateDirection(Ogre::Vector3 v1,Ogre::Vector3 v2);

		void rotateX(double rotation);
		void rotateY(double rotation);

		//minimum and maximum rotation to target's X axe
		double mMinRotX;
		double mMaxRotX;

		//camera position speed
		double mRotationSpeedX;
		double mRotationSpeedY;

		//camera relative rotation to target's X axe
		double mRotX;
		//camera relative rotation to target's Y axe
		double mRotY;

		double mMinDistance;
		double mCurrentDistance;

		double mCollisionOffsetX;
		double mCollisionOffsetY;

		CameraState mCameraState;

		void setCameraMoveToPosition(Ogre::Vector3 position1,Ogre::Quaternion rotation1,Ogre::Vector3 position2,Ogre::Quaternion rotation2,double targetSpeed,CameraState targetState);
		void setCameraMoveToTarget(Ogre::Vector3 position1,Ogre::Quaternion rotation1,CameraInputPtr pTargetInput,double targetSpeed,CameraState targetState);
		void setCameraMoveToPositionLookingAtTarget(Ogre::Vector3 position1,Ogre::Quaternion rotation1,Ogre::Vector3 position2,CameraInputPtr pTargetInput,double targetSpeed,CameraState targetState);

		void updateCameraAutoRotation(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraTrajectory(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraMoveToPosition(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraMoveToTarget(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraMoveToPositionLookingAtTarget(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraFree(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		void updateCameraTracking(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput);

		//autorotation atibutes
		double mTargetRotX;
		double mTargetRotY;
		double mInitRotX;
		double mInitRotY;
		double mAutoRotationSpeedX;
		double mAutoRotationSpeedY;
		double mAutoRotationDirectionX;
		double mAutoRotationDirectionY;
		double mAutoRotationDampenFactor;
		double mAutoRotationDampenStart;
		double mAutoRotationDampenPow;

		//trajectory atributes
		Trajectory * mTrajectory;
		Ogre::SceneNode * mDummyNode;
		bool mTrajectoryLookAtTarget;

		//move to position attributes
		Quaternion mTransitionInitialRotation;
		Quaternion mTransitionTargetRotation;
		Vector3 mTransitionInitialPosition;
		Vector3 mTransitionTargetPosition;
		double mTransitionSpeedFactor;
		double mTransitionSpeed;
		double mTransitionTargetSpeed;
		double mTransitionDampenFactor;
		double mTransitionDampenStart;
		double mTransitionDampenPow;
		CameraState mTargetState;

		//move to target
		CameraInputPtr mTransitionTargetInput;
		Ogre::Camera * mTransitionDummyCamera;

		//camera returning
		double mReturningSpeed;
		double mReturningDampenFactor;
		double mReturningDampenStart;
		double mReturningDampenPow;
		bool mHasCollisioned;

		void defaultUpdateCamera(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		double calculateDampenFactor(double perc,double dampenFactor, double dampenPow, double dampenStart);
		void startTrajectory(std::string trajectory,Ogre::Camera * pCamera);
		void updateCurrentDistance(CameraInputPtr pCameraInput,double elapsedTime);
		double calculateTransitionSpeed(Ogre::Vector3 initialPosition,Ogre::Vector3 targetPosition);
		double calculateRotationDistance(double angle1, double angle2);

		RayCasting * mRayCasting;
		TrajectoryManagerPtr mTrajectoryManager;
		Ogre::SceneManager * mSceneManager;
		TransparentEntityManagerPtr mTransparentEntityManager;
		GameWorldManagerPtr mGameWorldManager;
	};
}

#endif