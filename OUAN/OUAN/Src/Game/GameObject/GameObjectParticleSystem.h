#ifndef GameObjectParticleSystemH_H
#define GameObjectParticleSystemH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectParticleSystem : public GameObject, public boost::enable_shared_from_this<GameObjectParticleSystem>
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentParticleSystemPtr mRenderComponentParticleSystem;
		/// Holds information related to the object's position in space
		RenderComponentPositionalPtr mRenderComponentPositional;

	public:
		//Constructor
		GameObjectParticleSystem(const std::string& name);
		//Destructor
		~GameObjectParticleSystem();

		/// Get light component
		/// @return light component
		RenderComponentParticleSystemPtr getRenderComponentParticleSystem() const;

		/// Set light component
		/// @param pRenderComponentLight the light component to set
		void setRenderComponentParticleSystem(RenderComponentParticleSystemPtr pRenderComponentParticleSystem);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

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
	/// to the ParticleSystem object
	class TGameObjectParticleSystemParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectParticleSystemParameters();
		/// Default destructor
		~TGameObjectParticleSystemParameters();

		/// Light-specific parameters
		TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};
}
#endif