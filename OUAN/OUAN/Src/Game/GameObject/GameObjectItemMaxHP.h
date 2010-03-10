#ifndef GameObjectItemMaxHPH_H
#define GameObjectItemMaxHPH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../../Logic/LogicComponent/LogicComponentWorldExistance.h"

namespace OUAN
{
	/// Class to hold MaxHP information
	class GameObjectItemMaxHP : public GameObject, public boost::enable_shared_from_this<GameObjectItemMaxHP>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleCapsulePtr mPhysicsComponentSimpleCapsule;
		/// World Existance informacion
		LogicComponentWorldExistancePtr mLogicComponentWorldExistance;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectItemMaxHP(const std::string& name);
		//Destructor
		~GameObjectItemMaxHP();
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
		
		/// Set WorldExistence component
		void setLogicComponentWorldExistance(LogicComponentWorldExistancePtr pLogicComponentWorldExistance);

		/// Get WorldExistence component
		LogicComponentWorldExistancePtr getLogicComponentWorldExistance();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);
	};

	class TGameObjectItemMaxHPParameters: public TGameObjectParameters
	{
	public:
		TGameObjectItemMaxHPParameters();
		~TGameObjectItemMaxHPParameters();
		
		bool existsInDreams;
		bool existsInNightmares;

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters;

		///World Existance Information
		TLogicComponentWorldExistanceParameters tLogicComponentWorldExistanceParameters;
	};
}
#endif