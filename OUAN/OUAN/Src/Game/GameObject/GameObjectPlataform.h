#ifndef GameObjectPlataformH_H
#define GameObjectPlataformH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

namespace OUAN
{
	const std::string PLATFORM1_ANIM_FRONT="front_Clip";
	const std::string PLATFORM1_ANIM_BACK="back_Clip";
	const std::string PLATFORM2_ANIM_FRONT="front";
	const std::string PLATFORM2_ANIM_BACK="back";
	const std::string PLATFORM3_ANIM_FRONT="front";
	const std::string PLATFORM3_ANIM_BACK="back";

	const double PLATAFORM_COLLISION_TIME_MARGIN = 0.5;

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
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

		TrajectoryComponentPtr mTrajectoryComponent;

		Ogre::Vector3 mLastPosition;
		Ogre::Vector3 mLastPositionDifference;
		double mElapsedTimeSinceLastCollision;
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
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

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
		
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;
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
		TLogicComponentParameters tLogicComponentParameters;

		///Trajectory parameters
		TTrajectoryComponentParameters tTrajectoryComponentParameters;
	};
}
#endif