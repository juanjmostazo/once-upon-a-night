#ifndef GameObjectLightH_H
#define GameObjectLightH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectLight : public GameObject, public boost::enable_shared_from_this<GameObjectLight>
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentLightPtr mRenderComponentLight;
		/// Holds information related to the object's position in space
		RenderComponentPositionalPtr mRenderComponentPositional;

	public:
		//Constructor
		GameObjectLight(const std::string& name);
		//Destructor
		~GameObjectLight();

		/// Get light component
		/// @return light component
		RenderComponentLightPtr getRenderComponentLight() const;

		/// Set light component
		/// @param pRenderComponentLight the light component to set
		void setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);
	};

	/// Transport object carrying around data from the level loader
	/// to the light object
	class TGameObjectLightParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectLightParameters();
		/// Default destructor
		~TGameObjectLightParameters();

		/// Light-specific parameters
		TRenderComponentLightParameters tRenderComponentLightParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};
}
#endif