#ifndef GameObjectCameraH_H
#define GameObjectCameraH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentCamera.h"

namespace OUAN
{
	/// Models a Camera source object
	class GameObjectCamera : public GameObject
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentCameraPtr mRenderComponentCamera;

	public:
		//Constructor
		GameObjectCamera(const std::string& name);
		//Destructor
		~GameObjectCamera();

		/// Get Camera component
		/// @return Camera component
		RenderComponentCameraPtr getRenderComponentCamera() const;

		/// Set Camera component
		/// @param pRenderComponentCamera the Camera component to set
		void setRenderComponentCamera(RenderComponentCameraPtr pRenderComponentCamera);

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
	};

	/// Transport object carrying around data from the level loader
	/// to the Camera object
	class TGameObjectCameraParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectCameraParameters();
		/// Default destructor
		~TGameObjectCameraParameters();

		/// Camera-specific parameters
		TRenderComponentCameraParameters tRenderComponentCameraParameters;

	};
}
#endif