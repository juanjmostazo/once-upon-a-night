#ifndef GameObjectTotemH_H
#define GameObjectTotemH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	/// Class to hold Tower information
	class GameObjectTotem : public GameObject, public boost::enable_shared_from_this<GameObjectTotem>
	{
	private:
		
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexTrianglePtr mPhysicsComponentComplexTriangle;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTotem(const std::string& name);
		//Destructor
		~GameObjectTotem();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

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
		void setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle);

		/// Get physics component
		PhysicsComponentComplexTrianglePtr getPhysicsComponentComplexTriangle() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;
	};

	class TGameObjectTotemParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTotemParameters();
		~TGameObjectTotemParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;
	};
}
#endif