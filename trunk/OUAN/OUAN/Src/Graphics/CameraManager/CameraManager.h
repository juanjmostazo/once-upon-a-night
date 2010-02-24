#ifndef CameraManagerH_H
#define CameraManagerH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void initialise(Ogre::SceneManager* pSceneManager,Ogre::Viewport* pViewport);

		/// Free resources
		void cleanUp();

		void createCamera(std::string name,TRenderComponentCameraParameters tRenderComponentCameraParameters);

		void clear();

		void setActiveCamera(std::string name);
		std::string getActiveCameraName();

		Ogre::Camera * getActiveCamera();

		void setCameraType(TCameraControllerType cameraControllerType);

		void resetActiveCameraPosition();

		void update(long elapsedTime);

		//TODO: change keyboard to FullInputManager
		void processInput(OIS::Keyboard *keyboard,long elapsedTime);

		CameraControllerFirstPerson * mCameraControllerFirstPerson;

	private:
		/// Scene manager
		Ogre::SceneManager* mSceneManager;
		Ogre::Viewport* mViewport;

		TCameraParamsContainer mCameraInitialParams;

		CameraControllerFirstPerson * activeCameraController;

		//CameraControllerThirdPerson * mCameraControllerThirdPerson;
		//CameraControllerFixedThirdPerson * mCameraControllerFixedThirdPerson;
		//CameraControllerFixedFirstPerson * mCameraControllerFixedFirstPerson;
		//CameraControllerTrajectory * mCameraControllerTrajectory;

		void setCameraParameters(Ogre::Camera * pCamera,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		
	};
}

#endif