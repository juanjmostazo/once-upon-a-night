#ifndef GameObjectDiamondTreeH_H
#define GameObjectDiamondTreeH_H

#include "GameObject.h"
#include "GameObjectTree.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
//#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
//#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

namespace OUAN
{
	//State names
	const std::string DT_STATE_IDLE="DT_STATE_IDLE";
	const std::string DT_STATE_HIT="DT_STATE_HIT";
	const std::string DT_STATE_RELOAD="DT_STATE_RELOAD";

	//Animation names
	const std::string DT_ANIM_IDLE="static_pose";
	const std::string DT_ANIM_HIT="hit";

	//Sounds
	//const std::string TRIPOLLO_SOUND_HIT="tripollo_is_hit";
	//const std::string TRIPOLLO_SOUND_DIE="tripollo_dies";

	/// Class to hold DiamondTree information
	class GameObjectDiamondTree : public GameObject, public boost::enable_shared_from_this<GameObjectDiamondTree>
	{
	private:
		
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		//PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		//PhysicsComponentVolumeBoxPtr mPhysicsComponentVolumeBox;
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

		TGameObjectDiamondContainer mDiamonds;
	public:
		//Constructor
		GameObjectDiamondTree(const std::string& name);
		//Destructor
		~GameObjectDiamondTree();
		/// Set logic component
		void setLogicComponent(LogicComponentPropPtr logicComponent);

		/// return logic component
		LogicComponentPropPtr getLogicComponent();

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

		void setVisible(bool visible);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;

		//PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;
		//void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr physicsComponentSimpleBox);

		//PhysicsComponentVolumeBoxPtr getPhysicsComponentVolumeBox() const;
		//void setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr physicsComponentVolumeBox);

		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr physicsComponentSimpleBox);

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

		void updatePhysicsComponents(double elapsedSeconds);

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

		// update logic component
		void updateLogic(double elapsedSeconds);

		TGameObjectDiamondContainer* getDiamonds();
		void setDiamonds(const TGameObjectDiamondContainer& diamonds);
		void addDiamond(GameObjectDiamondPtr diamond);

		void processAnimationEnded(const std::string& animationName);

		void update(double elapsedSeconds);

	};

	class TGameObjectDiamondTreeParameters: public TGameObjectParameters
	{
	public:
		TGameObjectDiamondTreeParameters();
		~TGameObjectDiamondTreeParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;
		//TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentParameters;
	};
}
#endif