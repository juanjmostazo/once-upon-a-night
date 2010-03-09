#ifndef GameObjectItem1UPH_H
#define GameObjectItem1UPH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"

namespace OUAN
{
	/// Class to hold Item1UP information
	class GameObjectItem1UP : public GameObject, public boost::enable_shared_from_this<GameObjectItem1UP>
	{
	private:
		
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleCapsulePtr mPhysicsComponentSimpleCapsule;


		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectItem1UP(const std::string& name);
		//Destructor
		~GameObjectItem1UP();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Set physics component
		void setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule);

		/// Get physics component
		PhysicsComponentSimpleCapsulePtr getPhysicsComponentSimpleCapsule();

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

	class TGameObjectItem1UPParameters: public TGameObjectParameters
	{
	public:
		TGameObjectItem1UPParameters();
		~TGameObjectItem1UPParameters();

		bool existsInDreams;
		bool existsInNightmares;
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters;

	};
}
#endif