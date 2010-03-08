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

		void init(RootPtr pRoot,Ogre::SceneManager * pSceneManager);

		/// Free resources
		void cleanUp();

		Ogre::Camera *  createCamera(std::string name,TRenderComponentCameraParameters tRenderComponentCameraParameters);

		void clear();

		void setActiveCamera(std::string name);
		std::string getActiveCameraName();

		Ogre::Camera * getActiveCamera();

		void setCameraType(TCameraControllerType cameraControllerType);

		void resetActiveCameraPosition();

		void update(long elapsedTime);


		void processMouseInput(const OIS::MouseEvent &e);
		void processRelativeMotion(double xRel,double yRel,double zRel);
		void processSimpleTranslation(Ogre::Vector3 unitTranslationVector);

		/// Return read-only pointer to the viewport
		/// @return viewport
		Ogre::Viewport* getViewport() const;

		/// Activates next camera
		void changeCamera();
		/// Activates next camera controller type
		void changeCameraController();

		//Sets camera target
		void setCameraTarget(RenderComponentPositional * target);

		TCameraControllerType getControllerType();
	private:
		/// Scene manager
		Ogre::SceneManager* mSceneManager;
		/// Viewport
		Ogre::Viewport* mViewport;


		TCameraParamsContainer mCameraInitialParams;

		CameraController * activeCameraController;
		CameraControllerFirstPerson * mCameraControllerFirstPerson;
		CameraControllerThirdPerson * mCameraControllerThirdPerson;
		CameraControllerFixedThirdPerson * mCameraControllerFixedThirdPerson;

		//CameraControllerFixedFirstPerson * mCameraControllerFixedFirstPerson;
		//CameraControllerTrajectory * mCameraControllerTrajectory;

		void setCameraParameters(Ogre::Camera * pCamera,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		
	};
}

#endif