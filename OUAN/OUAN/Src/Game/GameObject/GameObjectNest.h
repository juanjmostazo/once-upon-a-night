#ifndef GAMEOBJECTNESTH_H
#define GAMEOBJECTNESTH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

namespace OUAN
{
	const std::string NEST_STATE_IDLE="NEST_STATE_IDLE";
	const std::string NEST_STATE_SHAKING="NEST_STATE_SHAKING";
	const std::string NEST_STATE_HATCHING="NEST_STATE_HATCHING";

	const std::string NEST_ANIM_IDLE="idle";
	const std::string NEST_ANIM_SHAKE="shake";
	const std::string NEST_ANIM_HATCH="jump";

	const std::string NEST_SOUND_NOTHING="nest_nothing";
	const std::string NEST_SOUND_TRIPOLLO="nest_tripollo";
	const std::string NEST_SOUND_BREAK="nest_break";
	const std::string NEST_SOUND_TOC_TOC="nest_toc_toc";


	/// Class to hold ScaredPlant information
	class GameObjectNest: public GameObject, public boost::enable_shared_from_this<GameObjectNest>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemBreak;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemJump;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

		std::string mSignpostMessage;

		std::vector<GameObjectPtr> mChildren;

		bool mEggHatched;
		
		double mChildrenTotalWeight;
		/// Audio component
		AudioComponentPtr mAudioComponent;
	public:
		//Constructor
		GameObjectNest(const std::string& name);
		//Destructor
		~GameObjectNest();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);
		/// Set logic component
		void setLogicComponent(LogicComponentPropPtr logicComponent);

		/// Set audio component
		/// @param pRenderComponentEntity
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);


		/// return logic component
		LogicComponentPropPtr getLogicComponent();

		void setVisible(bool visible);

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity);

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
		void setRenderComponentParticleSystemBreak(RenderComponentParticleSystemPtr mRenderComponentParticleSystemBreak);
		void setRenderComponentParticleSystemJump(RenderComponentParticleSystemPtr mRenderComponentParticleSystemJump);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemBreak() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemJump() const;

		/// Set physics component
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter() const;

		/// Update object
		virtual void update(double elapsedSeconds);
		void disable();

		/// Reset object
		virtual void reset();

		/// React to a world change to the given one
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

		
		

		void processAnimationEnded(const std::string& animationName);

		std::vector<GameObjectPtr>* getChildren();
		void setChildren(const std::vector<GameObjectPtr>& children);
		void addChild(GameObjectPtr child);
		void spawnChild();

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

		//------------------------------------------------------------------
	};

	class TGameObjectNestParameters: public TGameObjectParameters
	{
	public:
		TGameObjectNestParameters();
		~TGameObjectNestParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;


		///Logic parameters
		TLogicComponentPropParameters tLogicComponentParameters;

	};
}
#endif