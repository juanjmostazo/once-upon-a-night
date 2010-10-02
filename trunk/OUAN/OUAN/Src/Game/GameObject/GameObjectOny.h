#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "GameObjectOnyDefs.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Graphics/RenderComponent/RenderComponentQuadHalo.h"
#include "../../Graphics/RenderComponent/RenderComponentFractalVolume.h"
#include "../../Graphics/RenderComponent/RenderComponentMessageBox.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"
#include "../../Logic/LogicComponent/LogicComponentOny.h"

namespace OUAN
{
	//Time to be spent in idle state before the animation changes to 'napping'
	const double IDLE_SECONDS_TO_NAP=45.0;

	//Time during which Ony will be invulnerable, after having taken a hit.
	const double POST_HIT_INVULNERABILITY=5.0;

	const double ONY_ANIM_FALL_LOOP_TIME=0.9;
	const double ONY_ANIM_FALL_END_TIME=3;

	//Name of the bone whose position to retrieve to attach  to Ony
	const std::string ATTACH_BONE_NAME="LThumbRoot";

	//animation perc when foot hits the floor
	const double ONY_SOUND_STEP_TIME_00=0;
	const double ONY_SOUND_STEP_TIME_01=0.5;

	/// Main character game object
	class GameObjectOny : public GameObject, public boost::enable_shared_from_this<GameObjectOny>
	{
	public:
		enum OnyParticleSystemID
		{
			ONY_PS_MIN_ID=0,
			ONY_PS_LAND_DREAMS=ONY_PS_MIN_ID,
			/*
				Define new ids anywhere between this comment
			*/
			ONY_PS_LAND_NIGHTMARES,
			ONY_PS_LAND_WAVE,
			ONY_PS_LAND_WATER_WAVE,
			ONY_PS_LAND_WATER_DROPS,
			ONY_PS_RUN_GRASS,
			ONY_PS_RUN_SAND,
			ONY_PS_RUN_SURPRISE,
			/*
				...and this one, or replace values accordingly
			*/
			ONY_PS_RUN_WATER,
			ONY_PS_MAX_ID=ONY_PS_RUN_WATER

		};
		static const int PARTICLE_SYSTEMS_NUM=ONY_PS_MAX_ID-ONY_PS_MIN_ID+1;
		//PARTICLE SYSTEMS REFACTOR
		typedef std::map<OnyParticleSystemID, RenderComponentParticleSystemPtr> TParticleSystemsMap;

	private:	
		/// Visual component data
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Positional component data
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		TParticleSystemsMap mParticleSystemsComponent;

		/// Trajectory information
		TrajectoryComponentPtr mTrajectoryComponent;
		bool mUsingTrajectory;

		/// Quad Halo
		RenderComponentQuadHaloPtr mRenderComponentQuadHalo;
		/// Physics information
		PhysicsComponentCharacterOnyPtr mPhysicsComponentCharacterOny;
		/// Logic information
		LogicComponentOnyPtr mLogicComponentOny;
		/// Weapon wielding component
		WeaponComponentPtr mWeaponComponent;
		/// Audio component
		AudioComponentPtr mAudioComponent;

		//TODO: move to LogicComponentOny
		std::string mDreamsWeapon;
		std::string mNightmaresWeapon;

		double mRunParticlesElapsed;
		double mRunParticlesNextInterval;
		
		//Random interval Bounds
		double mRunParticlesMin;
		double mRunParticlesMax;

		TWeaponMode mCurrentWeaponMode;

		RenderComponentMessageBoxPtr mMsgBoxComponent;

		bool mPlayedStep00;
		bool mPlayedStep01;

		void resetStepSounds();
		void playStepSounds();
		void playStep00();
		void playStep01();

		void startRunParticleSystem();

		bool mInvulnerable;

		std::string mAttackAnimationName;

		//plataform related vars and function
		bool mIsOnPlataform;
		bool mLastFrameIsOnPlataform;
		bool mInNonGrassArea;
		GameObjectPlataformPtr mPlataform;
		void applyPlataformEffect();

	public:
		//Constructor
		/// @param name	name of the object, specific to the class
		/// @param id	unique identifier of the instance
		GameObjectOny(const std::string& name);
		//Destructor
		~GameObjectOny();

		void setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent);
		TrajectoryComponentPtr getTrajectoryComponent() const;

		void activateTrajectory(const std::string& name, bool looping=false);
		void deactivateTrajectory();
		bool isTrajectoryActive() const;
		bool isTrajectoryFinished() const;

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

		/// Set a whole map of particle systems
		void setParticleSystemsComponent(const TParticleSystemsMap& particleSystems);
		/// Return particle systems container
		TParticleSystemsMap& getParticleSystemsComponent();

		/// Add new particle system to the component map
		void addParticleSystem(OnyParticleSystemID id,RenderComponentParticleSystemPtr particleSystem);
		/// Return particle system from its ID
		RenderComponentParticleSystemPtr getParticleSystem(OnyParticleSystemID id);

		// Facade methods to start/stop a concrete particle system from outside GameObjectOny
		void startParticleSystem(OnyParticleSystemID id);
		void stopParticleSystem(OnyParticleSystemID id);

		/// Set Quad Halo
		void setRenderComponentQuadHalo(RenderComponentQuadHaloPtr mRenderComponentQuadHalo);

		/// Get Quad Halo
		RenderComponentQuadHaloPtr getRenderComponentQuadHalo() const;

		/// Set physics component
		void setPhysicsComponentCharacterOny(PhysicsComponentCharacterOnyPtr pPhysicsComponentCharacterOny);

		/// Get physics component
		PhysicsComponentCharacterOnyPtr getPhysicsComponentCharacterOny() const;

		/// set weapon component
		void setWeaponComponent(WeaponComponentPtr weaponComponent);

		void setAttack(TWeaponMode weaponMode);
		WeaponComponentPtr getWeaponComponent() const;

		//void initWeaponComponent(int newWorld);
		void setInitialWeaponComponent(int newWorld);
		void beginAttack();
		void switchOff();
		/// Set logic component
		void setLogicComponentOny(LogicComponentOnyPtr pLogicComponentOny);

		/// return logic component
		LogicComponentOnyPtr getLogicComponentOny();

		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

		/// Update object
		virtual void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

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

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		bool isDying() const;
		bool isHit() const;

		bool isMoving();
		bool isJumping();
		bool cancelAutoCameraMovement();

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

		void postUpdate();

		AudioComponentPtr getAudioComponentInstance() const;
		bool hasAudioComponent() const;

		double getMovingSpeed();

		int getLogicNewState() const;
		void setLogicNewState(int newState);
		//only provide the getter!
		int getLogicCurrentState() const;

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;

		RenderComponentMessageBoxPtr getMsgBoxComponent() const;
		void setMsgBoxComponent(RenderComponentMessageBoxPtr msgBoxComponent);
		void changeMessage(const std::string& stringKey);
		void changeMessage(const std::string& stringKey, double duration);
		void showMessage();
		void hideMessage();
		bool isMessageVisible() const;

		double getRunParticlesElapsed() const;
		void setRunParticlesElapsed(double runParticlesElapsed);
		double getRunParticlesNextInterval() const;
		void setRunParticlesNextInterval(double runParticlesNextInterval);

		//Random interval Bounds
		double getRunParticlesMin() const;
		void setRunParticlesMin(double runParticlesMin);
		double getRunParticlesMax() const;
		void setRunParticlesMax(double runParticlesMax);

		void addDiamonds(int amount=1);

		bool isOnPlataform() const;
		void setOnPlataform(bool onPlataform,GameObjectPlataformPtr plataform);

		void setCurrentAttackAnimation(const std::string& animationName);

		bool isInvulnerable() const;
		void setInvulnerable(bool invulnerable);

		bool isInNonGrassArea() const;
		void setInNonGrassArea(bool inNonGrassArea);

		bool isNapping() const;
		bool isAttacking() const;

		bool isBlockingAnimation() const;

		const std::string& getCurrentAnimationName() const;

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

		///Quad Halo parameters
		TRenderComponentQuadHaloParameters tRenderComponentQuadHaloParameters;

		///Physics parameters
		TPhysicsComponentCharacterOnyParameters tPhysicsComponentCharacterOnyParameters;	

		///Logic parameters
		TLogicComponentOnyParameters tLogicComponentOnyParameters;
		
		///Weapon parameters
		TWeaponComponentParameters tWeaponComponentParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;

		//Trajectory paramters
		TTrajectoryComponentParameters tTrajectoryComponentParameters;

		TRenderComponentMessageBoxParameters tMsgBoxParams;

		double mRunParticlesMin;
		double mRunParticlesMax;
	};
}
#endif