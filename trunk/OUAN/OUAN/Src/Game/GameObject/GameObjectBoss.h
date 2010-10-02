#ifndef GameObjectBossH_H
#define GameObjectBossH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{

	//States
	const std::string BOSS_STATE_PATROL="BOSS_STATE_PATROL";
	const std::string BOSS_STATE_ALERT="BOSS_STATE_ALERT";
	const std::string BOSS_STATE_CHASE="BOSS_STATE_CHASE";
	const std::string BOSS_STATE_TIRED="BOSS_STATE_TIRED";
	const std::string BOSS_STATE_ATTACK="BOSS_STATE_ATTACK";
	const std::string BOSS_STATE_SP_ATTACK="BOSS_STATE_SP_ATTACK";
	const std::string BOSS_STATE_FLASHLIGHT_HIT="BOSS_STATE_FLASHLIGHT_HIT";
	const std::string BOSS_STATE_STUNNED = "BOSS_STATE_STUNNED";
	const std::string BOSS_STATE_LEAVING_NIGHTMARES = "BOSS_STATE_LEAVING_NIGHTMARES";
	const std::string BOSS_STATE_PILLOW_HIT = "BOSS_STATE_PILLOW_HIT";
	const std::string BOSS_STATE_DIE = "BOSS_STATE_DIE";
	const std::string BOSS_STATE_WARCRY = "BOSS_STATE_WARCRY";

	//Animations
	const std::string BOSS_ANIMATION_ALERT = "alert";
	const std::string BOSS_ANIMATION_ATTACK = "attack00";
	const std::string BOSS_ANIMATION_SP_ATTACK = "sp_attack";
	const std::string BOSS_ANIMATION_DIE = "die";
	const std::string BOSS_ANIMATION_FLASHLIGHT_HIT = "flashlight_hit";
	const std::string BOSS_ANIMATION_LEAVE = "flashlight_hit";
	const std::string BOSS_ANIMATION_MANUAL = "manual";
	const std::string BOSS_ANIMATION_PILLOW_HIT = "pillow_hit";
	const std::string BOSS_ANIMATION_REST = "rest";
	const std::string BOSS_ANIMATION_WALK = "trot";
	const std::string BOSS_ANIMATION_RUN = "run";
	const std::string BOSS_ANIMATION_RUN_PISSED_OFF = "run_pissed_off";
	const std::string BOSS_ANIMATION_STUNNED = "stunned";
	const std::string BOSS_ANIMATION_TIRED = "tired";
	const std::string BOSS_ANIMATION_WARCRY = "war_cry";

	//Trajectory Speeds
	const double BOSS_SPEED_WALK = 0.5;
	const double BOSS_SPEED_RUN = 0.8;
	const double BOSS_SPEED_RUN_PISSED_OFF = 1.2;

	//materials
	const std::string BOSS_MATERIAL_RED = "boss_red_d";
	const std::string BOSS_MATERIAL_BLUE = "boss_blue_d";
	const std::string BOSS_MATERIAL_GREEN = "boss_green_d";

	//sounds
	const std::string BOSS_SOUND_HIT="tripollo_hit";
	const std::string BOSS_SOUND_DIE="tripollo_die";
	const std::string BOSS_SOUND_EXPLODE="tripollo_explosion";
	const std::string BOSS_SOUND_SCRATCH="tripollo_scratch";
	const std::string BOSS_SOUND_WINGS="tripollo_wings";
	const std::string BOSS_SOUND_GRAZNIDO="tripollo_graznido";
	const std::string BOSS_SOUND_ATTACK="tripollo_attack";
	const std::string BOSS_SOUND_SURPRISE="tripollo_surprise";
	const std::string BOSS_SOUND_CALL_TO_ARMS="tripollo_call_to_arms";

	/// Class modelling a particular enemy type
	class GameObjectBoss : public GameObject, public boost::enable_shared_from_this<GameObjectBoss>
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntity;

		/// Positional component
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemDie;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		PhysicsComponentWeaponPtr mPhysicsComponentWeapon;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentEnemyPtr mLogicComponentEnemy;

		/// TrajectoryComponent
		TrajectoryComponentPtr mTrajectoryComponent;

		/// Audio component
		AudioComponentPtr mAudioComponent;

		bool activateTrajectory(int newWorld);
		bool hasPatrolTrajectory();
		std::string getPatrolTrajectoryName(int world);
		void setCurrentWalkAnimation();
		void updateHPEvents();
	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectBoss(const std::string& name);

		//Destructor
		~GameObjectBoss();
		/// Set logic component
		void setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy);
		/// Set audio component
		/// @param pRenderComponentEntity
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);
		/// return logic component
		LogicComponentEnemyPtr getLogicComponentEnemy();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

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

		/// Set Particle Systems
		void setRenderComponentParticleSystemDie(RenderComponentParticleSystemPtr mRenderComponentParticleSystemDie);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemDie() const;
		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);
		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter() const;

		/// Set physics component weapon
		void setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon);
		/// Get physics component weapon
		PhysicsComponentWeaponPtr getPhysicsComponentWeapon() const;

		/// Update object
		virtual void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		bool hasBeenHit() const;
		bool hasDied() const;

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;
		
		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		int getTimeStunned() const;

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		void processAnimationEnded(const std::string& animationName);
		

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;

		bool isWorthUpdatingPhysicsComponents();
		bool isWorthUpdatingLogicComponents();
	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectBoss"
	class TGameObjectBossParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBossParameters();
		/// Default destructor
		~TGameObjectBossParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;
		TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;

		///Logic parameters
		TTrajectoryComponentParameters tTrajectoryComponentParameters;

		///Logic parameters
		TLogicComponentEnemyParameters tLogicComponentEnemyParameters;
	};

}
#endif