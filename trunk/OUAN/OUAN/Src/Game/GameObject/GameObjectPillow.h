#ifndef GameObjectPillowH_H
#define GameObjectPillowH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentPillow.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
#include "../../Logic/LogicComponent/AttackComponent.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"

namespace OUAN
{
	const std::string ATTACK_NAME_BASE="baseAttack";
	const std::string ATTACK_NAME_COMBO_1HIT="combo1Hit";
	const std::string ATTACK_NAME_COMBO_2HIT="combo2Hit";
	const std::string ATTACK_NAME_SPECIAL="spAttack";

	/// Class to hold GameObjectPillow information
	class GameObjectPillow : public GameObject, public boost::enable_shared_from_this<GameObjectPillow>
	{
	private:
		
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemAttack;
		/// Physics information
		PhysicsComponentPillowPtr mPhysicsComponentPillow;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;

		AttackComponentPtr mAttackComponent;

		double mLastAttackTime;
		Vector3 mLastBonePosition;

		WeaponComponentPtr mParentWeaponComponent;


	public:
		//Constructor
		GameObjectPillow(const std::string& name);
		//Destructor
		~GameObjectPillow();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

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

		/// Set Particle Systems
		void setRenderComponentParticleSystemAttack(RenderComponentParticleSystemPtr mRenderComponentParticleSystemAttack);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemAttack() const;

		PhysicsComponentPillowPtr getPhysicsComponentPillow() const;
		void setPhysicsComponentPillow(PhysicsComponentPillowPtr pPhysicsComponentPillow);


		AttackComponentPtr getAttackComponent() const;
		void setAttackComponent(AttackComponentPtr attackComponent);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		bool isWorthUpdatingPhysicsComponents();
		bool isWorthUpdatingLogicComponents();

		/// Reset object
		virtual void reset();

		/// Update object
		/// @param time passed since the last tick
		void update(double elapsedSeconds);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);


		// update logic component
		void updateLogic(double elapsedSeconds);

		double getLastAttackTime();
		void setLastAttackTime(double lastAttackTime);

		void beginAttack();
		void endAttack(); //TODO: Check all the similarly-named methods (switchOn/Off, use, etc) and refactor!!
		bool canInitiateAttack();
		std::string getDefaultAttack();
		void setAttack(const std::string& newAttack);

		std::string getAttackName();
		int getAttackDamage();

		WeaponComponentPtr getParentWeaponComponent() const;
		void setParentWeaponComponent(WeaponComponentPtr parentWeaponComponent);
		bool hasParentWeaponComponent() const;

		void disable();
		void enable();

		void startAttackParticles();
	};

	class TGameObjectPillowParameters: public TGameObjectParameters
	{
	public:
		TGameObjectPillowParameters();
		~TGameObjectPillowParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentPillowParameters tPhysicsComponentPillowParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;
		
		///Attack parameters
		TAttackComponentParameters attackComponentParameters;

	};
}
#endif