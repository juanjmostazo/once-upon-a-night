#ifndef GameObjectDragonH_H
#define GameObjectDragonH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Class modelling a particular enemy type
	class GameObjectDragon : public GameObject, public boost::enable_shared_from_this<GameObjectDragon>
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

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectDragon(const std::string& name);

		//Destructor
		~GameObjectDragon();

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

		/// Reset object
		virtual void reset();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		int getTimeStunned() const;

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectDragon"
	class TGameObjectDragonParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectDragonParameters();
		/// Default destructor
		~TGameObjectDragonParameters();

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