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
		//reset
		void clear();

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

		//CAMERA MODIFIERS
		//Transition activates or desactivates transitions between cameras
		//CameraParameters is a class that specifies camera parameters, check it out

		//Sets specified trajectory, lookAtTarget=true to ignore original trajectory orientation and look at target instead
		void setCameraTrajectory(CameraParametersPtr cameraParameters,std::string trajectory,bool lookAtTarget,bool transition);
		//true if trajectory ended
		bool cameraTrajectoryEnded();
		//Sets free camera, which processes input
		void setCameraFree(CameraParametersPtr cameraParameters,bool transition);
		//Sets tracking camera, like free but without processing input
		void setCameraTracking(CameraParametersPtr cameraParameters,bool transition);
		//Sets default camera
		void setDefaultThirdPersonCamera(bool transition);
		//Sets camera fixed first person
		void setCameraFixedFirstPerson(bool transition);

		//Note: those last two doesnt work for trajectory camera
		//Auto-rotates camera to selected rotation
		void setCameraAutoRotation(double rotX,double rotY,bool transition);
		//Auto-rotates camera to target's back
		void centerToTargetBack(bool transition);

		/// Activates next camera controller type
		void changeCameraController();

		/// Activates trajectory/fixed camera
		void changeAutoCamera();

		Ogre::Viewport* setViewportParameters(Ogre::String name,TRenderComponentViewportParameters tRenderComponentViewportParameters);

		//register/unregister
		void registerEventHandlers(EventManagerPtr evtMgr);
		void unregisterEventHandlers(EventManagerPtr evtMgr);

		//event handlers
		void processChangeWorld(ChangeWorldEventPtr evt);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement,double elapsedSeconds);

		void setCameraTrajectoryNames(std::vector<std::string> trajectoryNames);

		void setLastTrigger(std::string lastTrigger);
		std::string getLastTrigger() const;

		//LUA exports
		static void setTrajectoryCamera(const std::string& camName);
		static bool isCameraTrajectoryEnded();
		static void setAnyTrackingCamera();

	private:

		//void setCameraTrajectory(std::string name);

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

		std::vector<std::string> mCameraTrajectoryNames;
		unsigned int mCurrentTrajectory;

		std::string mLastTrigger;

		static CameraManager* mInst;
		
	};
}

#endif