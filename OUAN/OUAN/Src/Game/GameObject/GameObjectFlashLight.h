#ifndef GameObjectFlashLightH_H
#define GameObjectFlashLightH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentDecal.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
#include "../../Logic/LogicComponent/AttackComponent.h"
#include "../../Logic/LogicComponent/WeaponComponent.h"

namespace OUAN
{
	const std::string FLASHLIGHT_DECAL_PROJECTOR_NAME="Flashlight";
	const std::string FLASHLIGHT_DECAL_TEX_NAME="FlashlightDecal02.png";
	const std::string FLASHLIGHT_DECAL_FILTER_TEX_NAME="Decal_filter.png";

	const int RED = 0xff0000ff;
	const int BLUE= 0x0000ffff;
	const int GREEN=0x00ff00ff;
	const int WHITE=0xffffffff;

	const std::string ATTACK_NAME_RED="red";
	const std::string ATTACK_NAME_GREEN="green";
	const std::string ATTACK_NAME_BLUE="blue";
	const std::string ATTACK_NAME_WHITE="white";

	const std::string CONE_MATERIAL_NAME="flashlightcone_n";
	const std::string CONE_MESH_NAME="flashlightcone.mesh";

	class ProjectiveDecal;
	typedef boost::shared_ptr<ProjectiveDecal> ProjectiveDecalPtr;

	const double DEFAULT_ROLL_OMEGA = PI/2;

	/// Class to hold GameObjectFlashLight information
	class GameObjectFlashLight : public GameObject, public boost::enable_shared_from_this<GameObjectFlashLight>
	{
	private:
		/// Logic component: it'll represent the 'brains' of the game object
		LogicComponentPtr mLogicComponent;	
		AttackComponentPtr mAttackComponent;
		WeaponComponentPtr mParentWeaponComponent;

		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentLightPtr mRenderComponentLight;
		RenderComponentEntityPtr mConeEntity;
		RenderComponentDecalPtr mFlashlightDecalComponent;
		//ProjectiveDecalPtr mFlashlightDecal;
		/// Particle Systems
		RenderComponentParticleSystemPtr mRenderComponentParticleSystemAttack;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		RenderComponentPositionalPtr mLightPositionalComponent;

		/// Physics information
		PhysicsComponentVolumeConvexPtr mPhysicsComponentVolumeConvex;
		PhysicsComponentWeaponPtr mPhysicsComponentWeapon;

		RenderSubsystemPtr mRenderSubsystem;

		Ogre::Real rollAngle;
		Vector3 mLastBonePosition;

	public:
	//----------CONSTRUCTOR/DESTRUCTOR

		//Constructor
		GameObjectFlashLight(const std::string& name,RenderSubsystemPtr renderSubsystem);
		//Destructor
		~GameObjectFlashLight();

	//----------LOGIC COMPONENTS GETTERS/SETTERS

		/// return logic component
		LogicComponentPtr getLogicComponent();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);
		
		///Return parent weapon component (which will contain an instance
		/// to this flashlight)
		///@return parent object's weapon component
		WeaponComponentPtr getParentWeaponComponent() const;
		///Set the parent object's weapon component
		///@param parentWeaponComponent
		void setParentWeaponComponent(WeaponComponentPtr parentWeaponComponent);
		/// Tell if the game object is linked to 
		/// a parent game object through its weapon component
		/// @return true if this game object is linked to a parent
		/// object through its weapon component: false otherwise
		bool hasParentWeaponComponent() const;

		/// Return attack component
		AttackComponentPtr getAttackComponent() const;
		/// Set attack component
		void setAttackComponent(AttackComponentPtr attackComponent);

	//----------VISUAL COMPONENTS GETTERS/SETTERS

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;
		
		/// Return render component Light 
		/// @return render component Light
		RenderComponentLightPtr getRenderComponentLight() const;
		/// Set render component
		/// @param pRenderComponentLight
		void setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight);

		/// Set Particle Systems
		void setRenderComponentParticleSystemAttack(RenderComponentParticleSystemPtr mRenderComponentParticleSystemAttack);

		/// Get Particle Systems
		RenderComponentParticleSystemPtr getRenderComponentParticleSystemAttack() const;

		RenderComponentEntityPtr getConeEntity() const;
		void setConeEntity(RenderComponentEntityPtr coneEntity);

		RenderComponentDecalPtr getDecalComponent() const;
		void setDecalComponent(RenderComponentDecalPtr decalComponent);

	//----------POSITION COMPONENTS GETTERS/SETTERS

		RenderComponentPositionalPtr getLightPositionalComponent() const;
		void setLightPositionalComponent(RenderComponentPositionalPtr pRenderComponentPositional);
		

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;
		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;
		/// Set initial component
		void setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

	//----------PHYSICS COMPONENTS GETTERS/SETTERS

		/// Get physics component
		PhysicsComponentVolumeConvexPtr getPhysicsComponentVolumeConvex() const;
		/// Set physics component
		void setPhysicsComponentVolumeConvex(PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex);

		bool hasPhysicsComponent() const;
		PhysicsComponentPtr getPhysicsComponent() const;

		PhysicsComponentWeaponPtr getPhysicsComponentWeapon() const;
		void setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon);

	//----------WORLD CHANGE METHODS

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

	//----------- GENERAL GAME OBJECT MANAGEMENT
		/// Reset object
		virtual void reset();
		void enable();
		void disable();

		/// Update object
		void update(double elapsedSeconds);

	//----------- ATTACK-RELATED METHODS

		bool canInitiateAttack();

		/// Switch off the light
		void switchOff();
		/// Switch on the light
		void switchOn();
		/// Show the flashlight (i.e, the model)
		void show();
		/// Hide the flashlight (i.e, the model)
		void hide();

		std::string translateWeaponMode(TWeaponMode weaponMode);
		std::string getDefaultAttack();

		void beginAttack();
		void setAttack(const std::string& newAttack);

		// Return current colour
		int getColour();

		static std::string getColourName(int colour);
		int getAttackDamage() const;

		//Decal materials!
		void createProjector(TGameObjectContainer* objs);
		void applyTintColour(int colour);


		void loadDecalMaterials(TGameObjectContainer& mGameObjects);
		void unloadDecalMaterials();

	//----------LOGIC-RELATED PROCESSING METHODS
		
		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		
		void startAttackParticles();

		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

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
		TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters;

		TAttackComponentParameters attackComponentParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

		TRenderComponentEntityParameters tConeParams;
		TRenderComponentDecalParameters tDecalParams;

		//TRenderComponentBillboardSetParameters lightConeBBSParams;

	};
}
#endif