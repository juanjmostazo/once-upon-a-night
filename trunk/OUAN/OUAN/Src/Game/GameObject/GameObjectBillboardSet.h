#ifndef GameObjectBillboardSetH_H
#define GameObjectBillboardSetH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentBillboardSet.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectBillboardSet : public GameObject
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentBillboardSetPtr mRenderComponentBillboardSet;
		/// Holds information related to the object's position in space
		RenderComponentPositionalPtr mRenderComponentPositional;

	public:
		//Constructor
		GameObjectBillboardSet(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectBillboardSet();

		/// Get light component
		/// @return light component
		RenderComponentBillboardSetPtr getRenderComponentBillboardSet() const;

		/// Set light component
		/// @param pRenderComponentLight the light component to set
		void setRenderComponentBillboardSet(RenderComponentBillboardSetPtr pRenderComponentBillboardSet);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;


	};

	/// Transport object carrying around data from the level loader
	/// to the BillboardSet object
	class TGameObjectBillboardSetParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBillboardSetParameters();
		/// Default destructor
		~TGameObjectBillboardSetParameters();

		/// Light-specific parameters
		TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};
}
#endif