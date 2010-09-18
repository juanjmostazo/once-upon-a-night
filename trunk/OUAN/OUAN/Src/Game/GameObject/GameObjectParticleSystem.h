#ifndef GameObjectParticleSystemH_H
#define GameObjectParticleSystemH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	/// Models a light source object
	class GameObjectParticleSystem : public GameObject, public boost::enable_shared_from_this<GameObjectParticleSystem>
	{
	private:
		/// Holds the information related to visual rendering
		RenderComponentParticleSystemPtr mRenderComponentParticleSystem;
		/// Holds information related to the object's position in space
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
	public:
		//Constructor
		GameObjectParticleSystem(const std::string& name);
		//Destructor
		~GameObjectParticleSystem();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Get light component
		/// @return light component
		RenderComponentParticleSystemPtr getRenderComponentParticleSystem() const;

		/// Set light component
		/// @param pRenderComponentLight the light component to set
		void setRenderComponentParticleSystem(RenderComponentParticleSystemPtr pRenderComponentParticleSystem);

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

		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);


		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		
		

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponent() const;
	};

	/// Transport object carrying around data from the level loader
	/// to the ParticleSystem object
	class TGameObjectParticleSystemParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectParticleSystemParameters();
		/// Default destructor
		~TGameObjectParticleSystemParameters();

		/// Light-specific parameters
		TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

	};
}
#endif