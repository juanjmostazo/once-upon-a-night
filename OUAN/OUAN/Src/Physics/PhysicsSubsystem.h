#ifndef PHYSICSSUBSYSTEMH_H
#define PHYSICSSUBSYSTEMH_H

#include "../OUAN.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

namespace OUAN
{
	//This class encapsulates the physics logic
	//of our game. It uses NxOgre BloodyMess v.1.5.5
	class PhysicsSubsystem : public NxOgre::ControllerCallback
	{
	public:

		//Constructor
		PhysicsSubsystem();

		//Destructor
		~PhysicsSubsystem();
		
		//Initialize physics subsystem elements
		virtual void initialise(ApplicationPtr app,OUAN::ConfigurationPtr config);

		//Reset physics level elements
		virtual void resetLevel();

		//Initialize physics level elements
		virtual void initialiseLevel(std::string sceneName);

		// Update physics subsystem elements
		virtual void update(float elapsedSeconds);

		//Free memory used by the physics subsystem
		virtual void cleanUp();

		//Getters
		virtual NxOgre::World* getNxOgreWorld();
		virtual NxOgre::Scene* getNxOgreScene();
		virtual OGRE3DRenderSystem* getNxOgreRenderSystem();
		virtual NxOgre::TimeController* getNxOgreTimeController();
		virtual NxOgre::ControllerManager* getNxOgreControllerManager();

		virtual NxOgre::Enums::ControllerAction onShape(const NxOgre::ControllerShapeHit& hit);
		virtual NxOgre::Enums::ControllerAction onController(NxOgre::Controller* controller, NxOgre::Controller* other);

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
	};
}
#endif