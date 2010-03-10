#ifndef GameObjectBillboardSetH_H
#define GameObjectBillboardSetH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentBillboardSet.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectBillboardSet : public GameObject, public boost::enable_shared_from_this<GameObjectBillboardSet>
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentBillboardSetPtr mRenderComponentBillboardSet;
		/// Holds information related to the object's position in space
		RenderComponentPositionalPtr mRenderComponentPositional;

	public:
		//Constructor
		GameObjectBillboardSet(const std::string& name);
		//Destructor
		~GameObjectBillboardSet();

		/// Get billboardset component
		/// @return billboardset component
		RenderComponentBillboardSetPtr getRenderComponentBillboardSet() const;

		/// Set billboardset component
		/// @param pRenderComponentLight the billboardset component to set
		void setRenderComponentBillboardSet(RenderComponentBillboardSetPtr pRenderComponentBillboardSet);

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
	/// to the BillboardSet object
	class TGameObjectBillboardSetParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBillboardSetParameters();
		/// Default destructor
		~TGameObjectBillboardSetParameters();

		/// billboardset-specific parameters
		TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};
}
#endif