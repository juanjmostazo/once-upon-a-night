#ifndef GameObjectTreeComplexH_H
#define GameObjectTreeComplexH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	//Animation names
	const std::string TreeComplex_ANIM_UP="up";
	const std::string TreeComplex_ANIM_DOWN="down";
	const std::string TreeComplex_ANIM_IDLE_UP="idle01";
	const std::string TreeComplex_ANIM_IDLE_UP2="idle02";
	const std::string TreeComplex_ANIM_IDLE_DOWN="idle03";

	/// Class to hold GameObjectTreeComplex information
	class GameObjectTreeComplex : public GameObject, public boost::enable_shared_from_this<GameObjectTreeComplex>
	{
	private:
		int mType;

		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemStars;
		/// Physics information
		PhysicsComponentComplexConvexPtr mPhysicsComponentComplexConvex;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTreeComplex(const std::string& name);
		//Destructor
		~GameObjectTreeComplex();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		void setVisible(bool visible);

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

		/// Set Particle Systems
		void setRenderComponentParticleSystemStars(RenderComponentParticleSystemPtr mRenderComponentParticleSystemStars);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemStars() const;

		/// Set physics component
		void setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex);

		/// Get physics component
		PhysicsComponentComplexConvexPtr getPhysicsComponentComplexConvex() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void calculateChangeWorldTotalTime(double changeWorldTotalTime);
		void calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection);

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

		void setType(int pType);
		int getType() const;
	};

	class TGameObjectTreeComplexParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTreeComplexParameters();
		~TGameObjectTreeComplexParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

		//TreeComplex type [0, 12]
		int type;
	};
}
#endif