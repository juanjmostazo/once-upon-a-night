#ifndef PHYSICSSUBSYSTEMH_H
#define PHYSICSSUBSYSTEMH_H

#include "../OUAN.h"
#include "../Loader/Configuration.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

namespace OUAN
{
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

		//Destroy and free memory
		virtual void cleanUp();

		//Initialize physics level elements
		virtual void initLevel(std::string sceneName);

		//Destroy physics level elements
		virtual void clear();

		// Update physics subsystem elements
		virtual void update(double elapsedSeconds);

		//stabilize objects,  needs to be called at load level and change world
		void stabilize();

		//Getters
		virtual NxOgre::World* getNxOgreWorld();
		virtual NxOgre::Scene* getNxOgreScene();
		virtual OGRE3DRenderSystem* getNxOgreRenderSystem();
		virtual NxOgre::TimeController* getNxOgreTimeController();
		virtual NxOgre::ControllerManager* getNxOgreControllerManager();

		//General physics callbacks
		virtual bool onHitEvent(const NxOgre::RaycastHit& raycastHit);
		virtual void onContact(const NxOgre::ContactPair& contactPair);
		virtual void onVolumeEvent( NxOgre::Shape * volume, NxOgre::String collisionName, unsigned int collisionEventType );

		//Specific physics character callbacks
		virtual NxOgre::Enums::ControllerAction onShape(const NxOgre::ControllerShapeHit& hit);
		virtual NxOgre::Enums::ControllerAction onController(const NxOgre::ControllerControllerHit& hit);

		/// params read from config file
		NxOgre::Vec3 mGravity;
		double mStaticFriction;
		double mDynamicFriction;
		double mRestitution;
		double mDisplacementScale;
		double mMinDistance;
		double mMovementUnitsPerSecond;
		double mMovementUnitsPerSecondInverseScaled;
		double mMovementLimitUnitsPerSecond;
		double mMovementLimitUnitsPerSecondInverseScaled;
		double mTurnDegreesPerSecond;
		double mInitialJumpSpeed;		
		double mMinAllowedY;
		double mMinCollisionAngle;
		double mMinSlidingAngle;
		double mMinSlidingAngleFall;
		double mSlidingFactor;
		double mSlidingFactorFall;	
		double mDashFactor;
		double mDashMax;
		double mDashAccelerationIncrement;
		double mMinDashAccelerationFactor;
		double mMaxDashAccelerationFactor;
		double mAccelerationIncrement;
		double mMaxAccelerationFactor;
		double mMinAccelerationFactor;
		double mMaxSameDirectionAngle;		
		double mWalkSpeed;
		double mSlopeLimit;
		double mStepOffset;
		double mSkinWidth;
		double mGravityBodiesFactor;

		/// Load params from config file
		virtual bool loadConfig();

		bool raycastClosestGeometry(const Vector3 &point,const Vector3 &normal,Vector3 &result,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);
		bool raycastClosestBoundings(const Vector3 &point,const Vector3 &normal,Vector3 &result,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);

		//returns the number of hits
		int raycastAllBoundings(const Vector3 &point,const Vector3 &normal,std::vector<GameObjectPtr> &result,double maxDistance=-1,QueryFlags flags=QUERYFLAGS_NONE);

	protected:

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

		/// Auxiliar function
		bool setGameObjectSlidingFromController(NxOgre::Controller* controller, NxOgre::Vec3 normal, double normalAngle);

		/// Auxiliar function
		bool areClose(NxOgre::Vec3 position1, NxOgre::Vec3 position2, double radius);

		/// Auxiliar function
		bool isOnyCloseFromPosition(NxOgre::Vec3 position, double radius);

		/// Fetch function
		GameObjectPtr getGameObject(NxOgre::String name);

		/// Sends collisions to the EventManager function
		bool sendCollision(GameObjectPtr object1, GameObjectPtr object2);
		bool sendEnterTrigger(GameObjectPtr object1, GameObjectPtr object2);
		bool sendExitTrigger(GameObjectPtr object1, GameObjectPtr object2);
	};
}
#endif