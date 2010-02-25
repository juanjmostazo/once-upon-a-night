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

	class TRenderComponentCameraParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentCameraParameters();
		~TRenderComponentCameraParameters();

		Vector3 position;
		Quaternion orientation;
		String autotracktarget;
		bool autoaspectratio;
		Vector2 clipdistance;
		Real FOVy;
		Ogre::PolygonMode polygonmode;
		int viewmode;
	};
}

#endif