#ifndef GameObjectTripolloDreamsH_H
#define GameObjectTripolloDreamsH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	const std::string TRIPOLLO_STATE_IDLE="TRIPOLLO_STATE_IDLE";
	const std::string TRIPOLLO_STATE_PATROL="TRIPOLLO_STATE_PATROL";
	const std::string TRIPOLLO_STATE_CHASE="TRIPOLLO_STATE_CHASE";
	const std::string TRIPOLLO_STATE_FLEE="TRIPOLLO_STATE_FLEE";

	/// Class modelling a particular enemy type
	class GameObjectTripolloDreams : public GameObject, public boost::enable_shared_from_this<GameObjectTripolloDreams>
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Positional component
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		/// Trajectory information
		TrajectoryComponentPtr mTrajectoryComponent;

		// TODO: Delete this!
		int mRandomMovementDelay;
		bool pathfindingInitialized;

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectTripolloDreams(const std::string& name);

		//Destructor
		~GameObjectTripolloDreams();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

		/// Set trajectory component
		/// @param pTrajectoryComponent
		void setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent);
		TrajectoryComponentPtr getTrajectoryComponent();

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Set initial component
		void setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		/// Update object
		virtual void update(double elapsedSeconds);
		
		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		/// Reset object
		virtual void reset();

		//-- Methods used by GameWorldManager or GameObject to implement global query methods used by LUA
		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectTripolloDreams"
	class TGameObjectTripolloDreamsParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectTripolloDreamsParameters();
		/// Default destructor
		~TGameObjectTripolloDreamsParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;
	};

}
#endif