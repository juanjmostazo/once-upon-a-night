#ifndef GameObjectBridgeH_H
#define GameObjectBridgeH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	const std::string BRIDGE_ANIM_IDLE="idle";
	const std::string BRIDGE_ANIM_ROLL="roll";
	const std::string BRIDGE_ANIM_ROLL_IDLE="roll_idle";

	/// Class to hold terrain information
	class GameObjectBridge : public GameObject, public boost::enable_shared_from_this<GameObjectBridge>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexConvexPtr mPhysicsComponentComplexConvex;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

	public:
		//Constructor
		GameObjectBridge(const std::string& name);
		//Destructor
		~GameObjectBridge();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		bool isWorthUpdatingPhysicsComponents();

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);


		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);


		void setVisible(bool visible);

		Ogre::Vector3 getLastPositionDifference();

		/// Set initial component
		void setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;

		/// Set physics component
		void setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex);

		/// Get physics component
		PhysicsComponentComplexConvexPtr getPhysicsComponentComplexConvex() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

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

		void update(double elapsedSeconds);
		
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;
	};

	class TGameObjectBridgeParameters: public TGameObjectParameters
	{
	public:
		TGameObjectBridgeParameters();
		~TGameObjectBridgeParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;


	};
}
#endif