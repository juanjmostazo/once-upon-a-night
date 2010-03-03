#include "ExampleApplication.h"

#include <NxOgre.h>
#include <NxOgreOGRE3D.h>

class ExampleListener : public ExampleFrameListener
{ 
public:
	ExampleListener(RenderWindow *win, Camera *cam, NxOgre::VisualDebugger* visualDebugger, Ogre::SceneNode* node) 
		: ExampleFrameListener(win, cam)
	{
		mTimeController = NxOgre::TimeController::getSingleton();
		mVisualDebugger = visualDebugger;
		mVisualDebuggerNode = node;
	}

	bool frameStarted(const FrameEvent& evt)
	{
		mTimeController->advance(evt.timeSinceLastFrame);
		mVisualDebugger->draw();
		mVisualDebuggerNode->needUpdate();

		return ExampleFrameListener::frameStarted(evt);
	}

protected:
	NxOgre::TimeController*		mTimeController;
	NxOgre::VisualDebugger*		mVisualDebugger;
	Ogre::SceneNode*		mVisualDebuggerNode;
};

class Application : public ExampleApplication, public NxOgre::Callback
{
protected:
	NxOgre::World*			mWorld;
	NxOgre::Scene*			mScene;
	NxOgre::TimeController*		mTimeController;
	OGRE3DRenderSystem*		mRenderSystem;

	OGRE3DBody*			mCube;
	NxOgre::Volume*			mVolume;

	NxOgre::VisualDebugger*		mVisualDebugger;
	OGRE3DRenderable*		mVisualDebuggerRenderable;
	Ogre::SceneNode*		mVisualDebuggerNode;

	void createScene()
	{
		// Set ambient light
		mSceneMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

		// Create a light
		Light* l = mSceneMgr->createLight("MainLight");
		l->setPosition(20, 80, 50);

		// Position the camera
		mCamera->setPosition(0, 20, 80);
		mCamera->lookAt(0, 20, 0);

		// Create the world
		mWorld = NxOgre::World::createWorld();

		mVisualDebugger = mWorld->getVisualDebugger();

		// Create scene description
		NxOgre::SceneDescription sceneDesc;
		sceneDesc.mGravity = NxOgre::Vec3(0, -9.81f, 0);
		sceneDesc.mName = "DemoScene";

		// Create scene
		mScene = mWorld->createScene(sceneDesc);

		// Set some physical scene values
		mScene->getMaterial(0)->setStaticFriction(0.5);
		mScene->getMaterial(0)->setDynamicFriction(0.5);
		mScene->getMaterial(0)->setRestitution(0.1);

		// Create render system
		mRenderSystem = new OGRE3DRenderSystem(mScene);

		//Create time controller
		mTimeController = NxOgre::TimeController::getSingleton();

		// Add objects
		mCube = mRenderSystem->createBody(new NxOgre::Box(1, 1, 1), NxOgre::Vec3(0, 20, 0), "cube.1m.mesh");

		// Create floor plane (Ogre)
		MovablePlane *plane = new MovablePlane("Plane");
		plane->d = 0;
		plane->normal = Vector3::UNIT_Y;
		Ogre::MeshManager::getSingleton().createPlane("PlaneMesh", 
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
			*plane, 120, 120, 1, 1, true, 1, 3, 3, Vector3::UNIT_Z);
		Entity *planeEnt = mSceneMgr->createEntity("PlaneEntity", "PlaneMesh");
		planeEnt->setMaterialName("Examples/GrassFloor");

		Ogre::SceneNode* mPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mPlaneNode->attachObject(planeEnt);

		mVolume = mScene->createVolume(new NxOgre::Box(10), NxOgre::Matrix44(NxOgre::Vec3(0, 5, 0)), this, NxOgre::Enums::VolumeCollisionType_All);

		mVisualDebuggerRenderable = new OGRE3DRenderable(NxOgre::Enums::RenderableType_VisualDebugger);
		mVisualDebugger->setRenderable(mVisualDebuggerRenderable);
		mVisualDebuggerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mVisualDebuggerNode->attachObject(mVisualDebuggerRenderable);
		mVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowAll);
	}

	// Create a new frame listener
	void createFrameListener()
	{
		mFrameListener = new ExampleListener(mWindow, mCamera, mVisualDebugger, mVisualDebuggerNode);
		mRoot->addFrameListener(mFrameListener);
	}

	void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, NxOgre::RigidBody* rigidBody, NxOgre::Shape* rigidBodyShape, unsigned int collisionEvent)
	{
		if(collisionEvent == NxOgre::Enums::VolumeCollisionType_OnEnter)
		{
			NxOgre::Actor* actor = static_cast<NxOgre::Actor*>(rigidBody);
			float y =   (9.81 * actor->getMass())				  // counteract gravity
				+ (-actor->getLinearVelocity().y * actor->getMass())      // counteract vertical velocity
				+ (10 - actor->getGlobalPosition().y * actor->getMass()); // Add some force to move it to the top

			actor->addForce(NxOgre::Vec3(0, y, 0), NxOgre::Enums::ForceMode_Impulse); 
		}
	}

	void onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, void* controller, unsigned int collisionEvent)
	{

	}
};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char **argv)
#endif
	{
		// Create application object
		Application app;

		try {
			app.go();
		} catch(Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBoxA(NULL, e.getFullDescription().c_str(),
				"An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occurred: " << e.getFullDescription();
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif