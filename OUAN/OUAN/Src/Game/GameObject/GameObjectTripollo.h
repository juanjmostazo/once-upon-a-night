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

	const std::string TRIPOLLO_ATTACK_PECK="peck";
	const std::string TRIPOLLO_ATTACK_CLAW="claw";

	//Animation names
	const std::string TRIPOLLO_ANIM_IDLE_02="idle01";
	const std::string TRIPOLLO_ANIM_WALK="walk";
	const std::string TRIPOLLO_ANIM_DIE="die";
	const std::string TRIPOLLO_ANIM_HIT01="hit01";

	const std::string TRIPOLLO_SOUND_HIT="tripollo_is_hit";
	const std::string TRIPOLLO_SOUND_DIE="tripollo_dies";

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