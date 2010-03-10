#ifndef GameObjectCameraH_H
#define GameObjectCameraH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentCamera.h"

namespace OUAN
{
	/// Models a Camera source object
	class GameObjectCamera : public GameObject, public boost::enable_shared_from_this<GameObjectCamera>
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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);
		
		/// Attach all event handlers for this class.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		void registerHandlers();
		/// Detach all event handlers.
		// This method will have to be redefined by all GameObject subclasses to unregister all the event handlers
		void unregisterHandlers();

		//Event handler methods
		void processChangeWorld(ChangeWorldEventPtr evt);
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