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

		//virtual void setCamera(Ogre::Camera * pCamera);

		Ogre::Camera * getCamera();

		virtual void update(long elapsedTime);

		//TODO: change keyboard to FullInputManager
		virtual void processInput(OIS::Keyboard *keyboard,long elapsedTime);

	protected:
		Ogre::Camera *mCamera;
	};
}

#endif