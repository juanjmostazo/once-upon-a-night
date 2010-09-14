#ifndef GameObjectTripolloH_H
#define GameObjectTripolloH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/AttackComponent.h"
#include "../../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{
	//State names
	const std::string TRIPOLLO_STATE_IDLE="TRIPOLLO_STATE_IDLE";
	const std::string TRIPOLLO_STATE_PATROL="TRIPOLLO_STATE_PATROL";
	const std::string TRIPOLLO_STATE_CHASE="TRIPOLLO_STATE_CHASE";
	const std::string TRIPOLLO_STATE_FIND="TRIPOLLO_STATE_FIND";
	const std::string TRIPOLLO_STATE_ATTACK="TRIPOLLO_STATE_ATTACK";
	const std::string TRIPOLLO_STATE_FLEE="TRIPOLLO_STATE_FLEE";
	const std::string TRIPOLLO_STATE_DEAD="TRIPOLLO_STATE_DEAD";
	const std::string TRIPOLLO_STATE_HIT="TRIPOLLO_STATE_HIT";
	const std::string TRIPOLLO_STATE_SURPRISE = "TRIPOLLO_STATE_SURPRISE";
	const std::string TRIPOLLO_STATE_FALSE_ALARM = "TRIPOLLO_STATE_FALSE_ALARM";
	const std::string TRIPOLLO_STATE_ALERT = "TRIPOLLO_STATE_ALERT";
	const std::string TRIPOLLO_STATE_TIRED = "TRIPOLLO_STATE_TIRED";
	const std::string TRIPOLLO_STATE_CALL_TO_ARMS = "TRIPOLLO_STATE_CALL_TO_ARMS";
	const std::string TRIPOLLO_STATE_TREMBLING = "TRIPOLLO_STATE_TREMBLING";
	const std::string TRIPOLLO_STATE_IDLE1 = "TRIPOLLO_STATE_IDLE1";
	const std::string TRIPOLLO_STATE_CALL_TO_CHASE = "TRIPOLLO_STATE_CALL_TO_CHASE";	
	const std::string TRIPOLLO_STATE_STATUE="TRIPOLLO_STATE_STATUE";

	const std::string TRIPOLLO_ATTACK_PECK="peck";
	const std::string TRIPOLLO_ATTACK_CLAW="claw";

	//Animation names
	const std::string TRIPOLLO_ANIM_ALERT="alert";
	const std::string TRIPOLLO_ANIM_ATTACK_00="attack00";
	const std::string TRIPOLLO_ANIM_ATTACK_01="attack_01";
	const std::string TRIPOLLO_ANIM_CALL_TO_ARMS="call_to_arms";
	const std::string TRIPOLLO_ANIM_DIE="die";
	const std::string TRIPOLLO_ANIM_FALSE_ALARM="false_alarm";
	const std::string TRIPOLLO_ANIM_AFRAID="flee_afraid";
	const std::string TRIPOLLO_ANIM_HIT01="hit01";
	const std::string TRIPOLLO_ANIM_HIT02="hit02";
	const std::string TRIPOLLO_ANIM_IDLE="idle_00";	
	const std::string TRIPOLLO_ANIM_IDLE1="idle01";
	const std::string TRIPOLLO_ANIM_STATUE="rest";
	const std::string TRIPOLLO_ANIM_RUN="run";
	const std::string TRIPOLLO_ANIM_STUN="stun";
	const std::string TRIPOLLO_ANIM_SURPRISE="surprise";
	const std::string TRIPOLLO_ANIM_TIRED="tired";
	const std::string TRIPOLLO_ANIM_WALK="walk";
	const std::string TRIPOLLO_ANIM_WALK_FAST="walk_fast";

	//Should poses were used
	const std::string TRIPOLLO_ANIM_MANUAL="manual";

	const std::string TRIPOLLO_SOUND_HIT="tripollo_hit";
	const std::string TRIPOLLO_SOUND_DIE="tripollo_die";
	const std::string TRIPOLLO_SOUND_EXPLODE="tripollo_explosion";
	const std::string TRIPOLLO_SOUND_SCRATCH="tripollo_scratch";
	const std::string TRIPOLLO_SOUND_WINGS="tripollo_wings";
	const std::string TRIPOLLO_SOUND_GRAZNIDO="tripollo_graznido";
	const std::string TRIPOLLO_SOUND_ATTACK="tripollo_attack";
	const std::string TRIPOLLO_SOUND_SURPRISE="tripollo_surprise";
	const std::string TRIPOLLO_SOUND_CALL_TO_ARMS="tripollo_call_to_arms";

	const double CALL_TO_ARMS_SOUND_DISTANCE=500;

	/// Class modelling a particular enemy type
	class GameObjectTripollo : public GameObject, public boost::enable_shared_from_this<GameObjectTripollo>
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Positional component
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemDieDreams;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemDieNightmares;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemShock;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemSurprise;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		/// Trajectory information
		TrajectoryComponentPtr mTrajectoryComponent;

		AttackComponentPtr mAttackComponent;

		AudioComponentPtr mAudioComponent;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentEnemyPtr mLogicComponentEnemy;

		bool activateTrajectory(int newWorld);

		void checkTripolloPlataformPuzzleActivations();

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectTripollo(const std::string& name);

		//Destructor
		~GameObjectTripollo();
		/// Set logic component
		void setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy);

		/// return logic component
		LogicComponentEnemyPtr getLogicComponentEnemy();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		void setVisible(bool visible);

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

		/// Set Particle Systems
		void setRenderComponentParticleSystemDieDreams(RenderComponentParticleSystemPtr mRenderComponentParticleSystemDieDreams);
		void setRenderComponentParticleSystemDieNightmares(RenderComponentParticleSystemPtr mRenderComponentParticleSystemDieNightmares);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemDieDreams() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemDieNightmares() const;

		/// Set Particle Systems
		void setRenderComponentParticleSystemShock(RenderComponentParticleSystemPtr mRenderComponentParticleSystemShock);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemShock() const;

		/// Set Particle Systems
		void setRenderComponentParticleSystemSurprise(RenderComponentParticleSystemPtr mRenderComponentParticleSystemSurprise);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemSurprise() const;

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter() const;

		AttackComponentPtr getAttackComponent() const;
		void setAttackComponent(AttackComponentPtr attackComponent);
		std::string getDefaultAttack();

		/// Return audio component
		AudioComponentPtr getAudioComponent() const; //GETTER!
		void setAudioComponent(AudioComponentPtr audioComponent);

		/// Update object
		virtual void update(double elapsedSeconds);
		
		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		/// Reset object
		virtual void reset();

		//-- Methods used by GameWorldManager or GameObject to implement global query methods used by LUA
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

		void activateFlying(bool flying);		

		void postUpdate();
		void processAnimationEnded(const std::string& animationName);
		bool hasBeenHit() const;
		bool hasDied() const;

		bool hasAudioComponent()const;
		AudioComponentPtr getAudioComponentInstance() const; //INHERITED!!

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

		double getMeleeRange() const;
		int countNeighboursInRange(double range, bool call) const;

		bool isStatueEnabled() const;

		void enable();

		bool hasPatrolTrajectory();
		std::string getPatrolTrajectoryName(int world);

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

		// Attacks parameters
		TAttackComponentParameters tAttackComponentParameters;

		///Logic parameters
		TLogicComponentEnemyParameters tLogicComponentEnemyParameters;

		//Trajectory paramters
		TTrajectoryComponentParameters tTrajectoryComponentParameters;

		TAudioComponentMap tAudioComponentParameters;
	};

}
#endif