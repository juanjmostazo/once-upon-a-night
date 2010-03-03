#ifndef PHYSICSSUBSYSTEMH_H
#define PHYSICSSUBSYSTEMH_H

#include "../OUAN.h"
#include "../Loader/Configuration.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

namespace OUAN
{
	const std::string PHYSICS_CFG="../../Config/physics-cfg.xml";

	//This class encapsulates the physics logic
	//of our game. It uses NxOgre BloodyMess v.1.5.5
	class PhysicsSubsystem : public NxOgre::Callback, public NxOgre::ControllerCallback
	{
	public:

		//Constructor
		PhysicsSubsystem();

		//Destructor
		~PhysicsSubsystem();
		
		//Initialize physics subsystem elements
		virtual void init(ApplicationPtr app,OUAN::ConfigurationPtr config);

		//Reset physics level elements
		virtual void resetLevel();

		//Initialize physics level elements
		virtual void initLevel(std::string sceneName);

		// Update physics subsystem elements
		virtual void update(double elapsedSeconds);

		//Free memory used by the physics subsystem
		virtual void cleanUp();

		//Getters
		virtual NxOgre::World* getNxOgreWorld();
		virtual NxOgre::Scene* getNxOgreScene();
		virtual OGRE3DRenderSystem* getNxOgreRenderSystem();
		virtual NxOgre::TimeController* getNxOgreTimeController();
		virtual NxOgre::ControllerManager* getNxOgreControllerManager();

		//General physics callbacks
		virtual void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, 
			NxOgre::RigidBody* collision_body, NxOgre::Shape* rigidBodyShape, unsigned int collisionEvent);
		virtual bool onHitEvent(const NxOgre::RaycastHit& raycastHit);
		virtual void onContact(const NxOgre::ContactPair& contactPair);

		virtual void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, 
			void* controller, unsigned int collisionEvent);

		//Specific physics character callbacks
		virtual NxOgre::Enums::ControllerAction onShape(const NxOgre::ControllerShapeHit& hit);
		virtual NxOgre::Enums::ControllerAction onController(NxOgre::Controller* controller, NxOgre::Controller* other);

	protected:
		
		/// param read from config file, gravity force
		NxOgre::Vec3 mGravity;

		/// param
		double mStaticFriction;
		
		/// param
		double mDynamicFriction;

		/// param
		double mRestitution;

		/// param read from config file, applied to move()
		double mDisplacementScale;

		/// param read from config file, applied to move()
		double mMinDistance;

		/// param read from config file, applied to move()
		double mMovementUnitsPerSecond;

		/// param read from config file, applied to move()
		double mTurnDegreesPerSecond;

		/// param read from config file, applid to jump
		double mInitialJumpSpeed;

		/// the application
		OUAN::ApplicationPtr mApp;

		/// the configuration
		OUAN::ConfigurationPtr mConfig;

		/// NxOgre world
		NxOgre::World* mNxOgreWorld;
		
		/// NxOgre main scene
		NxOgre::Scene* mNxOgreScene;

		/// NxOgre render system
		OGRE3DRenderSystem* mNxOgreRenderSystem;

		/// NxOgre time controller
		NxOgre::TimeController* mNxOgreTimeController;

		/// NxOgre controller manager
		NxOgre::ControllerManager* mNxOgreControllerManager;

		/// Load params from config file
		virtual bool loadConfig();

		virtual void initPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);
		virtual void initPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex);
		virtual void initPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle);
		virtual void initPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule);
		virtual void initPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);
		virtual void initPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule);
		virtual void initPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox);

		virtual void updateGameObjectOny(double elapsedSeconds, GameObjectOnyPtr pGameObjectOny);
		virtual void updateGameObjectTripollo(double elapsedSeconds, GameObjectTripolloPtr pGameObjectTripollo);
		virtual void updateGameObjectEye(double elapsedSeconds, GameObjectEyePtr pGameObjectEye);
	};
}
#endif