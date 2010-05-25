#ifndef GameObjectBillboardSetH_H
#define GameObjectBillboardSetH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../../Graphics/RenderComponent/ChangeWorldMaterial.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectBillboardSet : public GameObject, public boost::enable_shared_from_this<GameObjectBillboardSet>
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentBillboardSetPtr mRenderComponentBillboardSet;
		/// Holds information related to the object's position in space
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;

	public:
		//Constructor
		GameObjectBillboardSet(const std::string& name);
		//Destructor
		~GameObjectBillboardSet();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Get billboardset component
		/// @return billboardset component
		RenderComponentBillboardSetPtr getRenderComponentBillboardSet() const;

		/// Set billboardset component
		/// @param pRenderComponentLight the billboardset component to set
		void setRenderComponentBillboardSet(RenderComponentBillboardSetPtr pRenderComponentBillboardSet);

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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;


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

	/// Transport object carrying around data from the level loader
	/// to the BillboardSet object
	class TGameObjectBillboardSetParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectBillboardSetParameters();
		/// Default destructor
		~TGameObjectBillboardSetParameters();

		/// billboardset-specific parameters
		TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

		//ChangeWorld parameters
		TChangeWorldMaterialParameters tChangeWorldMaterialParameters;
	};
}
#endif