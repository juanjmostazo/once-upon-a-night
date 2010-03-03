#pragma once

#include <Ogre.h>
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

#include "SimpleInputManager.h"
#include "OrbitCameraController.h"

#define NXS_PATH "file:../media/nxs"

enum GameGroup
{
   GROUP_NON_COLLIDABLE,
   GROUP_COLLIDABLE_NON_PUSHABLE,
   GROUP_COLLIDABLE_PUSHABLE,
};

#define COLLIDABLE_MASK (1 << GROUP_COLLIDABLE_NON_PUSHABLE) | (1 << GROUP_COLLIDABLE_PUSHABLE)

class Application : SimpleInputManager, NxOgre::ControllerCallback, public NxOgre::Callback
{
	public:
		Application();
		~Application();

		bool initialise();
		bool setup();

		bool createCharacter();
		bool createVolume();
		bool createBasicScenary();
		bool createTriangleMeshes();
		bool createConvexes();

		void update();
		void loadResources();

		void updateLogic(const float elapsedSeconds);
		void updateAnimations(const float elapsedSeconds);
		void updateOverlayInfo();
		
		virtual bool keyPressed( const OIS::KeyEvent& e );
		virtual bool mouseMoved( const OIS::MouseEvent& e );
	
	private:
		Ogre::Root* m_root;
		Ogre::RenderWindow* m_window;
		Ogre::SceneManager* m_sceneMgr;
		Ogre::Viewport* m_viewport;
		Ogre::Camera* m_camera;
		OrbitCameraController* m_cameraOrbitController;
		Ogre::Entity* m_character;
		
		NxOgre::World* m_NXOgreWorld;
		NxOgre::Scene* m_NXOgreScene;
		OGRE3DRenderSystem* m_NXOgreRenderSystem;
		NxOgre::TimeController* m_NXOgreTimeController;

		NxOgre::VisualDebugger*	m_NXOgreVisualDebugger;
		OGRE3DRenderable*		m_NXOgreVisualDebuggerRenderable;
		Ogre::SceneNode*		m_NXOgreVisualDebuggerNode;

		NxOgre::ControllerManager* m_NXOgreControllerManager;
		NxOgre::Controller* m_NXOgreController;
		OGRE3DPointRenderable* m_NXOgreControllerRenderable;
		
		Ogre::AnimationState* m_idleAnimation;
		Ogre::AnimationState* m_runAnimation;
		int m_movingDirection;

		NxOgre::Volume* m_volume;

		bool m_exitRequested;
		bool m_showInfo;
		bool m_showDebug;
		
		virtual NxOgre::Enums::ControllerAction onShape(const NxOgre::ControllerShapeHit& hit)
		{
			return NxOgre::Enums::ControllerAction_None;
		}

		virtual NxOgre::Enums::ControllerAction onController(NxOgre::Controller* controller, NxOgre::Controller* other)
		{	
			return NxOgre::Enums::ControllerAction_None;
		}

		void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, NxOgre::RigidBody* rigidBody, NxOgre::Shape* rigidBodyShape, unsigned int collisionEvent)
		{
			/*
			if(collisionEvent == NxOgre::Enums::VolumeCollisionType_OnEnter)
			{
				NxOgre::Actor* actor = static_cast<NxOgre::Actor*>(rigidBody);
				float y =   (9.81 * actor->getMass())				  // counteract gravity
					+ (-actor->getLinearVelocity().y * actor->getMass())      // counteract vertical velocity
					+ (10 - actor->getGlobalPosition().y * actor->getMass()); // Add some force to move it to the top

				actor->addForce(NxOgre::Vec3(0, y, 0), NxOgre::Enums::ForceMode_Impulse); 
			}
			*/
		}

		void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, void* controller, unsigned int collisionEvent)
		{

		}
};