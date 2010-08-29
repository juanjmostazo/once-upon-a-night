#ifndef GameObjectItemMaxHPH_H
#define GameObjectItemMaxHPH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../../Logic/LogicComponent/LogicComponentItem.h"

namespace OUAN
{

	const std::string MAXHP_ANIM_IDLE="idle01";
	/// Class to hold MaxHP information
	class GameObjectItemMaxHP : public GameObject, public boost::enable_shared_from_this<GameObjectItemMaxHP>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemHeartsFountain;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemHeartsFountainDouble;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemStarsCloud;
		/// Physics information
		PhysicsComponentVolumeBoxPtr mPhysicsComponentVolumeBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentItemPtr mLogicComponentItem;
	public:
		//Constructor
		GameObjectItemMaxHP(const std::string& name);
		//Destructor
		~GameObjectItemMaxHP();

		/// Set logic component
		void setLogicComponentItem(LogicComponentItemPtr logicComponentItem);

		void setVisible(bool visible);

		/// return logic component
		LogicComponentItemPtr getLogicComponentItem();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

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
		void setRenderComponentParticleSystemHeartsFountain(RenderComponentParticleSystemPtr mRenderComponentParticleSystemHeartsFountain);
		void setRenderComponentParticleSystemHeartsFountainDouble(RenderComponentParticleSystemPtr mRenderComponentParticleSystemHeartsFountainDouble);
		void setRenderComponentParticleSystemStarsCloud(RenderComponentParticleSystemPtr mRenderComponentParticleSystemStarsCloud);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemHeartsFountain() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemHeartsFountainDouble() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemStarsCloud() const;

		/// Set physics component
		void setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox);

		/// Get physics component
		PhysicsComponentVolumeBoxPtr getPhysicsComponentVolumeBox() const;
		
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
		void setChangeWorldFactor(double factor);

		/// Reset object
		virtual void reset();
		void disable();
		void enable();

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

		/// Update object
		void update(double elapsedSeconds);

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

		void startCollisionParticles();
	};

	class TGameObjectItemMaxHPParameters: public TGameObjectParameters
	{
	public:
		TGameObjectItemMaxHPParameters();
		~TGameObjectItemMaxHPParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

		///Logic parameters
		TLogicComponentItemParameters tLogicComponentItemParameters;
	};
}
#endif