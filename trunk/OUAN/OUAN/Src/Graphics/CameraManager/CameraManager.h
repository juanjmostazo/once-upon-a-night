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

		void setCameraTrajectory(std::string trajectory,bool transition);
		void setCameraFree(bool transition);
		void setCameraTracking(CameraParametersPtr cameraParameters,bool transition);


		/// Activates next camera controller type
		void changeCameraController();

		/// Activates trajectory/fixed camera
		void changeAutoCamera();

		//Sets camera target for applicable controllers
		void setCameraTarget(RenderComponentPositionalPtr pTarget);

		Ogre::Viewport* setViewportParameters(Ogre::String name,TRenderComponentViewportParameters tRenderComponentViewportParameters);

		//register/unregister
		void registerEventHandlers(EventManagerPtr evtMgr);
		void unregisterEventHandlers(EventManagerPtr evtMgr);

		//event handlers
		void processChangeWorld(ChangeWorldEventPtr evt);

		void setCameraParameters(CameraParametersPtr pCameraParameters,bool transition);
		void setDefaultCameraParameters(bool transition);

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement,double elapsedSeconds);

		void centerCamera();

		void setCameraTrajectoryNames(std::vector<std::string> trajectoryNames);

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
		CameraParametersPtr mDefaultCameraParameters;

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
		
	};
}

#endif