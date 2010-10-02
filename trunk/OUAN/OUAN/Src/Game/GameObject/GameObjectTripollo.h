#ifndef GameObjectBOSSH_H
#define GameObjectBOSSH_H

#include "GameObject.h"
#include "GameObjectBOSSDefs.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../Logic/LogicComponent/AttackComponent.h"
#include "../../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{
	const double CALL_TO_ARMS_SOUND_DISTANCE = 500;
	const double MAX_TIME_DEATH_PARTICLE_SYSTEM = 3;

	/// Class modelling a particular enemy type
	class GameObjectBOSS : public GameObject, public boost::enable_shared_from_this<GameObjectBOSS>
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
		PhysicsComponentWeaponPtr mPhysicsComponentWeapon;

		/// Trajectory information
		TrajectoryComponentPtr mTrajectoryComponent;

		AttackComponentPtr mAttackComponent;

		AudioComponentPtr mAudioComponent;

		double mDeathTime;

		void checkDeathParticleSystem(double elapsedSeconds);

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentEnemyPtr mLogicComponentEnemy;

		bool activateTrajectory(int newWorld);

		void checkBOSSPlataformPuzzleActivations();

		bool isHitAnimation(const std::string& animationName) const;
		bool isDieAnimation(const std::string& animationName) const;
		bool isAlertAnimation(const std::string& animationName) const;
		bool isFalseAlarmAnimation(const std::string& animationName) const;
		bool isSurpriseAnimation(const std::string& animationName) const;
		bool isTiredAnimation(const std::string& animationName) const;

	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectBOSS(const std::string& name);

		//Destructor
		~GameObjectBOSS();
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

		/// Set physics component
		void setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon);

		/// Get physics component
		PhysicsComponentWeaponPtr getPhysicsComponentWeapon() const;

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

		void updateWeapons(double elapsedSeconds);

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
		LogicComponentPtr getLogicComponent() const;

		double getMeleeRange() const;
		int countNeighboursInRange(double range, bool call) const;

		bool isStatueEnabled() const;

		void enable();

		bool hasPatrolTrajectory();
		std::string getPatrolTrajectoryName(int world);

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectBOSS"
	class TGameObjectBOSSParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBOSSParameters();
		/// Default destructor
		~TGameObjectBOSSParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;
		TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters;

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