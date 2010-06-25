#ifndef CameraControllerH_H
#define CameraControllerH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		virtual void init(Ogre::SceneManager * pSceneManager);
		virtual void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		virtual void loadInfo();
		virtual TCameraControllerType getControllerType();
		virtual Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds);
		virtual void setCameraParameters(Ogre::Camera *pCamera,CameraInputPtr pCameraInput);
		virtual void centerCamera(Ogre::Camera *pCamera,CameraInputPtr pCameraInput);
		virtual void clear();
	protected:

		double calculateDistanceToTarget(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,bool twoDimensions);

	};
}

#endif