#ifndef GameObjectPlataformH_H
#define GameObjectPlataformH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{
	const std::string PLATFORM_ANIM_IDLE="idle";
	const std::string PLATFORM_ANIM_JUMP="jump";

	const double PLATAFORM_COLLISION_TIME_MARGIN = 0.3;
	const double PLATAFORM_COLLISION_HEIGHT_CORRECTION = 40;
	const double PLATAFORM_MAX_DIFFERENCE_FALL = 10;

	const std::string PLATFORM_MATERIAL_1_NORMAL_DREAMS = "flower1_d";
	const std::string PLATFORM_MATERIAL_1_JUMP_DREAMS = "flower1_jump_d";
	const std::string PLATFORM_MATERIAL_1_NORMAL_NIGHTMARES = "flower1_n";
	const std::string PLATFORM_MATERIAL_1_JUMP_NIGHTMARES = "flower1_jump_n";

	const std::string FLOWER_JUMPABLE_MESH = "flor1_ani.mesh";

	/// Class to hold terrain information
	class GameObjectPlataform : public GameObject, public boost::enable_shared_from_this<GameObjectPlataform>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexConvexPtr mPhysicsComponentComplexConvex;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

		TrajectoryComponentPtr mTrajectoryComponent;

		Ogre::Vector3 mLastPosition;
		Ogre::Vector3 mLastPositionDifference;
		double mElapsedTimeSinceLastCollision;
		bool mHit;
		bool mLastFrameHit;
		bool mActivated;
		bool mOnyOntoPlatform;
	public:
		//Constructor
		GameObjectPlataform(const std::string& name);
		//Destructor
		~GameObjectPlataform();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;
		/// Set logic component
		void setLogicComponentProp(LogicComponentPropPtr logicComponent);

		/// return logic component
		LogicComponentPropPtr getLogicComponentProp();

		
		bool isWorthUpdatingPhysicsComponents();

		void activate();
		bool isActivated();

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Set trajectory component
		/// @param pTrajectoryComponent
		void setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent);
		TrajectoryComponentPtr getTrajectoryComponent();

		void resetElapsedTimeSinceLastCollision();
		void resetLastPositionDifference();

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

		void updatePhysicsComponents(double elapsedSeconds);

		void activateHit();

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

		void activateTrajectory();

		void update(double elapsedSeconds);
		
		void processAnimationEnded(const std::string& animationName);
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;
	};

	class TGameObjectPlataformParameters: public TGameObjectParameters
	{
	public:
		TGameObjectPlataformParameters();
		~TGameObjectPlataformParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentPropParameters;

		///Trajectory parameters
		TTrajectoryComponentParameters tTrajectoryComponentParameters;
	};
}
#endif