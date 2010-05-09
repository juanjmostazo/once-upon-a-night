#ifndef GameObjectTriggerCapsuleH_H
#define GameObjectTriggerCapsuleH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "../../Logic/LogicComponent/LogicComponentTrigger.h"

namespace OUAN
{
	/// Class to hold volume capsule information
	class GameObjectTriggerCapsule : public GameObject, public boost::enable_shared_from_this<GameObjectTriggerCapsule>
	{
	private:
		/// Visual information - ONLY SHOWN IN DEBUG MODE
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentVolumeCapsulePtr mPhysicsComponentVolumeCapsule;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentTriggerPtr mLogicComponent;
	public:
		//Constructor
		GameObjectTriggerCapsule(const std::string& name);
		//Destructor
		~GameObjectTriggerCapsule();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);
		
		/// Set logic component
		void setLogicComponent(LogicComponentTriggerPtr logicComponent);

		/// return logic component
		LogicComponentTriggerPtr getLogicComponent();

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
		void setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule);

		/// Get physics component
		PhysicsComponentVolumeCapsulePtr getPhysicsComponentVolumeCapsule() const;

		/// Show or hide the component
		void changeVisibility();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;


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

	};

	class TGameObjectTriggerCapsuleParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTriggerCapsuleParameters();
		~TGameObjectTriggerCapsuleParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;

		///Logic parameters
		TLogicComponentTriggerParameters tLogicComponentParameters;

	};
}
#endif