#ifndef GameObjectFlashLightH_H
#define GameObjectFlashLightH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"

namespace OUAN
{
	const int RED = 0xff0000ff;
	const int BLUE= 0x0000ffff;
	const int GREEN=0x00ff00ff;
	const int WHITE=0xffffffff;
	/// Class to hold GameObjectFlashLight information
	class GameObjectFlashLight : public GameObject, public boost::enable_shared_from_this<GameObjectFlashLight>
	{
	private:
		
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentLightPtr mRenderComponentLight;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		RenderComponentPositionalPtr mLightPositionalComponent;

		/// Physics information
		PhysicsComponentSimpleCapsulePtr mPhysicsComponentSimpleCapsule;

		CameraManagerPtr mCameraManager;
		GameWorldManagerPtr mGameWorldManager;
		RayCastingPtr mRayCasting;
		EventManagerPtr mEventManager;

		double distance;
		int mSelectedColour;
		int mDamage;
		int mAttackRange;//distance?
		double mAttackAngle;//flashlight cone angle

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectFlashLight(const std::string& name, GameWorldManagerPtr pGameWorldManager, CameraManagerPtr pCameraManager, RayCastingPtr pRayCasting);
		//Destructor
		~GameObjectFlashLight();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		/// Return render component Light 
		/// @return render component Light
		RenderComponentLightPtr getRenderComponentLight() const;

		/// Set render component
		/// @param pRenderComponentLight
		void setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight);

		void setLightPositionalComponent(RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentPositionalPtr getLightPositionalComponent() const;

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

		/// Detects Flashlight's light collisions with the scene and adds the events to the eventManager
		void detectLightCollisions();

		/// Set physics component
		void setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule);

		/// Get physics component
		PhysicsComponentSimpleCapsulePtr getPhysicsComponentSimpleCapsule();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		/// Update object
		void update(double elapsedSeconds);

		int getSelectedColour() const;
		void setSelectedColour(int selectedColour);

		void setAttackMode(TWeaponMode attackMode);
		void switchOff();
		void switchOn();

		/// Reset object
		virtual void reset();
	};

	class TGameObjectFlashLightParameters: public TGameObjectParameters
	{
	public:
		TGameObjectFlashLightParameters();
		~TGameObjectFlashLightParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters;

	};
}
#endif