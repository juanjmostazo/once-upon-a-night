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

		virtual void setCamera(Ogre::Camera * pCamera);

		Ogre::Camera * getCamera();

		virtual void update(long elapsedTime);
		virtual void processMouseInput(const OIS::MouseEvent &e);
		virtual void processRelativeMotion(double xRel,double yRel);
		virtual void processSimpleTranslation(Ogre::Vector3 translationVector);

	protected:
		Ogre::Camera *mCamera;
	};
}

#endif