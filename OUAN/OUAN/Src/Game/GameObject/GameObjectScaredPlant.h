#ifndef GameObjectScaredPlantH_H
#define GameObjectScaredPlantH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Class to hold ScaredPlant information
	class GameObjectScaredPlant : public GameObject, public boost::enable_shared_from_this<GameObjectScaredPlant>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectScaredPlant(const std::string& name);
		//Destructor
		~GameObjectScaredPlant();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		/// Update object
		virtual void update(double elapsedSeconds);

		/// React to a world change to the given one
		/// @param world world to change to
		void changeWorld(int world);

		/// Attach all event handlers for this class.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		void registerHandlers();
		/// Detach all event handlers.
		// This method will have to be redefined by all GameObject subclasses to unregister all the event handlers
		void unregisterHandlers();
		
		//------------------------------------------------------------------
	};

	class TGameObjectScaredPlantParameters: public TGameObjectParameters
	{
	public:
		TGameObjectScaredPlantParameters();
		~TGameObjectScaredPlantParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;
	};
}
#endif