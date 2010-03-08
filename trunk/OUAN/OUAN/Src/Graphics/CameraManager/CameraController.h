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
		virtual TCameraControllerType getControllerType();

		Ogre::Camera * getCamera();

		virtual void update(long elapsedTime);
		virtual void processMouseInput(const OIS::MouseEvent &e);
		virtual void processRelativeMotion(double xRel,double yRel,double zRel);
		virtual void processSimpleTranslation(Ogre::Vector3 translationVector);
		virtual void setTarget(RenderComponentPositional * target);

	protected:
		Ogre::Camera *mCamera;
	};
}

#endif