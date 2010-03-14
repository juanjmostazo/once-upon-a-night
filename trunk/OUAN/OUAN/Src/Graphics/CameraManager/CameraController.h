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

		virtual void update(double elapsedTime);
		virtual void processMouseInput(const OIS::MouseEvent &e);
		virtual void processRelativeMotion(double xRel,double yRel,double zRel);
		virtual void processSimpleTranslation(int movementFlags);
		virtual void setTarget(RenderComponentPositional * target);

	protected:
		Ogre::Camera *mCamera;
	};
}

#endif