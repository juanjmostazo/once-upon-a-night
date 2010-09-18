#ifndef GameObjectDoorH_H
#define GameObjectDoorH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	const std::string DOOR_ANIM_IDLE_CLOSE="idle01";
	const std::string DOOR_ANIM_OPEN="open";
	const std::string DOOR_ANIM_IDLE_OPEN="idle02";
	const std::string DOOR_ANIM_CLOSE="close";

	const std::string DOOR_SOUND_OPEN="door_open";
	const std::string DOOR_SOUND_CLOSE="door_close";

	/// Class to hold Door information
	class GameObjectDoor : public GameObject, public boost::enable_shared_from_this<GameObjectDoor>
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
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent
		/// Audio component
		AudioComponentPtr mAudioComponent;
	public:
		//Constructor
		GameObjectDoor(const std::string& name);
		//Destructor
		~GameObjectDoor();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);
		/// Set audio component
		/// @param pRenderComponentEntity
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);
		/// return logic component
		LogicComponentPtr getLogicComponent();

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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

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
		

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;

	};

	class TGameObjectDoorParameters: public TGameObjectParameters
	{
	public:
		TGameObjectDoorParameters();
		~TGameObjectDoorParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;
		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;


		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;
	};
}
#endif