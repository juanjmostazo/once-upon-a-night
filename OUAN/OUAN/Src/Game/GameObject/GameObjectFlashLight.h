#ifndef GameObjectFlashLightH_H
#define GameObjectFlashLightH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
#include "../../Logic/LogicComponent/AttackComponent.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"

namespace OUAN
{
	const int RED = 0xff0000ff;
	const int BLUE= 0x0000ffff;
	const int GREEN=0x00ff00ff;
	const int WHITE=0xffffffff;

	const std::string ATTACK_NAME_RED="red";
	const std::string ATTACK_NAME_GREEN="green";
	const std::string ATTACK_NAME_BLUE="blue";
	const std::string ATTACK_NAME_WHITE="white";

	/// Class to hold GameObjectFlashLight information
	class GameObjectFlashLight : public GameObject, public boost::enable_shared_from_this<GameObjectFlashLight>
	{
	private:
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;		
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentLightPtr mRenderComponentLight;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		RenderComponentPositionalPtr mLightPositionalComponent;

		/// Physics information
		PhysicsComponentVolumeConvexPtr mPhysicsComponentVolumeConvex;

		CameraManagerPtr mCameraManager;
		GameWorldManagerPtr mGameWorldManager;
		RayCastingPtr mRayCasting;
		EventManagerPtr mEventManager;

		double distance;
		int mSelectedColour;
		int mDamage;
		int mAttackRange;//distance?
		double mAttackAngle;//flashlight cone angle

		AttackComponentPtr mAttackComponent;

		WeaponComponentPtr mParentWeaponComponent;

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
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

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

		/// Set physics component
		void setPhysicsComponentVolumeConvex(PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex);

		/// Get physics component
		PhysicsComponentVolumeConvexPtr getPhysicsComponentVolumeConvex() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;

		WeaponComponentPtr getParentWeaponComponent() const;
		void setParentWeaponComponent(WeaponComponentPtr parentWeaponComponent);
		bool hasParentWeaponComponent() const;

		bool canInitiateAttack();


		/// Update object
		void update(double elapsedSeconds);

		int getSelectedColour() const;
		void setSelectedColour(int selectedColour);

		void setAttackMode(TWeaponMode attackMode);
		/// Switch off the light
		void switchOff();
		/// Switch on the light
		void switchOn();
		/// Show the flashlight (i.e, the model)
		void show();
		/// Hide the flashlight (i.e, the model)
		void hide();

		/// Reset object
		virtual void reset();
		void enable();
		void disable();

		AttackComponentPtr getAttackComponent() const;
		void setAttackComponent(AttackComponentPtr attackComponent);
		std::string translateWeaponMode(TWeaponMode weaponMode);
		std::string getDefaultAttack();
		void beginAttack();
		void setAttack(const std::string& newAttack);

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

		// Return current colour
		int getColour();
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
		TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters;

		TAttackComponentParameters attackComponentParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

	};
}
#endif