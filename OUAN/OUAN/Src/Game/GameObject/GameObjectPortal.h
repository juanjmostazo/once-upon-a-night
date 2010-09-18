#ifndef GameObjectPortalH_H
#define GameObjectPortalH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Graphics/RenderComponent/RenderComponentGlow.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponentProp.h"

namespace OUAN
{
	const std::string PORTAL_ANIMATION_ONY_APPROACHING="";
	const std::string PORTAL_ANIMATION_CHANGING_WORLD="broken";

	const std::string PORTAL_STATE_IDLE="PORTAL_STATE_IDLE";
	const std::string PORTAL_STATE_ONY_APPROACHING="PORTAL_STATE_ONY_APPROACHING";
	const std::string PORTAL_STATE_HIT="PORTAL_STATE_HIT";
	const std::string PORTAL_STATE_CHANGING_WORLD="PORTAL_STATE_CHANGING_WORLD";

	const std::string PORTAL_SOUND_CHANGEWORLD="portal_changeworld";
	const std::string PORTAL_SOUND_CLOSE="portal_close";

	const std::string BROKEN_PORTAL_MESH="portal02.mesh";

	const double PORTAL_ROTATION_SPEED = 50;

	class AudioComponent;
	typedef boost::shared_ptr<AudioComponent> AudioComponentPtr;
	typedef std::map<std::string, int> TAudioComponentMap;

	/// Class to hold Portal information
	class GameObjectPortal : public GameObject, public boost::enable_shared_from_this<GameObjectPortal>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentEntityPtr mRenderComponentEntityBroken;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldIdleDreams;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldIdleNightmares;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldChanging;
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldSky;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPropPtr mLogicComponent;		

		AudioComponentPtr mAudioComponent;

		double mRotY;

	public:
		//Constructor
		GameObjectPortal(const std::string& name);
		//Destructor
		~GameObjectPortal();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		RenderComponentEntityPtr getRenderComponentEntityBroken() const;
		/// Set logic component
		void setLogicComponentProp(LogicComponentPropPtr logicComponentProp);

		/// return logic component
		LogicComponentPropPtr getLogicComponentProp();

		void setVisible(bool visible);

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);
		void setRenderComponentEntityBroken(RenderComponentEntityPtr pRenderComponentEntityBroken);

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
		void setRenderComponentParticleSystemChangeWorldIdleDreams(RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldIdleDreams);
		void setRenderComponentParticleSystemChangeWorldIdleNightmares(RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldIdleNightmares);
		void setRenderComponentParticleSystemChangeWorldChanging(RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldChanging);
		void setRenderComponentParticleSystemChangeWorldSky(RenderComponentParticleSystemPtr mRenderComponentParticleSystemChangeWorldSky);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemChangeWorldIdleDreams() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemChangeWorldIdleNightmares() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemChangeWorldChanging() const;
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemChangeWorldSky() const;

		/// Set physics component
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		AudioComponentPtr getAudioComponentInstance() const;
		bool hasAudioComponent() const;

		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);

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

		void updatePhysicsComponents(double elapsedSeconds);


		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;
	};

	class TGameObjectPortalParameters: public TGameObjectParameters
	{
	public:
		TGameObjectPortalParameters();
		~TGameObjectPortalParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		///Logic parameters
		TLogicComponentPropParameters tLogicComponentParameters;

		///Audio params
		TAudioComponentMap tAudioComponentParameters;
	};
}
#endif