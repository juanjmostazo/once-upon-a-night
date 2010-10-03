#ifndef GameObjectSwitchH_H
#define GameObjectSwitchH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

namespace OUAN
{
	const std::string SWITCH_STATE_OFF="SWITCH_STATE_OFF";
	const std::string SWITCH_STATE_PUSHABLE="SWITCH_STATE_PUSHABLE";
	const std::string SWITCH_STATE_PUSHED="SWITCH_STATE_PUSHED";

	const std::string SWITCH_SOUND_PUSHED="switch";

	const double SWITCH_PUSH_DISTANCE=1.9;

	/// Class to hold Tower information
	class GameObjectSwitch : public GameObject, public boost::enable_shared_from_this<GameObjectSwitch>
	{
	private:
		
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntity;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent
		AudioComponentPtr mAudioComponent;

		void applySwitchEffect();
	public:
		//Constructor
		GameObjectSwitch(const std::string& name);
		//Destructor
		~GameObjectSwitch();
		/// Set logic component
		void setLogicComponentProp(LogicComponentPropPtr logicComponent);

		/// return logic component
		LogicComponentPropPtr getLogicComponentProp();

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

		/// Set physics component
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

		/// Set audio component
		/// @param pAudioComponent
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

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

		void setVisible(bool visible);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		void makePushable();

		void update(double elapsedSeconds);
	};

	class TGameObjectSwitchParameters: public TGameObjectParameters
	{
	public:
		TGameObjectSwitchParameters();
		~TGameObjectSwitchParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentPropParameters;

		///Audio parameters
		TAudioComponentMap tAudioComponentParameters;
	};
}
#endif