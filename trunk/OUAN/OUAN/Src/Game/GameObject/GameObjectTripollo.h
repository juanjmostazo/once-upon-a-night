#ifndef GameObjectTripolloH_H
#define GameObjectTripolloH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Class modelling a particular enemy type
	class GameObjectTripollo : public GameObject
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Positional component
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectTripollo(const std::string& name);

		//Destructor
		~GameObjectTripollo();

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

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectTripollo"
	class TGameObjectTripolloParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectTripolloParameters();
		/// Default destructor
		~TGameObjectTripolloParameters();

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