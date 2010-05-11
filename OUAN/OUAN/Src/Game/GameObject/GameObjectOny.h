#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Graphics/RenderComponent/RenderComponentQuadHalo.h"
#include "../../Graphics/RenderComponent/RenderComponentFractalVolume.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"
#include "../../Logic/LogicComponent/LogicComponentOny.h"

namespace OUAN
{
	//Time to be spent in idle state before the animation changes to 'napping'
	const double IDLE_SECONDS_TO_NAP=15.0;

	//Name of the bone whose position to retrieve to attach  to Ony
	const std::string ATTACH_BONE_NAME="RThumbRoot";

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

	#define SET_BIT(var,pos) var|(1<<pos)
	#define CLEAR_BIT(var,pos) var& ~(1<<pos)
	#define CHECK_BIT(var,pos) (var & (1<<pos))
	#define TOGGLE_BIT(var,pos) var^= (1<<pos)
	#define RESET_BIT_FIELD(var) var=0;

	//Animation names
	const std::string ONY_ANIM_IDLE01="idle01";
	const std::string ONY_ANIM_IDLE02="idle02";
	const std::string ONY_ANIM_WALK="walk";
	const std::string ONY_ANIM_RUN="run";
	const std::string ONY_ANIM_JUMP="jump";
	const std::string ONY_ANIM_GET_PILLOW="get_pillow";
	const std::string ONY_ANIM_STAB_RIGHT_PILLOW="stab_right_pillow";
	const std::string ONY_ANIM_STAB_LEFT_PILLOW="stab_left_pillow";
	const std::string ONY_ANIM_LEAVE_PILLOW="leave_pillow";
	const std::string ONY_ANIM_SPECIAL_PILLOW_ATTACK="special_pillow_attack";
	const std::string ONY_ANIM_GET_FLASH="get_flash";
	const std::string ONY_ANIM_SHOOT_SPECIAL="shoot_special";
	const std::string ONY_ANIM_ALERT="alert";
	const std::string ONY_ANIM_HIT01="hit01";
	const std::string ONY_ANIM_HIT02="hit02";
	const std::string ONY_ANIM_DIE01="die01";
	const std::string ONY_ANIM_DIE02="die02";
	const std::string ONY_ANIM_TIRED="tired";
	const std::string ONY_ANIM_HANDLE="handle";
	const std::string ONY_ANIM_OPEN_DOOR="open_door";
	const std::string ONY_ANIM_GET_PIECE="get_piece";
	const std::string ONY_ANIM_GET_ITEM="get_item";
	const std::string ONY_ANIM_AFRAID="afraid";
	const std::string ONY_ANIM_CHANGE_WORLD="change_world";
	const std::string ONY_ANIM_TICKLING="tickling";
	const std::string ONY_ANIM_SPEAK="speak";
	const std::string ONY_ANIM_FALLING="falling";
	const std::string ONY_ANIM_SHOOT_UP="shoot_up";
	const std::string ONY_ANIM_SHOOT_CENTER="shoot_center";
	const std::string ONY_ANIM_SHOOT_DOWN="shoot_down";

	/// Main character game object
	class GameObjectOny : public GameObject, public boost::enable_shared_from_this<GameObjectOny>
	{

	private:	
		/// Visual component data
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Positional component data
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemLand;
		/// Quad Halo
		RenderComponentQuadHaloPtr mRenderComponentQuadHalo;
		/// Fractal Volume
		RenderComponentFractalVolumePtr mRenderComponentFractalVolume;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		/// Logic information
		LogicComponentOnyPtr mLogicComponentOny;
		/// Weapon wielding component
		WeaponComponentPtr mWeaponComponent;
		//TODO: move to LogicComponentOny
		std::string mDreamsWeapon;
		std::string mNightmaresWeapon;
		double mIdleTime;

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

		/// Set Particle Systems
		void setRenderComponentParticleSystemLand(RenderComponentParticleSystemPtr mRenderComponentParticleSystemLand);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemLand() const;

		/// Set Quad Halo
		void setRenderComponentQuadHalo(RenderComponentQuadHaloPtr mRenderComponentQuadHalo);

		/// Get Quad Halo
		RenderComponentQuadHaloPtr getRenderComponentQuadHalo() const;

		/// Set Fractal Volume
		void setRenderComponentFractalVolume(RenderComponentFractalVolumePtr mRenderComponentFractalVolume);

		/// Get Fractal Volume
		RenderComponentFractalVolumePtr getRenderComponentFractalVolume() const;

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter() const;

		/// set weapon component
		void setWeaponComponent(WeaponComponentPtr weaponComponent);

		void setAttack(TWeaponMode weaponMode);
		WeaponComponentPtr getWeaponComponent() const;

		//void initWeaponComponent(int world);
		void setInitialWeaponComponent(int world);
		void beginAttack();
		void switchOff();
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

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		bool isDying() const;

		bool isMoving();
		bool isJumping();
		bool cancelAutoCameraMovement();

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

		void processAnimationEnded(const std::string& animationName);

		void postUpdate();
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

		///Fractal Volume parameters
		TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;	

		///Logic parameters
		TLogicComponentOnyParameters tLogicComponentOnyParameters;
		
		///Weapon parameters
		TWeaponComponentParameters tWeaponComponentParameters;
	};

}
#endif