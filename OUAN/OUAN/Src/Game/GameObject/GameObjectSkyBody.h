#ifndef GAMEOBJECTSKYBODYH_H
#define GAMEOBJECTSKYBODYH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
#include "../../Graphics/RenderComponent/RenderComponentGlow.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{

	class LensFlare;
	typedef boost::shared_ptr<LensFlare> LensFlarePtr;
	/// Class to hold Traspasable information
	class GameObjectSkyBody: public GameObject, public boost::enable_shared_from_this<GameObjectSkyBody>
	{
	private:
		// TODO: Maybe replace with a billboard

		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		RenderComponentGlowPtr mRenderComponentGlowDreams;
		RenderComponentGlowPtr mRenderComponentGlowNightmares;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;

		RenderComponentBillboardSetPtr mBBSComponentDreams;
		RenderComponentBillboardSetPtr mBBSComponentNightmares;

		RenderComponentLightPtr mLightComponentDreams;
		RenderComponentLightPtr mLightComponentNightmares;

		bool mUseEntityDreams;
		bool mUseEntityNightmares;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;

		LensFlarePtr mLensFlare;

	public:
		//Constructor
		GameObjectSkyBody(const std::string& name);
		//Destructor
		~GameObjectSkyBody();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		void setVisible(bool visible);

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

		/// Return render component entity 
		/// @return render component entity
		RenderComponentGlowPtr getRenderComponentGlowDreams() const;
		RenderComponentGlowPtr getRenderComponentGlowNightmares() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentGlowDreams(RenderComponentGlowPtr pRenderComponentGlowDreams);
		void setRenderComponentGlowNightmares(RenderComponentGlowPtr pRenderComponentGlowNightmares);

		RenderComponentBillboardSetPtr getRenderComponentBillboardSetDreams() const;
		void setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr bbsDreams);

		RenderComponentBillboardSetPtr getRenderComponentBillboardSetNightmares() const;
		void setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr bbsNightmares);

		RenderComponentLightPtr getLightDreams() const;
		void setLightDreams(RenderComponentLightPtr lightComponent);
		RenderComponentLightPtr getLightNightmares() const;
		void setLightNightmares(RenderComponentLightPtr lightComponent);

		bool isUsingEntityDreams();
		void setUseEntityDreams(bool useEntity);

		bool isUsingEntityNightmares();
		void setUseEntityNightmares(bool useEntity);

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

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();

		LensFlarePtr getLensFlare() const;
		void setLensFlare(LensFlarePtr lensFlare);
		void initLensFlare(Ogre::Camera*, Ogre::SceneManager*);

		/// Reset object
		virtual void reset();

		/// 
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

		
		

		/// 
		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		void update(double elapsedSeconds);

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;
	};

	class TGameObjectSkyBodyParameters: public TGameObjectParameters
	{
	public:
		TGameObjectSkyBodyParameters();
		~TGameObjectSkyBodyParameters();

		bool useEntityDreams;
		bool useEntityNightmares;

		bool useDreamsGlow;
		bool useNightmaresGlow;

		std::string dreamsGlowMaterial;
		std::string nightmaresGlowMaterial;

		TRenderComponentLightParameters lightDreamsParams;
		TRenderComponentLightParameters lightNightmaresParams;

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		TRenderComponentBillboardSetParameters bbsDreamsParams;
		TRenderComponentBillboardSetParameters bbsNightmaresParams;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///RenderComponentGlow parameters
		TRenderComponentGlowParameters tRenderComponentGlowDreamsParameters;
		TRenderComponentGlowParameters tRenderComponentGlowNightmaresParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;	
	};
}
#endif