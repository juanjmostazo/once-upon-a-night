#ifndef GameObjectTripolloDreamsH_H
#define GameObjectTripolloDreamsH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/AttackComponent.h"

#include "../../Logic/LogicComponent/LogicComponentEnemy.h"
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
	const std::string TRIPOLLO_ANIM_IDLE_02="idle02";
	const std::string TRIPOLLO_ANIM_WALK="walk";
	const std::string TRIPOLLO_ANIM_DIE="die";
	const std::string TRIPOLLO_ANIM_HIT01="hit01";

	/// Class modelling a particular enemy type
	class GameObjectTripolloDreams : public GameObject, public boost::enable_shared_from_this<GameObjectTripolloDreams>
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

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentEnemyPtr mLogicComponentEnemy;

		bool activateTrajectory(int world);
	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectTripolloDreams(const std::string& name);

		//Destructor
		~GameObjectTripolloDreams();
		/// Set logic component
		void setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy);

		/// return logic component
		LogicComponentEnemyPtr getLogicComponentEnemy();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

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

		/// Update object
		virtual void update(double elapsedSeconds);
		
		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

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
		void processCollision(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		// update logic component
		void updateLogic(double elapsedSeconds);

		void postUpdate();
		void processAnimationEnded(const std::string& animationName);
		bool hasBeenHit() const;
		bool hasDied() const;

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectTripolloDreams"
	class TGameObjectTripolloDreamsParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectTripolloDreamsParameters();
		/// Default destructor
		~TGameObjectTripolloDreamsParameters();

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
	};

}
#endif