#ifndef GameObjectProvisionalEntityH_H
#define GameObjectProvisionalEntityH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"

namespace OUAN
{
	/// Class to hold ProvisionalEntity information
	class GameObjectProvisionalEntity : public GameObject, public boost::enable_shared_from_this<GameObjectProvisionalEntity>
	{
	private:
		
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;


		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectProvisionalEntity(const std::string& name);
		//Destructor
		~GameObjectProvisionalEntity();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;


		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		//------------------------------------------------------------------
		//Event handler methods
		void processChangeWorld(ChangeWorldEventPtr evt);

		/// Attach all event handlers for this class.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		void registerHandlers();
		/// Detach all event handlers.
		// This method will have to be redefined by all GameObject subclasses to unregister all the event handlers
		void unregisterHandlers();
	};

	class TGameObjectProvisionalEntityParameters: public TGameObjectParameters
	{
	public:
		TGameObjectProvisionalEntityParameters();
		~TGameObjectProvisionalEntityParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	};
}
#endif