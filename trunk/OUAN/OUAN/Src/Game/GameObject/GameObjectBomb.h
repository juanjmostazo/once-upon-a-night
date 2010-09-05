#ifndef GameObjectBombH_H
#define GameObjectBombH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

	//State names
	const std::string BOMB_STATE_OFF="BOMB_STATE_OFF";
	const std::string BOMB_STATE_IDLE="BOMB_STATE_IDLE";
	const std::string BOMB_STATE_ACTIVATE="BOMB_STATE_ACTIVATE";
	const std::string BOMB_STATE_EXPLOSION="BOMB_STATE_EXPLOSION";

namespace OUAN
{
	//Animation states
	//const std::string Bomb_ANIM_IDLE01="idle";
	//const std::string Bomb_ANIM_BREAK01="break_01";
	const std::string Bomb_ANIM_BROKEN="broken";

	/// Class to hold Bomb information
	class GameObjectBomb : public GameObject, public boost::enable_shared_from_this<GameObjectBomb>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemExplosion;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;

		/// Physics information
		PhysicsComponentWeaponPtr mPhysicsComponentWeapon;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponentProp;

		/// Audio component
		AudioComponentPtr mAudioComponent;

		double mElapsedTime;

	public:
		//Constructor
		GameObjectBomb(const std::string& name);
		//Destructor
		~GameObjectBomb();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		/// Set audio component
		/// @param pRenderComponentEntity
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

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
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

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

		void updateLogic(double elapsedSeconds);
		

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;
	};

	class TGameObjectBombParameters: public TGameObjectParameters
	{
	public:
		TGameObjectBombParameters();
		~TGameObjectBombParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;
		TRenderComponentEntityParameters tRenderComponentAdditionalParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		///Physics parameters
		TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentPropParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;

	};
}
#endif