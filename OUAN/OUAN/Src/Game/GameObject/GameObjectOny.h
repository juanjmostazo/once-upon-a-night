#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{

	const int STATE_ONY_IDLE=0;
	const int STATE_ONY_WALKS=1;
	const int STATE_ONY_JUMPS=2;
	const int STATE_ONY_TAKES_HIT=3;
	const int STATE_ONY_PILLOW_DRAW=4;
	const int STATE_ONY_PILLOW_ATTACK=5;
	const int STATE_ONY_PILLOW_ATTACK_SPECIAL=6;
	const int STATE_ONY_PILLOW_HIDE=7;
	const int STATE_ONY_FLASHLIGHT_DRAW=8;
	const int STATE_ONY_FLASHLIGHT_USE=9;
	const int STATE_ONY_FLASHLIGHT_HIDE=10;
	const int STATE_ONY_FLASHLIGHT_USE_SPECIAL=11;
		
	/// Main character game object
	class GameObjectOny : public GameObject, public boost::enable_shared_from_this<GameObjectOny>
	{
	private:
		
		/// Visual component data
		RenderComponentEntityPtr mRenderComponentEntity;

		/// Positional component data
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

		/// Health-related information (i.e, current HP and number of lives)
		//HealthComponentPtr mHealthComponent;
		
		/// Weapon wielding component
		//WeaponComponentPtr mWeaponComponent;

		/// 'Immunity' time so a single collision is not processed during several ticks
		int mHitRecoveryTime;

	public:
		//Constructor
		/// @param name	name of the object, specific to the class
		/// @param id	unique identifier of the instance
		GameObjectOny(const std::string& name);
		//Destructor
		~GameObjectOny();

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
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		/// Update object
		virtual void update(double elapsedSeconds);
		
		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		void decreaseHP(int amount=1);

	};

	/// Carries data between the level loader and the object factories
	class TGameObjectOnyParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectOnyParameters();
		/// Default destructor
		~TGameObjectOnyParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;		
	};

}
#endif