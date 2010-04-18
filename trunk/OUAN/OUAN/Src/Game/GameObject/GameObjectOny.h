#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"
#include "../../Logic/LogicComponent/LogicComponentOny.h"

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
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

		LogicComponentOnyPtr mLogicComponentOny;
		
		/// Weapon wielding component
		WeaponComponentPtr mWeaponComponent;
		void initWeaponComponent();

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

		/// set weapon component
		void setWeaponComponent(WeaponComponentPtr weaponComponent);

		void setWeaponMode(TWeaponMode weaponMode);
		WeaponComponentPtr getWeaponComponent() const;

		/// Set logic component
		void setLogicComponentOny(LogicComponentOnyPtr pLogicComponentOny);

		/// return logic component
		LogicComponentOnyPtr getLogicComponentOny();

		/// Update object
		virtual void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		void decreaseHP(int amount=1);
		void setMaxHP();

		void increaseWeaponPower(int powerUnits=1);
		void decreaseWeaponPower(int powerUnits=1);

		/// Additional actions to take after losing one life
		void loseLife();
		/// Additional actions to take after losing all lives
		void gameOver();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		void useWeapon();
		void stopUsingWeapon();

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		// update logic component
		void updateLogic(double elapsedSeconds);
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

		///Logic parameters
		TLogicComponentOnyParameters tLogicComponentOnyParameters;
		
		///Weapon parameters
		TWeaponComponentParameters tWeaponComponentParameters;
	};

}
#endif