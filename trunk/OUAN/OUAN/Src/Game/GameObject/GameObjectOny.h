#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
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
	const double IDLE_SECONDS_TO_NAP=15.0;

	//Time during which Ony will be invulnerable, after having taken a hit.
	const double POST_HIT_INVULNERABILITY=5.0;

	//Name of the bone whose position to retrieve to attach  to Ony
	const std::string ATTACH_BONE_NAME="LThumbRoot";

	//Default state
	const int ONY_STATE_IDLE=0;

	//Bit positions to encode Ony's state.
	//The reason why a bit field is being used instead
	//of a single number is to allow for combinations
	//of states (for instance, ony can be attacking at the same time that he's jumping
	//forward; that would combine three states at once)
	const unsigned int ONY_STATE_BIT_FIELD_IDLE=0;		//0=IDLE; 1=NAPPING (iff the rest of bits are set to 0)
	const unsigned int ONY_STATE_BIT_FIELD_MOVEMENT=1;  //0=Still or jumping vertically; 1=Moving in the XZ plane
	const unsigned int ONY_STATE_BIT_FIELD_WALK=2;		//0=Running; 1=Walking
	const unsigned int ONY_STATE_BIT_FIELD_JUMP=3;		//0=No jump; 1=Jumping
	const unsigned int ONY_STATE_BIT_FIELD_ACTION=4;	//0=No action; 1=Executing action (activating a portal, pulling a lever,...)
	const unsigned int ONY_STATE_BIT_FIELD_CHANGE_WORLD=5; //During a world change (probably not necessary)
	const unsigned int ONY_STATE_BIT_FIELD_WORLD=6; //if 1, nightmares
	const unsigned int ONY_STATE_BIT_FIELD_ATTACK=7;	//Ony is attacking	
	const unsigned int ONY_STATE_BIT_FIELD_SP_ATTACK=8; //If 1, ony's using his current weapon's special attack
	const unsigned int ONY_STATE_BIT_FIELD_COMBO01=9;	//These two fields will encode the combo state:
	const unsigned int ONY_STATE_BIT_FIELD_COMBO02=10;  //00: No combo
														//01: first hit
														//10: second hit
														//11: last hit
	const unsigned int ONY_STATE_BIT_FIELD_HIT=11; //Ony being hit
	const unsigned int ONY_STATE_BIT_FIELD_DIE=12; //Ony is dying
	const unsigned int ONY_STATE_BIT_FIELD_INVULNERABLE=13;

	const unsigned int ONY_STATE_BIT_FIELD_FALL=14; //Ony is falling

	#define SET_BIT(var,pos) var|(1<<pos)
	#define CLEAR_BIT(var,pos) var& ~(1<<pos)
	#define CHECK_BIT(var,pos) (var & (1<<pos))
	#define TOGGLE_BIT(var,pos) var^= (1<<pos)
	#define RESET_BIT_FIELD(var) var=0;

	//Animation names
/*

<PROPERTY id="animation9::name" type="7" value="face_afraid"></PROPERTY>
<PROPERTY id="animation9::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation10::name" type="7" value="face_close"></PROPERTY>
<PROPERTY id="animation10::loop" type="12" value="false"></PROPERTY>    
<PROPERTY id="animation11::name" type="7" value="face_happy01"></PROPERTY>
<PROPERTY id="animation11::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation12::name" type="7" value="face_happy02"></PROPERTY>
<PROPERTY id="animation12::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation13::name" type="7" value="face_neutral"></PROPERTY>
<PROPERTY id="animation13::loop" type="12" value="false"></PROPERTY>
<PROPERTY id="animation14::name" type="7" value="face_panic"></PROPERTY>
<PROPERTY id="animation14::loop" type="12" value="false"></PROPERTY>    
<PROPERTY id="animation15::name" type="7" value="face_sad"></PROPERTY>
<PROPERTY id="animation15::loop" type="12" value="false"></PROPERTY>    
<PROPERTY id="animation16::name" type="7" value="face_scream"></PROPERTY>
<PROPERTY id="animation16::loop" type="12" value="false"></PROPERTY>    
<PROPERTY id="animation17::name" type="7" value="face_speak01"></PROPERTY>
<PROPERTY id="animation17::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation18::name" type="7" value="face_speak02"></PROPERTY>
<PROPERTY id="animation18::loop" type="12" value="false"></PROPERTY>  

<PROPERTY id="animation34::name" type="7" value="look_back"></PROPERTY>
<PROPERTY id="animation34::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation35::name" type="7" value="look_down"></PROPERTY>
<PROPERTY id="animation35::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation36::name" type="7" value="look_left"></PROPERTY>
<PROPERTY id="animation36::loop" type="12" value="false"></PROPERTY>  
<PROPERTY id="animation37::name" type="7" value="look_right"></PROPERTY>
<PROPERTY id="animation37::loop" type="12" value="false"></PROPERTY>   
<PROPERTY id="animation38::name" type="7" value="look_up"></PROPERTY>
<PROPERTY id="animation38::loop" type="12" value="false"></PROPERTY>   

*/

	const std::string ONY_ANIM_IDLE01="idle01";
	const std::string ONY_ANIM_IDLE02="idle02";
	const std::string ONY_ANIM_WALK="walk";
	const std::string ONY_ANIM_RUN="run";
	const std::string ONY_ANIM_JUMP="jump02_pre";
	const std::string ONY_ANIM_JUMP02_START="jump02_pre";
	const std::string ONY_ANIM_JUMP02_KEEP="jump02_loop";
	const std::string ONY_ANIM_JUMP02_END="jump02_post";
	const std::string ONY_ANIM_JUMP01_START="jump01_pre";
	const std::string ONY_ANIM_JUMP01_KEEP="jump01_loop";
	const std::string ONY_ANIM_JUMP01_END="jump01_post";
	const std::string ONY_ANIM_ATTACK01="attack01";
	const std::string ONY_ANIM_ATTACK02="attack02";
	const std::string ONY_ANIM_ATTACK03="attack03";
	const std::string ONY_ANIM_CROUCH_START="crouch_pre";
	const std::string ONY_ANIM_CROUCH_KEEP="crouch_loop";
	const std::string ONY_ANIM_CROUCH_END="crouch_post";
	const std::string ONY_ANIM_DIE="die";
	const std::string ONY_ANIM_DRAW_PILLOW="draw_pillow";
	const std::string ONY_ANIM_HIDE_PILLOW01="hide_pillow01";
	const std::string ONY_ANIM_HIDE_PILLOW02="hide_pillow02";
	const std::string ONY_ANIM_HIDE_PILLOW03="hide_pillow03";
	const std::string ONY_ANIM_FRIGHT="fright";
	const std::string ONY_ANIM_FALL_START="fall_pre";
	const std::string ONY_ANIM_FALL_KEEP="fall_loop";
	const std::string ONY_ANIM_FALL_END="fall_post";
	const std::string ONY_ANIM_HIT01="hit01";
	const std::string ONY_ANIM_NAP_START="nap_pre";
	const std::string ONY_ANIM_NAP_KEEP="nap_loop";
	const std::string ONY_ANIM_NAP_END="nap_post";
	const std::string ONY_ANIM_SHOOT_CENTER="shoot_center";
	const std::string ONY_ANIM_VICTORY="victory";
	const std::string ONY_ANIM_VICTORY_START="victory_pre";
	const std::string ONY_ANIM_VICTORY_LOOP="victory_loop";
	const std::string ONY_ANIM_TICKLING_START="tickling_pre";
	const std::string ONY_ANIM_TICKLING_LOOP="tickling_loop";
	const std::string ONY_ANIM_MANUAL="manual";

	//SOUND DEFINITIONS
	const std::string ONY_SOUND_DIE="any_dies";
	const std::string ONY_SOUND_STEP_GRASS_00="any_step_grass_00";
	const std::string ONY_SOUND_STEP_GRASS_01="any_step_grass_01";
	const std::string ONY_SOUND_STEP_WATER_00="any_step_water_00";
	const std::string ONY_SOUND_STEP_WATER_01="any_step_water_01";
	const std::string ONY_SOUND_STEP_HARD_SURFACE_00="any_step_hard_surface_00";
	const std::string ONY_SOUND_STEP_HARD_SURFACE_01="any_step_hard_surface_01";
	const std::string ONY_SOUND_STEP_WOOD_00="any_step_wood_00";
	const std::string ONY_SOUND_STEP_WOOD_01="any_step_wood_01";
	const std::string ONY_SOUND_SCARED="any_scared";
	const std::string ONY_SOUND_FALLS="any_falls";
	const std::string ONY_SOUND_LAUGHTS="any_laughts";
	const std::string ONY_SOUND_PILLOW_ATTACK_VOICE="any_pillow_attack";
	const std::string ONY_SOUND_PUSH="any_push";
	const std::string ONY_SOUND_INTERESTED="any_interested";
	const std::string ONY_SOUND_TRIUMPH_A="any_triumph_a";
	const std::string ONY_SOUND_TRIUMPH_B="any_triumph_b";
	const std::string ONY_SOUND_HIT_A="any_takes_hit_a";
	const std::string ONY_SOUND_HIT_B="any_takes_hit_b";
	const std::string ONY_SOUND_TRIUMPH_LAUGHT="any_triumph_laught";
	const std::string ONY_SOUND_JUMP="any_jump";
	const std::string ONY_SOUND_BURN="any_burn";
	const std::string ONY_SOUND_EXHAUSTED="any_exhausted";
	const std::string ONY_SOUND_SURPRISE_A="any_surprise_a";
	const std::string ONY_SOUND_SURPRISE_B="any_surprise_b";
	const std::string ONY_SOUND_VERY_SCARED="any_very_scared";
	const std::string ONY_SOUND_SPLASH_00="any_splash_00";
	const std::string ONY_SOUND_SPLASH_01="any_splash_01";
	const std::string ONY_SOUND_SPLASH_02="any_splash_02";
	const std::string ONY_SOUND_CRASH_00="any_crash_00";
	const std::string ONY_SOUND_CRASH_01="any_crash_01";
	const std::string ONY_SOUND_CRASH_02="any_crash_02";
	const std::string ONY_SOUND_SLIDE="any_slide";
	const std::string ONY_SOUND_JUMP_ONTO_WATER="any_jump_onto_water";
	const std::string ONY_SOUND_JUMP_ONTO_GRASS="any_jump_onto_grass";
	const std::string ONY_SOUND_JUMP_ONTO_HARD_SURFACE="any_jump_onto_hard_surface";
	const std::string ONY_SOUND_JUMP_ONTO_WOOD="any_jump_onto_wood";

	const std::string ONY_SOUND_PILLOW_ATTACK_START="pillow_attack_start";
	const std::string ONY_SOUND_PILLOW_ATTACK_END="pillow_attack_end";
	const std::string ONY_SOUND_FLASHLIGHT_ATTACK_START="flashlight_attack_start";
	const std::string ONY_SOUND_FLASHLIGHT_ATTACK_END="flashlight_attack_end";
	const std::string ONY_SOUND_FLASHLIGHT_OVERHEAT="flashlight_overheat";

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
		double mIdleTime;

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

		std::string mAttackAnimationName;

		//plataform related vars and function
		bool mIsOnPlataform;
		bool mLastFrameIsOnPlataform;
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