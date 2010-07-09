#ifndef GameObjectWoodBoxH_H
#define GameObjectWoodBoxH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../../Logic/LogicComponent/LogicComponentBreakable.h"

namespace OUAN
{
	//Animation states
	//const std::string WOODBOX_ANIM_IDLE01="idle";
	//const std::string WOODBOX_ANIM_BREAK01="break_01";
	const std::string WOODBOX_ANIM_BROKEN="broken";

	/// Class to hold WoodBox information
	class GameObjectWoodBox : public GameObject, public boost::enable_shared_from_this<GameObjectWoodBox>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		
		RenderComponentEntityPtr mRenderComponentEntityAdditional;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		PhysicsComponentVolumeBoxPtr mPhysicsComponentVolumeBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentBreakablePtr mLogicComponentBreakable;

	public:
		//Constructor
		GameObjectWoodBox(const std::string& name);
		//Destructor
		~GameObjectWoodBox();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;
		RenderComponentEntityPtr getRenderComponentEntityAdditional() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);
		void setRenderComponentEntityAdditional(RenderComponentEntityPtr pRenderComponentEntityAdditional);
		
		/// Set logic component
		void setLogicComponentBreakable(LogicComponentBreakablePtr logicComponentBreakable);

		/// return logic component
		LogicComponentBreakablePtr getLogicComponentBreakable();

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

		void setVisible(bool visible);

		/// Set physics component
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

		/// Set physics component
		void setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox);

		/// Get physics component
		PhysicsComponentVolumeBoxPtr getPhysicsComponentVolumeBox() const;

		void updatePhysicsComponents(double elapsedSeconds);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void calculateChangeWorldTotalTime(double changeWorldTotalTime);
		void calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();

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

		// update 
		void update(double elapsedSeconds);

		// update logic component
		void updateLogic(double elapsedSeconds);
	};

	class TGameObjectWoodBoxParameters: public TGameObjectParameters
	{
	public:
		TGameObjectWoodBoxParameters();
		~TGameObjectWoodBoxParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;
		TRenderComponentEntityParameters tRenderComponentAdditionalParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;
		TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

		///Logic parameters
		TLogicComponentBreakableParameters tLogicComponentBreakableParameters;
	};
}
#endif