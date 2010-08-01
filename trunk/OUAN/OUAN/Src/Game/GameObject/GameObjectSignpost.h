#ifndef GAMEOBJECTSIGNH_H
#define GAMEOBJECTSIGNH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentMessageBox.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

namespace OUAN
{
	const std::string SIGN_STATE_IDLE="SIGN_STATE_IDLE";
	const std::string SIGN_STATE_HIT="SIGN_STATE_HIT";
	
	const std::string SIGN_ANIM_IDLE="idle";
	const std::string SIGN_ANIM_HIT="hit";

	/// Class to hold ScaredPlant information
	class GameObjectSignpost: public GameObject, public boost::enable_shared_from_this<GameObjectSignpost>
	{
	private:
		/// Visual information
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

		//std::string mSignpostMessage;
		RenderComponentMessageBoxPtr mMessageBox;
	public:
		//Constructor
		GameObjectSignpost(const std::string& name);
		//Destructor
		~GameObjectSignpost();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		RenderComponentMessageBoxPtr getRenderComponentMessageBox() const;
		void setRenderComponentMessageBox(RenderComponentMessageBoxPtr messageBox);

		/// Set logic component
		void setLogicComponent(LogicComponentPropPtr logicComponent);

		/// return logic component
		LogicComponentPropPtr getLogicComponent();

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity);

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

		/// Update object
		virtual void update(double elapsedSeconds);

		/// Reset object
		virtual void reset();

		/// React to a world change to the given one
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);
		void calculateChangeWorldTotalTime(double changeWorldTotalTime);
		void calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

	/*	const std::string& getSignpostMessage() const;
		void setSignpostMessage(const std::string& signpostMessage);*/


		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		
		

		void processAnimationEnded(const std::string& animationName);

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

		//------------------------------------------------------------------
	};

	class TGameObjectSignpostParameters: public TGameObjectParameters
	{
	public:
		TGameObjectSignpostParameters();
		~TGameObjectSignpostParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentParameters;

		//std::string signpostMessage;
		TRenderComponentMessageBoxParameters tMsgBoxParams;
	};
}
#endif