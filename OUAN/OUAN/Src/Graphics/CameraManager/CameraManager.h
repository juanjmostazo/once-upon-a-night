#ifndef CameraManagerH_H
#define CameraManagerH_H
#include "../../OUAN.h"
#include "../../Event/EventDefs.h"
namespace OUAN
{
	class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		/// Init resources
		void init(RenderSubsystemPtr pRenderSubsystem,TrajectoryManagerPtr pTrajectoryManager,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting, GameWorldManagerPtr pGameWorldManager);

		/// Free resources
		void cleanUp();

		/// Return read-only pointer to the camera
		/// @return camera
		Ogre::Camera * getCamera() const;
		/// Return read-only pointer to the viewport
		/// @return viewport
		Ogre::Viewport* getViewport() const;

		//Set camera controller type
		void setCameraType(TCameraControllerType cameraControllerType);
		//Returns camera controller type
		TCameraControllerType getCameraControllerType() const;

		void update(double elapsedTime);

		void processMouseInput(const OIS::MouseEvent &e);
		void processCameraRotation(Ogre::Vector2 rotation);
		void processSimpleTranslation(Ogre::Vector3 translation);

		/// Activates next camera controller type
		void changeCameraController();

		//Sets camera target for applicable controllers
		void setCameraTarget(PhysicsComponentCharacterPtr pTarget);

		//Sets camera trajectory for trajectory controller
		void setCameraTrajectory(std::string name);

		Ogre::Viewport* setViewportParameters(Ogre::String name,TRenderComponentViewportParameters tRenderComponentViewportParameters);

		//register/unregister
		void registerEventHandlers(EventManagerPtr evtMgr);
		void unregisterEventHandlers(EventManagerPtr evtMgr);

		//event handlers
		void processChangeWorld(ChangeWorldEventPtr evt);

		void setCameraParameters(CameraParametersPtr pCameraParameters,bool transition);
		void setDefaultCameraParameters(bool transition);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

	private:
		/// GameWorldManager
		GameWorldManagerPtr mGameWorldManager;
		/// GameWorldManager
		Ogre::SceneManager* mSceneManager;
		/// Viewport
		Ogre::Viewport* mViewport;
		/// Trajectory Manager
		TrajectoryManagerPtr mTrajectoryManager;

		//Creates main camera, which always exists
		void createMainCamera();

		Ogre::Camera * mCamera;

		CameraController * mActiveCameraController;
		CameraControllerFirstPerson * mCameraControllerFirstPerson;
		CameraControllerThirdPerson * mCameraControllerThirdPerson;
		CameraControllerFixedThirdPerson * mCameraControllerFixedThirdPerson;
		CameraControllerFixedFirstPerson * mCameraControllerFixedFirstPerson;
		CameraControllerTrajectory * mCameraControllerTrajectory;

		//Changeworld functions and variables
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void activateChangeWorld();
		void activateChangeWorldFast();

		double mChangeWorldTotalTime;
		double mChangeWorldElapsedTime;
		bool mIsChangingWorld;
		int mWorld;

		CameraInputPtr mCameraInput;

		PhysicsComponentCharacterPtr mTarget;

		
	};
}

#endif