#ifndef RenderComponentCameraH_H
#define RenderComponentCameraH_H

#include "RenderComponent.h"

namespace OUAN
{
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

	class RenderComponentCamera: public RenderComponent
	{
	private:
		Ogre::Camera * mCamera;
		TRenderComponentCameraParameters initialParameters;
	public:

		RenderComponentCamera(const std::string& type="");
		~RenderComponentCamera();

		Ogre::Camera * getCamera() const;
		void setCamera(Ogre::Camera *);

		void setCameraParameters(TRenderComponentCameraParameters tRenderComponentCameraParameters);
		void resetCameraParameters();
	};


}

#endif