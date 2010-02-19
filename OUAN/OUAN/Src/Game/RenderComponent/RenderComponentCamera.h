#ifndef RenderComponentCameraH_H
#define RenderComponentCameraH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentCamera: public RenderComponent
	{
	private:
		Ogre::Camera * mCamera;
	public:

		RenderComponentCamera(const std::string& name="");
		~RenderComponentCamera();

		Ogre::Camera * getCamera() const;
		void setCamera(Ogre::Camera *);

	};
}

#endif