#ifndef GameObjectCryKingH_H
#define GameObjectCryKingH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

namespace OUAN
{
	const std::string CRYKING_ANIMATION_CRY_END="cry_end1_Clip";
	const std::string CRYKING_ANIMATION_CRY="cry_loop1_Clip";
	const std::string CRYKING_ANIMATION_IDLE_2="idle02_Clip";
	const std::string CRYKING_ANIMATION_IDLE_3="idle03_Clip";
	const std::string CRYKING_ANIMATION_IDLE_3_1="idle03_Clip1";
	const std::string CRYKING_ANIMATION_IDLE_4="idle4_Clip";
	const std::string CRYKING_ANIMATION_SPEAK="speak_loop1_Clip";
	const std::string CRYKING_ANIMATION_WALK="walk_Clip";

	/// Class modelling a particular enemy type
	class GameObjectCryKing : public GameObject, public boost::enable_shared_from_this<GameObjectCryKing>
	{
	private:
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntity;

		/// Positional component
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;
		/// Audio component
		AudioComponentPtr mAudioComponent;
	public:
		/// Constructor
		/// @param name name of the game object, specific to this class
		/// @param id unique id of the game object
		GameObjectCryKing(const std::string& name);

		//Destructor
		~GameObjectCryKing();
		/// Set logic component
		void setLogicComponentProp(LogicComponentPropPtr logicComponent);

		/// return logic component
		LogicComponentPropPtr getLogicComponentProp();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set audio component
		/// @param pRenderComponentEntity
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

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

		/// Set physics component
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

		/// Update object
		virtual void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

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

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;

	};
	
	/// Information data structure to carry around data between the
	/// level loader and the "GameObjectCryKing"
	class TGameObjectCryKingParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectCryKingParameters();
		/// Default destructor
		~TGameObjectCryKingParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;


		///Logic parameters
		TLogicComponentPropParameters tLogicComponentPropParameters;
	};

}
#endif