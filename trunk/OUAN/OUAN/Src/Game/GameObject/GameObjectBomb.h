#ifndef GameObjectBombH_H
#define GameObjectBombH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{

	//State names
	const std::string BOMB_STATE_OFF="BOMB_STATE_OFF";
	const std::string BOMB_STATE_IDLE="BOMB_STATE_IDLE";
	const std::string BOMB_STATE_FOLLOW="BOMB_STATE_FOLLOW";
	const std::string BOMB_STATE_ACTIVATE="BOMB_STATE_ACTIVATE";
	const std::string BOMB_STATE_ACTIVATE_TO_PUZZLE_START="BOMB_STATE_ACTIVATE_TO_PUZZLE_START";
	const std::string BOMB_STATE_EXPLOSION="BOMB_STATE_EXPLOSION";
	const std::string BOMB_STATE_EXPLOSION_TO_PUZZLE_START="BOMB_STATE_EXPLOSION_TO_PUZZLE_START";
	const std::string BOMB_STATE_PUZZLE_START="BOMB_STATE_PUZZLE_START";

	const std::string BOMB_ANIMATION_IDLE="bite_idle1_eani_Clip";
	const std::string BOMB_ANIMATION_EXPLODE="explote_eani_Clip";
	const std::string BOMB_ANIMATION_WALK="walk1_Clip";
	const double BOMB_ANIMATION_EXPLODE_FART_MOMENT=0.85;

	const std::string BOMB_SOUND_FART="fart";
	const std::string BOMB_SOUND_EXPLOSION="explosion";


	/// Class to hold Bomb information
	class GameObjectBomb : public GameObject, public boost::enable_shared_from_this<GameObjectBomb>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemExplosion;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		TrajectoryComponentPtr mTrajectoryComponent;

		/// Physics information
		PhysicsComponentWeaponPtr mPhysicsComponentWeapon;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponentProp;

		/// Audio component
		AudioComponentPtr mAudioComponent;

		void checkPlayFartSound();
		bool mPlayedFart;
	public:
		//Constructor
		GameObjectBomb(const std::string& name);
		//Destructor
		~GameObjectBomb();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set audio component
		/// @param pAudioComponent
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

		/// Set trajectory component
		/// @param pTrajectoryComponent
		TrajectoryComponentPtr getTrajectoryComponent() const;
		void setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent);

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntityDreams);

		/// Set logic component
		void setLogicComponentProp(LogicComponentPropPtr logicComponentProp);

		/// return logic component
		LogicComponentPropPtr getLogicComponentProp();

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
		void setRenderComponentParticleSystemExplosion(RenderComponentParticleSystemPtr mRenderComponentParticleSystemExplosion);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemExplosion() const;

		void setVisible(bool visible);

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter() const;

		void updatePhysicsComponents(double elapsedSeconds);
		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		PhysicsComponentWeaponPtr getPhysicsComponentWeapon() const;
		void setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void calculateChangeWorldTotalTime(double changeWorldTotalTime);
		void calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

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

		void processAnimationEnded(const std::string& animationName);

		void restartToInitialPoint();
		void activateExplosion();
		void initBombPuzzle();


		// update 
		void update(double elapsedSeconds);

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;
	};

	class TGameObjectBombParameters: public TGameObjectParameters
	{
	public:
		TGameObjectBombParameters();
		~TGameObjectBombParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;
		TRenderComponentEntityParameters tRenderComponentAdditionalParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;

		///Physics parameters
		TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentPropParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;

		/// Trajectory component params
		TTrajectoryComponentParameters tTrajectoryComponentParamters;
	};
}
#endif