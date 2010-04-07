#ifndef GameObjectParticleSystemH_H
#define GameObjectParticleSystemH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
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
		RenderComponentInitialPtr mRenderComponentInitial;
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

		/// Set initial component
		void setRenderComponentInitialFromPositional();

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		void changeWorld(int world);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;
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