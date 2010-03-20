#ifndef GameObjectBee_ButterflyH_H
#define GameObjectBee_ButterflyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Class modelling a particular enemy type
	class GameObjectBee_Butterfly : public GameObject, public boost::enable_shared_from_this<GameObjectBee_Butterfly>
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Positional component
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacterDreams;
		PhysicsComponentCharacterPtr mPhysicsComponentCharacterNightmares;
	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectBee_Butterfly(const std::string& name);

		//Destructor
		~GameObjectBee_Butterfly();

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
		void setPhysicsComponentCharacterDreams(PhysicsComponentCharacterPtr pPhysicsComponentCharacterDreams);
		void setPhysicsComponentCharacterNightmares(PhysicsComponentCharacterPtr pPhysicsComponentCharacterNightmares);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacterDreams();
		PhysicsComponentCharacterPtr getPhysicsComponentCharacterNightmares();

		/// Update object
		virtual void update(double elapsedSeconds);

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectBee_Butterfly"
	class TGameObjectBee_ButterflyParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBee_ButterflyParameters();
		/// Default destructor
		~TGameObjectBee_ButterflyParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterDreamsParameters;
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterNightmaresParameters;
	};

}
#endif